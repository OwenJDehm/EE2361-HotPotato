/* Date: April 26th, 2024
 * Name: Robert Chandler, Owen Dehm, Joe Thomas, Maverick Plsek
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
volatile int stepsRemaining;        // The remaining amount of steps for the motor to move
volatile int stepSequence;          // The step sequence it is currently on (0-3)

/* This function sets up the stepper motor, it configures the stepper
 * motor to RB2-RB5. Additionally, set up timer 1 to be used with the motor
 * by setting PR1 to its default value. Turning on the interrupt and setting
 * the prescaclar to 1. Finally, the function sets the default values of 
 * the global variables that are used inside the interrupt service routine.
 */
void stepperMotor_init() {
    // set pins to output (RB2 through RB5)
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
    PR1 = 15999;        // default value
    IFS0bits.T1IF = 0;  // clear interrupt flag
    IEC0bits.T1IE = 1;  // enable interrupt
    T1CONbits.TCKPS = 0b01; // 1 pre-scalar

    // Default values
    stepsRemaining = 13000;
    stepSequence = 1;
}

/* Set the desired speed of the motor. The speed of the motor is determined by the 
 * period of the Timer 1. The function sets the period of the timer with the desired
 * speed parameter. 
 */
void stepSpeed(int speed) {
    int period = 40000000 / (256 * speed);
    // not including a cap speed so we can over speed the motor to make it rumble
    // from the gear not "snapping" to the inductors
    PR1 = period;
    T1CONbits.TON = 1; // resume timer 1
}

/* This is the interrupt service routine for Timer 1. At each timer interrupt,
 * the function executes. This function is responsible for "stepping" the 
 * motor which means that the motor is incremented by one.
 */
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void) {
    IFS0bits.T1IF = 0; // clear interrupt
    
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

/* Set the desired step count. Makes the global variable the desired parameter
 * value.
 */
void setMovement(int step) {
    stepsRemaining = step;     // set the step count
}

/* This function stops the motor. The function is very simple and only turns the 
 * timer off so the interrupt is not able to be run. 
 */
void stopMotor(){
    T1CONbits.TON = 0;
}

/* This function starts the motor. The function is very simple and only turns the 
 * timer on so the interrupt is able to run on timer overflows.
 */
void startMotor(){
    T1CONbits.TON = 1;
}
