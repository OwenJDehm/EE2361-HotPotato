/* Date: April 26th, 2024
 * Name: Robert Chandler, Owen Dehm, Joe Thomas, Maverick Plsek
 * Course number: EE 2361
 * Term: Spring 2024
 * Lab/assignment number: Final Project - Hot Potato Game
 * Created on March 24, 2024, 3:14 PM
 * 
 * File Purpose: This is the source file,the source file contains all 
 * of the function definitions that are used in the main file. This source
 * file uses the buzzer, step motor, and led librarys to create our "Hot Potato" game.
 */


#include "xc.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * This function initializes timer 4 by setting the pre-scalar to 1:1 and the max PR 
 * of 65535. The purpose of utilizing this timer is for the sole purpose of our random number generator. 
 */
void initTimer4(void){
    T4CONbits.TON = 0;      // Timer 3 off
    T4CONbits.TCS = 0;      // internal clock
    
    T4CON = 0;                  // Clear Timer3 control register
    T4CONbits.TCKPS = 0b00;     // Set prescaler to 1:1
    PR4 = 65535;
    TMR4 = 0;       // Clear Timer3 counter
    T4CONbits.TON = 1;
}

/*
 * This function initializes the PIC24FJ64GA002.
 * It sets the clock frequency to 16 MHz and all of the pins to digital
 * It also designates RB8 as an output and initializes it to 1. This specific pin is for the button and will ground when button is pressed.
 * Finally it sets RA0 to output and sets to low for the Led
 */
void pic24_init(void){
    _RCDIV = 0; //set frequency to 16 Mhz
    AD1PCFG = 0xffff; //set all pins digital
    TRISBbits.TRISB8 = 0; //This line set RB8 to an output
    LATBbits.LATB8 = 1; //This line sets the pin the button is connected to (RB8) to high. when button is pressed it will go low signifying start
    TRISAbits.TRISA0 = 0; // set RA0 to output (For the LED lights)
    LATAbits.LATA0 = 0; // set RA0 to Low (FOR the LED lights)
}

/*
 * This function initializes the hot potato game by calling all initialization functions from the
 * other component libraries.
 */
void initGame(void){
    pic24_init();
    stepperMotor_init();
    initTimer2();
    initTimer3();
    initTimer4();
}

/*
 * Function: startGame
 * Starts the game once the button is pressed.
 * Plays a start chime, sets game duration, and handles game actions.
 * Vibrates the step motor, flashes LEDs, and plays alternating tones when the potato is "hot".
 * durationOfGame: Integer representing the length of the game in seconds.
 */
void startGame(int durationOfGame){
    //set tone 2000-5000
    piezoOn();      //
    delay_ms(250);   //
    setTone(2000);      //
    delay_ms(250);   // Implement a start chime that starts after button is pressed to let players know game is beginning
    setTone(3000);     // (Time For the game itself has not started yet will start after chime)
    delay_ms(250);  // (1 is just placeholder right now).
    setTone(4000);     //
    delay_ms(250);  //
    setTone(0);   //
    piezoOff();    //
    
    /*
     * Need to implement lights changing as time hits randomized time
     * Need to be a smooth transition given any TOG (Time of game)
     * (For loop with cleverness and formula?)
     */
    //start time of game //I re did the LCD c file utilizing the interrupt to change the rate of transition from green to red based off a PR3 calculation.
    writeColor(0,255,0); //begin with light completely green
    startGameTimer3(durationOfGame);
    endGameTimer3();
    
    /*
     * After above means times up and potato is "Hot".
     * Need to make step-Motor vibrate speed really high (1200-12000) steps low= (10-20),
     * LED's flash red,
     * piezo alternating between 2 tones (might need to implement 4 second delay into this instead of after function)
     * [will still act the same just need to be able to flip the tone...cant do that while in delay mode]
     */
    stepSpeed(1800);
    setMovement(10000);
    startMotor();
    piezoOn();
    for (int i = 0; i < 25; i++){
        writeColor(0,0,0);
        setTone(3000);
        delay_ms(100);
        writeColor(255,0,0);
        setTone(5000);
        delay_ms(100);
    }
}

/*
 * This function ends the game by resetting all the componenets of the game. Intended to be called after start game finishes.
 */
void endGame(void){
    piezoOff();
    setTone(0);
    writeColor(0,0,0);
    stopMotor();
}

/*
 * This function randomly generates and int between the range of 15-60. This random number is intended to be used as 
 * the length of a single game in seconds. !!Timer 4 must be initialized in order for the numbers to be random!!
 */
int time_of_Game_Generator(void){
    srand(TMR4);
    return (rand() % (60 - 15 + 1)) + 15; //Generates a random number between 15-60;
}
