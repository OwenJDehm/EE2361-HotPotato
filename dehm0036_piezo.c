#include "xc.h"
#include "stdint.h"

#define BuzzerPin LATAbits.LATA4

#define F 20 // example value for the tone F to be put in the PR2
#define C 15 // example value for the tone C to be put in the PR2

volatile uint8_t state = 0; // starts off, we will have to toggle this to on using piezoOn()

void initPiezo(void) {
    //use pin  B4
    TRISBbits.TRISB4 = 0;//output

    T3CON = 0;
    T3CONbits.TCKPS = 0B01;
    TMR3 = 0;
    PR3 = 40000 -1;
    T3CONbits.TON = 1;
    
}

void initTimer2(void) {
    T2CONbits.TON = 0;      // Timer 2 off
    T2CONbits.TCS = 0;      // internal clock
    T2CONbits.TCKPS = 0b00; // 1:1 Pre-scalar
    
    OC1CONbits.OCM = 0b110;     // PWM mode without pin
    OC1CONbits.OCTSEL = 0;      // Timer 2 as output compare
    OC1RS = 0;      // duty cycle register
    OC1R = 0;       // duty cycle register
    
    TMR2 = 0;       // clear Timer 2
    T2CONbits.TON = 1;      // Timer 2 on
    IEC0bits.T2IE = 1;      // Timer 2 interrupt enabled
}

int current = 0;

void __attribute__((__interrupt__, no_auto_psv)) _T2Interrupt(void) {
    TMR2 = 0; // resets timer 2
    
    if (state == 1) {
        BuzzerPin = !BuzzerPin; // toggle buzzer pin
    }
    
    IFS0bits.T2IF = 0; // clear Timer 2 interrupt flag
}

/* This function sets the Piezo Buzzer to off, we are doing this by setting the pin to low and making 
   the state = 0, when the state = 0, the pin does not toggle within the T2Interrupt, so it will remain
   completely off */
void piezoOff(void) {
    BuzzerPin = 0; // the pin is off
    state = 0; // will not oscillate within the timer interrupt
}

/* This function changes the state from 0 to 1, so the Piezo Buzzer can toggle high to low using the
   T2Interrupt, which is how sound is produced */
void piezoOn(void) {
    state = 1; // will oscillate within the timer interrupt
}

// used for setting the length of time for the PR2, sets the tone
void setTone(int tone) {
    PR2 = tone;
}
