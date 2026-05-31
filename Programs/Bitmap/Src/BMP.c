/**
 ******************************************************************************
 * @file    bmp.c
 * @author  Timo Hinrichs, Emre Hakli
 * @brief   Funktionen zum einlesen der Header, Paletten und Dekodieren der Pixel einer BMP Datei auf dem ITS-Board. 
 ******************************************************************************
 */

#include "BMP.h"
#include "BMP_types.h"
#include "LCD_general.h"
#include "errorhandler.h"
#include "LCD_GUI.h"
#include "input.h"
#include <stdbool.h>
#include <stdint.h>
#include "lcd.h"

static BITMAPFILEHEADER fileHeader;
static BITMAPINFOHEADER infoHeader;
static RGBQUAD palette[256];

static uint16_t bmp_toRGB565(uint8_t r, uint8_t g, uint8_t b)
{
    return ((r >> 3) <<11) | ((g >> 2) << 5) | (b >> 3);
}

static int bmp_readFileHeader(void)
{
    RETURN_NOK_ON_ERR(1 != COMread((char*)&fileHeader, sizeof(BITMAPFILEHEADER), 1), "Fehler!");
    RETURN_NOK_ON_ERR(fileHeader.bfType != BMP_SIGNATURE, "keine BMP Datei!");
    return EOK;

}

static int bmp_readInfoHeader(void)
{
    RETURN_NOK_ON_ERR(1 != COMread((char*)&infoHeader, sizeof(BITMAPINFOHEADER), 1), "Fehler!");
    RETURN_NOK_ON_ERR(infoHeader.biSize != 0x28,"Falsche InfoHeader Groesse!")
    RETURN_NOK_ON_ERR(infoHeader.biBitCount != 8 && infoHeader.biBitCount != 24, "Falsche Farbtiefe!")
    RETURN_NOK_ON_ERR(infoHeader.biCompression != BI_RGB && infoHeader.biCompression != BI_RLE8, "Falsche Kompression!")
    return EOK;
}

static int bmp_readPalette(void)
{
    uint32_t numColors;
    if(infoHeader.biClrUsed == 0)
    {
        numColors = 256;
    }
    else
    {
        numColors = infoHeader.biClrUsed;
    }
    RETURN_NOK_ON_ERR(numColors != COMread((char*)palette, sizeof(RGBQUAD), numColors), "Fehler beim Palette einlesen!");
    return EOK;
}

static int bmp_decodePixels(void)
{
    int rowBytes = (((infoHeader.biWidth * infoHeader.biBitCount) +31)/32)*4;
    int padding = rowBytes - (infoHeader.biWidth * (infoHeader.biBitCount /8));

    for(int y_bmp = 0; y_bmp < infoHeader.biHeight; y_bmp++)
    {
        int y_display = (infoHeader.biHeight -1) - y_bmp;
        for (int i = 0; i < infoHeader.biWidth; i++)
        {
            uint8_t r, g, b;
            if(infoHeader.biBitCount == 8)
            {
                int index = nextChar();
                r = palette[index].rgbRed;
                g = palette[index].rgbGreen;
                b = palette[index].rgbBlue;
            }
            else
            {
                RGBTRIPLE pixel;
                COMread((char*)&pixel, sizeof(RGBTRIPLE), 1);
                r = pixel.rgbtRed;
                g = pixel.rgbtGreen;
                b = pixel.rgbtBlue;
            }
            uint16_t color = bmp_toRGB565(r,g,b);
            Coordinate point = {(uint16_t)i, (uint16_t)y_display};
            if(i < 480 && y_display < 320)
            {
                GUI_drawPoint(point, color, DOT_PIXEL_1X1, DOT_FILL_AROUND);
            }
        }
        for(int o = 0; o < padding; o++)
        {
            nextChar();
        }
    }
    return EOK;
}

static int bmp_decodePixelsTwo(void)
{
    if (infoHeader.biCompression == BI_RLE8) // 8 compressed
    {
        int x = 0;
        int y_display = infoHeader.biHeight - 1; // Start unten
        bool endOfBitmap = false;

        static COLOR compressedBuffer[480];

        for(int i = 0; i<480; i++) //füllen, da manche bytes übersprungen werden, und wir diese trotzdem schreiben müssen. (außer writeline kann leere array stellen überspringen)
        {
            compressedBuffer[i] = WHITE;
        }


        while (!endOfBitmap)
        {
            uint8_t byte1 = nextChar();
            uint8_t byte2 = nextChar();

            if (byte1 > 0)
            {
                uint8_t r = palette[byte2].rgbRed;
                uint8_t g = palette[byte2].rgbGreen;
                uint8_t b = palette[byte2].rgbBlue;
                uint16_t color = bmp_toRGB565(r, g, b);

                for (int i = 0; i < byte1; i++)
                {
                    if (x < 480)
                    {
                        //Coordinate point = {(uint16_t)x, (uint16_t)y_display};
                        //GUI_drawPoint(point, color, DOT_PIXEL_1X1, DOT_FILL_AROUND);
                        compressedBuffer[x] = color;
                    }
                    x++;
                }
            }
            else
            {
                // ESCAPE MODE
                switch (byte2)
                {
                    case 0: // EOL
                    if(y_display >= 0 && y_display < 320 && x > 0) //all done?
                    {
                        Coordinate start = {0, (uint16_t)y_display};
                        LENGTH length = (x < 480) ? (LENGTH)x : 480;
                        GUI_WriteLine(start, length, compressedBuffer);
                    }
                        x = 0;
                        y_display--;

                        for(int i = 0; i < 480; i++) // buffer säubern, da da noch die alten farben drinne stehen
                        {
                            compressedBuffer[i] = WHITE;
                        }
                        break;

                    case 1: // bitmap ende, zeiche noch einmal die Zeile davor
                    if (y_display >= 0 && y_display < 320 && x > 0)
                        {
                            Coordinate start = {0, (uint16_t)y_display};
                            LENGTH length = (x < 480) ? (LENGTH)x : 480;
                            GUI_WriteLine(start, length, compressedBuffer);
                        }
                        endOfBitmap = true;
                        break;

                    case 2: // Delta
                        x += nextChar();
                        y_display -= nextChar();
                        break;

                    default:
                        for (int i = 0; i < byte2; i++)
                        {
                            uint8_t index = nextChar();
                            uint8_t r = palette[index].rgbRed;
                            uint8_t g = palette[index].rgbGreen;
                            uint8_t b = palette[index].rgbBlue;
                            uint16_t color = bmp_toRGB565(r, g, b);

                            if (x < 480)
                            {
                                //Coordinate point = {(uint16_t)x, (uint16_t)y_display};
                                //GUI_drawPoint(point, color, DOT_PIXEL_1X1, DOT_FILL_AROUND);
                                compressedBuffer[x] = color;
                            }
                            x++;
                        }
                        // ungerade
                        if (byte2 % 2 != 0)
                        {
                            nextChar();
                        }
                        break;
                }
            }
        }
    }

    else //uncompressed
    {
        int rowBytes = (((infoHeader.biWidth * infoHeader.biBitCount) + 31) / 32) * 4;
        int padding = rowBytes - (infoHeader.biWidth * (infoHeader.biBitCount / 8));

        static COLOR buffer[480];

        for(int y_bmp = 0; y_bmp < infoHeader.biHeight; y_bmp++)
        {
            int y_display = (infoHeader.biHeight - 1) - y_bmp;

            for (int i = 0; i < infoHeader.biWidth; i++)
            {
                uint8_t r, g, b;
                if(infoHeader.biBitCount == 8)
                {
                    int index = nextChar();
                    r = palette[index].rgbRed;
                    g = palette[index].rgbGreen;
                    b = palette[index].rgbBlue;
                }
                else
                {
                    RGBTRIPLE pixel;
                    COMread((char*)&pixel, sizeof(RGBTRIPLE), 1);
                    r = pixel.rgbtRed;
                    g = pixel.rgbtGreen;
                    b = pixel.rgbtBlue;
                }
                uint16_t color = bmp_toRGB565(r, g, b);
                
                if(i < 480 && y_display < 320)
                {
                    //Coordinate point = {(uint16_t)i, (uint16_t)y_display};
                    //GUI_drawPoint(point, color, DOT_PIXEL_1X1, DOT_FILL_AROUND);
                    buffer[i] = color;
                }
            }
            
            for(int o = 0; o < padding; o++)
            {
                nextChar();
            }

            if(y_display >= 0 && y_display < 320)
            {
                Coordinate start = {0, (uint16_t)y_display};
                LENGTH length = (infoHeader.biWidth < 480) ? (LENGTH)infoHeader.biWidth : 480;
                GUI_WriteLine(start, length, buffer);
            }
        }
    }
    return EOK;
}


void bmp_displayNext(void)
{
    GUI_clear(WHITE);
    openNextFile();

    if(EOK != bmp_readFileHeader()) return;
    if(EOK != bmp_readInfoHeader()) return;
    if(infoHeader.biBitCount == 8)
    {
        if(EOK != bmp_readPalette()) return;
    }

    bmp_decodePixelsTwo();
} 