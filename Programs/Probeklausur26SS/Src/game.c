/**
 ******************************************************************************
 * @file    game.c
 *
 * @date    25. Juli 2024
 * @brief   Template der game.c f�r die Laborklausur GS SoSe 2024
 *
 * @author  
 *
 ******************************************************************************
 */

#include "display.h"
#include "lcd.h"
#include "main.h"
#include "io.h"
#include "touch.h"

extern piece_t pieces[9];

bool isNeighbour(int pos0, int pos1) {
    int col0 = pos0 % 3;
    int col1 = pos1 % 3;
    int row0 = pos0 / 3;
    int row1 = pos1 / 3;

    bool isHorizontal = ((row0 == row1) && ((col0 == col1 + 1) || (col0 == col1 - 1)));
    bool isVertical = ((col0 == col1) && ((row0 == row1 + 1) || (row0 == row1 - 1)));

    return isHorizontal || isVertical;
}

void getPosLED(bool* leds) {

    for(int i = 0; i < 8; i++)
    {
        leds[i] = false;
    }

    for(int pos = 1; pos < 9; pos++)
    {
        if(pieces[pos].number == pos)
        {
            leds[pos - 1] = true;
        }
    }
}

bool checkGameOver(void) {
    for(int block = 0; block < 9; block++)
    {
        if(pieces[block].number != block)
        {
            return false;
        }
    }

    return true;
}
	
void startGame(void)
{
    bool leds[8];
    getPosLED(leds);
    setLEDs(leds);
    if(checkGameOver())
    {
        if(getButton(0))
        {
            initPuzzle();
            drawPuzzle();
        }
    }
    else 
    {
        int touched = getTouchedBlock();

        if(touched != -1)
        {
            int gap = -1;
            for(int i = 0; i < 9; i++)
            {
                if(pieces[i].number == 0)
                {
                    gap = i;
                    break;
                }
            }

            if(isNeighbour(touched, gap))
            {
                pieces[gap].number = pieces[touched].number;
                pieces[touched].number = 0;

                drawPiece(touched);
                drawPiece(gap);

                getPosLED(leds);
                setLEDs(leds);
            }
        }
    }
}

// EOF