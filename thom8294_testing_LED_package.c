/*
 * File:   thom8294_testing_LED_package.c
 * Author: Maverick Plsek
 *
 * Created on April 19, 2024, 1:14 PM
 */


#include "xc.h"
#include "stdint.h"
#include "thom8294_test_LED.h"

//maxValue determines the length of the LED cycle. it should be set to a random value
//within a certain range, to sync with the random length of the game
volatile unsigned int counter = 0;

void initTimer3(void) {// Configure Timer3
    T3CONbits.TON = 0;      // Timer 3 off
    T3CONbits.TCS = 0;      // internal clock
    
    T3CON = 0;                  // Clear Timer3 control register
    T3CONbits.TCKPS = 0b11;     // Set prescaler to 1:256 , PR3 62499 = 1 second
    TMR3 = 0;       // Clear Timer3 counter
}

void startGameTimer3(int durationOfGame){
    unsigned int periodCalculator = ((durationOfGame / 255.0) / (0.0000000625 * 256)) - 1; //This formula calculates the PR3 needed in order to update the LED gradient given any valid durationOfGame (15-60 seconds).
    PR3 = periodCalculator; //This rounding could lead to a +- .5 max error on the PR3 calculation, however this error will only lead the game to go on for a very very short amount of time longer or shorter than desired.
    TMR3 = 0;
    IEC0bits.T3IE = 1; //Timer 3 interrupt enabled
    T3CONbits.TON = 1; //Timer 3 on
    while (counter < 255); // wait here while interrupt handles the shifting from green to red
}

void endGameTimer3(void){
    IEC0bits.T3IE = 0; // disable interrupt
    T3CONbits.TON = 0; // turn timer off
    counter = 0;
}

void __attribute__((__interrupt__,__auto_psv__)) _T3Interrupt(void)
{
    IFS0bits.T3IF = 0;
    if (counter >= 0 && counter < 64) {
        if ((counter % 16 == 0) || (counter % 16 == 1)) {
            writeColor(0 + counter, 255 - counter, 0);
        }
        else {
            writeColor(0,0,0);
        }
    }
    else if (counter >= 64 && counter < 128) {
        if ((counter % 8 == 0) || (counter % 8 == 1)) {
            writeColor(0 + counter, 255 - counter, 0);
        }
        else {
            writeColor(0,0,0);
        }
    }
    else if (counter >= 128 && counter < 192) {
        if ((counter % 4 == 0) || (counter % 4 == 1)) {
            writeColor(0 + counter, 255 - counter, 0);
        }
        else {
            writeColor(0,0,0);
        } 
    }
    else if (counter >= 192 && counter < 256) {
        if (counter % 2 == 0) {
            writeColor(0 + counter, 255 - counter, 0);
        }
        else {
            writeColor(0,0,0);
        }
    }
    counter++;
} 
        
void writeColor(int r, int g, int b)
    {
        // r values
        int i = 8;
        while (i > 0)
        {
            if (((r >> (i - 1)) & 0b00000001) == 1)
            {
                write_1();
            }
            else
            {
                write_0();
            }
            i--;
        }
        // g values
        int j = 8;
        while (j > 0)
        {
            if (((g >> (j - 1)) & 0b00000001) == 1)
            {
                write_1();
            }
            else
            {
                write_0();
            }
            j--;
        }
        int k = 8;
        while (k > 0)
        {
            if (((b >> (k - 1)) & 0b00000001) == 1)
            {
                write_1();
            }
            else
            {
                write_0();
            }
            k--;
        }
    }
