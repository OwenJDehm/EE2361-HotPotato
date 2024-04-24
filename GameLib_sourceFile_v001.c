/*
 * File:   GameLib_sourceFile_v001.c
 * Author: maverickplsek
 *
 * Created on March 24, 2024, 12:16 PM
 */


#include "xc.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void initTimer4(void){
    T4CONbits.TON = 0;      // Timer 3 off
    T4CONbits.TCS = 0;      // internal clock
    
    T4CON = 0;                  // Clear Timer3 control register
    T4CONbits.TCKPS = 0b00;     // Set prescaler to 1:1
    PR4 = 65535;
    TMR4 = 0;       // Clear Timer3 counter
    T4CONbits.TON = 1;
}

//This function initializes the pic24
void pic24_init(void){
    _RCDIV = 0; //set frequency to 16 Mhz
    AD1PCFG = 0xffff; //set all pins digital
    TRISBbits.TRISB8 = 0; //This line set RB8 to an output
    LATBbits.LATB8 = 1; //This line sets the pin the button is connected to (RB8) to high. when button is pressed it will go low signifying start
    TRISAbits.TRISA0 = 0; // set RA0 to output (For the LED lights)
    LATAbits.LATA0 = 0; // set RA0 to Low (FOR the LED lights)
}

//This function initializes all init functions from group.
void initGame(void){
    pic24_init();
    stepperMotor_init();
    initTimer2();
    initTimer3();
    initTimer4();
}

//This function is the game, will be called once button is pressed
void startGame(int durationOfGame){
    //set tone 2000-5000, maybe add a 0 if it doesn't work
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

//This function will reset all components of the game to prepare for another start
void endGame(void){
    piezoOff();
    setTone(0);
    writeColor(0,0,0);
    stopMotor();
}

//This function causes a delay, will be used at end of game.
void delay_In_Seconds(int seconds){
    while (seconds-- > 0) {
        for (int i=0; i < 1000;i++){
            asm("repeat #15998"); //1 msec delay
            asm("nop");
        }
    }
}

//This function will randomly generated a number between 15-60 and return it as an int
//The number returned will represent the length of the game, in seconds, before the potato becomes "hot"
int time_of_Game_Generator(void){
    srand(TMR4);
    return (rand() % (60 - 15 + 1)) + 15; //Generates a random number between 15-60;
}