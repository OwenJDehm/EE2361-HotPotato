/* Date: April 26th, 2024
 * Name: Robert Chandler, Owen Dehm, Joe Thomas, Maverick Plsek
 * Course number: EE 2361
 * Term: Spring 2024
 * Lab/assignment number: Final Project - Hot Potato Game
 * Created on March 24th, 2024, 12:22 PM
 * 
 * File Purpose: This is the source file, the source file contains all 
 * of the function definitions that are used in the main file. This source
 * file is only for the step motor and nothing else relating to the 
 * Hot Potato Game Project.
 */

#include "xc.h"
#include "finalProject_stepMotor_library.h"

// Global Variables
int step_delay;             // speed of the motor
int direction;    // motor direction
int step_number;        // which step the motor is on
unsigned long int last_step_time;    // time in micros seconds of the last step taken
int number_of_steps;    // total number of steps for the motor to make one revolution
volatile int overflow;      //timer overflow

/* This is the interrupt service routine for the timer 1. It keeps track of
 * the timer overflows to correctly compute the correct time.
 */
void __attribute__((__interrupt__,__auto_psv__)) _T1Interrupt(){
    _T1IF = 0;
    overflow++;
}

/* This function sets up the stepper motor, it configures the stepper
 * motor to RB0-RB3 and sets the default direction, number of steps,
 * last step time, and current step number. The function also configures
 * timer 1 to have the longest delay with the smallest prescalar for
 * increased accuracy
 */
void stepMotor_init(){
    // Configure the pins to output
    TRISBbits.TRISB4 = 0;
    TRISBbits.TRISB5 = 0;
    TRISBbits.TRISB2 = 0;
    TRISBbits.TRISB3 = 0;
    //Set the internal global variables
    direction = 0;
    number_of_steps = 4076;
    last_step_time = 0;
    step_number = 0;
    // Configure the timer
    TMR1 = 0;
    T1CON = 0;
    T1CONbits.TCKPS = 0;
    PR1 = 65535;
    _T1IF = 0;
    _T1IE = 1;
    T1CONbits.TON = 1;
}

/* Set the desired speed of the motor. The units for the speed
 * are in revolutions per minute. The units for the step delay is in
 * microseconds.
 */
void stepMotor_setSpeed(long int speed){
    step_delay = 60L * 1000L * 1000L / number_of_steps / speed;
}

/* This function sets the movement of the stepper motor by the intended
 * number of steps. If the number of steps to take is a negative number,
 * the motor will move in the opposite direction. If the number is positive,
 * it will move the desired number of steps in the forward direction.
 */
void stepMotor_movement(int steps){
    int amount;
              
    if (steps > 0){              //compute the direction of rotation & magnitude of the number of steps
        direction = 1;
        amount = steps;
    }
    else {
        direction = 0;
        amount = -1*steps;
    }
    
    for(int i = amount; i > 0; i--){            // loop for the intended amount of steps
        // move only if time appropriate delay has passed
        while((TMR1 + (PR1 + 1)*overflow)*0.0625 - last_step_time < step_delay);      
        last_step_time = (TMR1 + (PR1 + 1)*overflow)*0.0625;      //step will be taken, update the last step time to current time
        
        if (direction){                 // if forward direction, increase the current step index and make sure its within the bounds
            step_number++;
            step_number %= number_of_steps;
        }
        else {                          // if backwards direction, decrease the current step index and make sure its within the bounds
            step_number--;
            step_number = (number_of_steps + step_number) % number_of_steps;
        }
            
        stepMotor(step_number % 4);        // step the motor to the next step
        
    }
}

/*  This function moves the motor forward or backwards based on the step that was
 * inputed. The step that was inputed is the next step to move to based on the 
 * internal components of the motor. This function is not designed to be used
 * outside of the library but it is capable of being used.
 */
void stepMotor(int this_step){
    switch(this_step) {
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
}

/* This function uses inline assembly code to get a precise delay of
 * 1ms. That delay is then repeated the specified number of times to 
 * achieve an user specified delay
 */
void delay_ms(unsigned int ms){
    while (ms-- > 0) {
        asm("repeat #15998");
        asm("nop");
    }
}
