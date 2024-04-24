/* 
 * File:   thom8294_test_LED.h
 * Author: jdtho
 *
 * Created on April 19, 2024, 11:53 AM
 */

#ifndef THOM8294_TEST_LED_H
#define	THOM8294_TEST_LED_H

#define PERIOD 5

    void write_0(void);
    void write_1(void);
    void delay_100micro(void);
    void delay_1milli(void);
    void initTimer3(void);
    void startGameTimer3(int durationOfGame);
    void endGameTimer3(void);
    void writeColor(int r, int g, int B);
    
#ifdef	__cplusplus
}
#endif

#endif	/* THOM8294_TEST_LED_H */

