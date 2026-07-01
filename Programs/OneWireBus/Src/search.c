#include "gpio.h"
#include <stdbool.h>
#include <stdint.h>
#include "search.h"
#include "lcd.h"
#include "stdio.h"

uint8_t rom_num[8]; // speichert ROM
uint8_t lastDiscrepanc; // speichert bit position, 
bool lastDevice; // flag für letzten sensor
unsigned char crc8;


void reset_search(void)
{
    lastDiscrepanc = 0;
    lastDevice = 0; 
    
    for(int i = 0; i < 8; i++)
    {
        rom_num[i] = 0;
    }
}

uint8_t search(void)
{
    int id_bit_num;
    int lastZero, romByteNum, result;
    int id, cmp_id;

    unsigned char rom_byte_mask, search_direction;

    id_bit_num = 1;
    lastZero = 0;
    romByteNum = 0;
    rom_byte_mask = 1; // die maske für die 1 in der jeweiligen stelle im family code
    result = 0;
    crc8 = 0; //resette den crc pro search


    if(!lastDevice)
    {
        if(!reset())
        {
            lcdPrintlnS("reset fail\n"); //debug
            lastDiscrepanc = 0;
            lastDevice = false;
            return 0;
        }

        writeByte(SEARCH_ROM_COMMAND);

        do
        {
            id = readBit();
            cmp_id = readBit();

            // kein gerät angeschlossen
            if((id == 1) && (cmp_id == 1))
            {
                char buf[32];
                snprintf(buf, sizeof(buf), "bit failure: %d\n", id_bit_num); // debug
                lcdPrintlnS(buf);
                break;
            }
                
            else
            {
                // alle geräte haben 0 oder 1
                if(id != cmp_id)
                {
                    search_direction = id;
                }
                else
                {   //  wenn wir noch nicht bei der diskrepanz angekommen sind, einfach weiter (oder: Take the same path as last time)
                    if(id_bit_num < lastDiscrepanc)
                    {
                        search_direction = ((rom_num[romByteNum] & rom_byte_mask) > 0);
                    }
                    else
                    {   // wenn bei alter diskrepanz angekommen, wähle 1, wenn nicht 0 (oder: neuen Split gefunden, da weiter)
                        search_direction = (id_bit_num == lastDiscrepanc);
                    }

                    if(search_direction == 0)
                    {   // wenn 0 gewählt, aufzeichnen
                        lastZero = id_bit_num;
                    }
                }

                if(search_direction == 1)
                { //set bit
                    rom_num[romByteNum] |= rom_byte_mask;
                    writeOne();
                }
                else
                { //clear bit
                    rom_num[romByteNum] &= ~rom_byte_mask;
                    writeZero();
                }

                // writeByte(search_direction); 

                // index erhöhen
                id_bit_num++;
                // verschieben, da die maske angepasst werden muiss um an der richtigen stelle im byte zu schreiben
                rom_byte_mask <<= 1;

                if(rom_byte_mask == 0) // wenn bei nächstem byte angekommen, da mask von 8 auf 0 flippt
                { //crc validieren, counter erhöhen und maske wieder auf 1
                    checkcrc8(rom_num[romByteNum]);
                    romByteNum++;
                    rom_byte_mask = 1;
                }
            }
        }
        while(romByteNum < 8); //durch alle bytes loopen

        if(!((id_bit_num < 65) || (crc8 != 0)))
        { //search successful
            lastDiscrepanc = lastZero;

            if(lastDiscrepanc == 0)
            {
                lastDevice = true;
            }
            result = true;
        }
        else 
        {
            lcdPrintlnS("crc falsch!\n"); // debug
        }

    }

    if(!result  || !rom_num[0]) //wenn kein gerät vorhanden ist, reset auf ersten
    {
        lastDiscrepanc = 0;
        lastDevice = false;
        result = false;
    }

    return result;
}

unsigned char checkcrc8(unsigned char value)
{
    for(int i = 0; i < 8; i++)
    {
        uint8_t calculated = (crc8 ^ value) & 0x01;

        crc8 = crc8 >> 1;

        if(calculated)
        {
            crc8 ^= 0x8C;
        }

        value = value >> 1;
    }

    return crc8;
}



/*uint8_t search_next(void)
{
    if(lastDevice) return 0;

    if(reset() == 0)
    {
        reset_search();
        return 0;
    }

    uint8_t bit_index = 1; // index von der rom nummer am Bus
    uint8_t lastzero = 0; // index vom letzten 0 
    uint8_t rom_num_index = 0; // index von UNSEREM array
    uint8_t search_direction = 0; 
    uint8_t id, cmp_id; // erstes gelesenes bit, und das compare 
    uint8_t result;


    writeByte(SEARCH_ROM_COMMAND);

    for(int i = 0; i < 64; i++)
    {
        id = readBit();
        cmp_id = readBit();

        if((id == 1) && (cmp_id == 1))
        {
            break; //sensor schickt zwei mal dasselbe, entweder error oder kein sensor
        }
    }



    return result;

} */