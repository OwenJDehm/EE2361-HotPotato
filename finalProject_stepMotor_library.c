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

/* Global Variables
 */
int step_delay;             // speed of the motor
int direction;    // motor direction
int step_number;        // which step the motor is on
unsigned long int last_step_time;    // time in micros seconds of the last step taken
int number_of_steps;    // total number of steps for the motor
volatile int overflow;      //timer overflow


/* This function sets up the stepper motor, it configures the stepper
 * motor to RB0-RB3 and sets the default period, direction, and position.
 */
void stepMotor_init(int num){
    // Configure the pins to output
    TRISBbits.TRISB4 = 0;
    TRISBbits.TRISB5 = 0;
    TRISBbits.TRISB2 = 0;
    TRISBbits.TRISB3 = 0;
    //Set the internal global variables
    direction = 0;
    number_of_steps = num;
    last_step_time = 0;
    step_number = 0;
    // Configure the timer
    
}

/* Set the desired speed of the motor. The units for the speed
 * are in revolutions per minute
 */
void stepMotor_setSpeed(long int speed){
    step_delay = 60L * 1000L * 1000L / number_of_steps / speed;
}

/* This function sets the movement of the stepper motor with the
 * intended speed and direction that was specified earlier
 */
void stepMotor_movement(int steps){
    int amount;
    steps > 0 ? amount = steps : amount = -1* steps;
    
    if (steps > 0)
        direction = 1;
    else
        direction = 0;
    
    for(int i = amount; i > 0; i--){
        // move only if time appropriate delay has passed
        if(TMR + (PR + 1)*overflow - last_step_time > step_delay){
            last_step_time = TMR + (PR + 1)*overflow;
        
            if (direction){
                step_number++;
                step_number %= number_of_steps;
            }
            else {
                step_number--;
                step_number = (number_of_steps + step_number) % number_of_steps;
            }
            
            stepMotor(step_number % 4);
        }
        else{
            continue;
        }
    }
}

/*  This function moves the motor forward or backwards
 */
void stepMotor(int this_step){
    switch(this_step) {
        case 0:
            LATB |= 0x0014;
            break;
        case 1:
            LATB |= 0x0018;
            break;
        case 2:
            LATB |= 0x0028;
            break;
        case 3:
            LATB |= 0x0024;
            break;
    }
}

/* This function uses inline assembly code to get a precise delay of
 * 1ms. That delay is then repeated the specified number of times to 
 * achieve an user specified delay
 */
void delay_mus(unsigned int mus){
    while (mus-- > 0) {
        asm("repeat #14");
        asm("nop");
    }
}