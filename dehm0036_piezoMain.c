/* 
 * File:   dehm0036_piezoMain.c
 * Author: owenj
 *
 * Created on March 24, 2024, 12:38 PM
 */

#include "xc.h"
#include "stdint.h"
#include "dehm0036_piezo_v2.h"

// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
#pragma config ICS = PGx1          // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF        // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF          // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF           // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF        // JTAG Port Enable (JTAG port is disabled)


// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI       // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF       // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON       // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
#pragma config FCKSM = CSECME      // Clock Switching and Monitor (Clock switching is enabled, 
                                       // Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL

//initializing the pic24 microcontroller

void pic24_init() {
    CLKDIVbits.RCDIV = 0;  //clock to 16
    AD1PCFG = 0xffff; //all pins digital
}

void delay_ms(unsigned int ms) {
    while(ms-- > 0) {
        asm("repeat #15998");
        asm("nop");
    }
}

int main() {
    pic24_init();
    initTimer2();
    setTone(5999);
    
    // for testing the Piezo Buzzer
    while(1) {
        
       setTone(5999);
       piezoOn();
       delay_ms(250);
       piezoOff();
       delay_ms(50);
       
       setTone(2999);
       
       piezoOn();
       delay_ms(250);
       piezoOff();
       delay_ms(1000);
       
       // down in tone
       for (int i = 0; i < 20; i++) {
           setTone(3500 + (i * 200));
           
           piezoOn();
           delay_ms(100);
           
           piezoOff();
           delay_ms(100);
       }
       delay_ms(1000);
    }
    return 0;
}
