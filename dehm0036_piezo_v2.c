#include "xc.h"
#include "stdint.h"

volatile uint8_t state = 0;

/* Initialize the timer 2 to utilize the PWM and use output compare 1, the timer uses a 1 to 1 prescalar
   The PWM is also being set to use pin RP11 as that is the pin connected to the Piezo Buzzer.*/
void initTimer2(void) {
    T2CON = 0;              // stop timer 2
    T2CONbits.TCS = 0;      // using external clock
    T2CONbits.TCKPS = 0b00;     // 1:1 pre-scaler
    
    // PWM output compare 1
    OC1CON = 0;                 // Output Compare 1 off
    OC1CONbits.OCM = 0b110;     // PWM uses OC1
    OC1CONbits.OCTSEL = 0;      // Timer 2 for Output Compare 1
    
    OC1RS = 0;      // no starting duty cycle
    OC1R = 0;       // current duty cycle
    
    TMR2 = 0;           // clear timer 2
    PR2 = 0xFFFF;       // base starting period for Timer 2
    T2CONbits.TON = 1;  // start timer 2
    
    // setting it to RP11
    __builtin_write_OSCCONL(OSCCON & ~(1<<6));
    
    RPOR5bits.RP11R = 18;
    __builtin_write_OSCCONL(OSCCON | (1<<6));
}

// sets the duty cycle to 0% so the buzzer is off
void piezoOff(void) {
    OC1RS = 0;
    state = 0;
}

// toggles the state on whether the piezo is on if previously off
// sets the duty cycle to 50% for audible output
void piezoOn(void) {
    if (state == 0) {
        OC1RS = (PR2 + 1) / 2;
        state = 1;
    }
}

// changes the frequency of the PWM and adjust the period to change the sound
void setTone(int value) {
    PR2 = value;
    if (state == 1) {
        OC1RS = (PR2 + 1) / 2;
    }
}

