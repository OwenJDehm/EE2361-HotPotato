/* Date: April 26th, 2024
 * Name: Robert Chandler, Owen Dehm, Joe Thomas, Maverick Plsek
 * Student ID number: 5791316
 * Course number: EE 2361
 * Term: Spring 2024
 * Lab/assignment number: Final Project - Hot Potato Game
 * Created on March 24, 2024, 12:22 PM
 * 
 * File Purpose: This is the source file, the source file contains all 
 * of the function definitions that are used in the main file. This source
 * file is only for the step motor and nothing else relating to the 
 * Hot Potato Game Project.
 */

#include "xc.h"
#include "stdint.h"

// Global Variables
volatile int stepsRemaining = 0;        // 
volatile int currentStep = 0;
volatile int stepSequence = 1;


void stepperMotor_init() {
    // set pins to output (RP2 through RP5)
    TRISBbits.TRISB2 = 0;
    TRISBbits.TRISB3 = 0;
    TRISBbits.TRISB4 = 0;
    TRISBbits.TRISB5 = 0;
    
    // make sure none of the pins are on
    LATBbits.LATB2 = 0;
    LATBbits.LATB3 = 0;
    LATBbits.LATB4 = 0;
    LATBbits.LATB5 = 0;

    // Set up Timer 1
    T1CON = 0x0000;     // stop timer 1 and reset control register
    TMR1 = 0;           // clear timer 1
    PR1 = 15999;
    IFS0bits.T1IF = 0;  // clear interrupt flag
    IEC0bits.T1IE = 1;  // enable interrupt
    T1CONbits.TCKPS = 0b01; // 1 pre-scalar, may need to lower
}

void stepSpeed(int speed) {
    if (speed == 0) {
        T1CONbits.TON = 0; // stop timer 1
    }
    else {
        int period = 40000000 / (256 * speed);
        // not including a cap speed so we can over speed the motor to make it rumble
        // from the gear not "snapping" to the inductors
        PR1 = period;
        T1CONbits.TON = 1; // resume timer 1
    }
}

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void) {
    IFS0bits.T1IF = 0; // clear interrupt
    // will use masking and bit shifting to clear and set to next steps
    // going forward
    
    switch(stepSequence) {
        case 0:
            LATBbits.LATB2 = 1;
            LATBbits.LATB3 = 0;
            LATBbits.LATB4 = 1;
            LATBbits.LATB5 = 0;   
        break;
        case 1:
            LATBbits.LATB2 = 0;
            LATBbits.LATB3 = 1;
            LATBbits.LATB4 = 1;
            LATBbits.LATB5 = 0;  
        break;
        case 2:
            LATBbits.LATB2 = 0;
            LATBbits.LATB3 = 1;
            LATBbits.LATB4 = 0;
            LATBbits.LATB5 = 1;             
        break;
        case 3:
            LATBbits.LATB2 = 1;
            LATBbits.LATB3 = 0;
            LATBbits.LATB4 = 0;
            LATBbits.LATB5 = 1;             
        break;
    }
    
    if (stepsRemaining != 0) {
        if (stepsRemaining > 0) {
            stepSequence = (stepSequence + 1) % 4;
            stepsRemaining--;
        }
        else {
            stepSequence = (stepSequence + 3) % 4;
            stepsRemaining++;
        }
    }
}

void setMovement(int step) {
    stepsRemaining = step;     // set the step count
}

void stopMotor(){
    T1CONbits.TON = 0;
}

void startMotor(){
    T1CONbits.TON = 1;
}
