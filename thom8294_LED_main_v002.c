


#include "xc.h"
#include "thom8294_LED_asm_v002.h"
#include "stdint.h"

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
#pragma config FNOSC = FRCPLL      // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))


void setup(void) {
   
    CLKDIVbits.RCDIV = 0;       //Set RCDIV=1:1 (default 2:1) 32MHz or FCY/2=16M
   
    AD1PCFG = 0xffff;            //sets all pins to digital I/O
    TRISAbits.TRISA0 = 0;         //set RA0 to output,
    LATAbits.LATA0 = 0;               //Set all of port A to HIGH
}
void initTimer3(void) {// Configure Timer3
    T3CONbits.TON = 0;      // Timer 3 off
    T3CONbits.TCS = 0;      // internal clock
    
    T3CON = 0;                  // Clear Timer3 control register
    T3CONbits.TCKPS = 0b01;     // Set prescaler to 1:8
    TMR3 = 0;       // Clear Timer3 counter
    
    T3CONbits.TON = 1;      // Timer 3 on
    IEC0bits.T3IE = 1;      // Timer 3 interrupt enabled
}
volatile unsigned int counter = 0;
volatile unsigned int maxValue = 100; // # random value to determine time of the flashing. 
volatile unsigned int idx = 0;

void __attribute__((__interrupt__,__auto_psv__)) _T3Interrupt(void)
{
    IFS0bits.T3IF = 0;
    counter++;
}   

int main(void) {
    setup();
    initTimer3(); // Initialize Timer 3
    while(1){
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
}
