/*
 * File:   thom8294_testing_LED_package.c
 * Author: jdtho
 *
 * Created on April 19, 2024, 11:54 AM
 */


#include "xc.h"
#include "stdint.h"

void initTimer3(void) {// Configure Timer3
    T3CONbits.TON = 0;      // Timer 3 off
    T3CONbits.TCS = 0;      // internal clock
    
    T3CON = 0;                  // Clear Timer3 control register
    T3CONbits.TCKPS = 0b01;     // Set prescaler to 1:8
    TMR3 = 0;       // Clear Timer3 counter
    
    T3CONbits.TON = 1;      // Timer 3 on
    IEC0bits.T3IE = 1;      // Timer 3 interrupt enabled
}
//maxValue determines the length of the LED cycle. it should be set to a random value
//within a certain range, to sync with the random length of the game
volatile unsigned int counter = 0;
volatile unsigned int maxValue = 100; // # random value to determine time of the flashing. 
volatile unsigned int idx = 0;

void __attribute__((__interrupt__,__auto_psv__)) _T3Interrupt(void)
{
    IFS0bits.T3IF = 0;
    counter++;
}  

void LED_cycle(void){
    int intervals = maxValue /(256);
        if(counter>intervals){
            idx += 1;
            counter = 0;
        }
        if(idx<256){
            int red = idx;
            int grn = 256 - idx;
        
            writeColor(red, grn, 0);
            delay(50);
            writeColor(0,0,0);
            delay(256 - red);
        }
}
        
 
