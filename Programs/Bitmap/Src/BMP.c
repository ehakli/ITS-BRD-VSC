#include "BMP.h"
#include "BMP_types.h"
#include "errorhandler.h"
#include "LCD_GUI.h"
#include "input.h"
#include <stdint.h>

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
    RETURN_NOK_ON_ERR(1 != COMread((char*)&infoHeader, sizeof(BITMAPINFOHEADER),1), "Fehler!");
    RETURN_NOK_ON_ERR(infoHeader.biSize != 0x28,"Fehler")
    RETURN_NOK_ON_ERR(infoHeader.biBitCount != 8 && infoHeader.biBitCount != 24, "Fehler")
    RETURN_NOK_ON_ERR(infoHeader.biCompression != BI_RGB && infoHeader.biCompression != BI_RLE8, "Fehler")
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
    RETURN_NOK_ON_ERR(numColors != COMread((char*)palette, sizeof(RGBQUAD), numColors), "Fehler!");
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
    bmp_decodePixels();
}