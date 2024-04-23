/* 
 * File:   dehm0036_stepperMotor.h
 * Author: owenj
 *
 * Created on April 12, 2024, 6:23 PM
 */

#ifndef DEHM0036_STEPPERMOTOR_H
#define	DEHM0036_STEPPERMOTOR_H

#ifdef	__cplusplus
extern "C" {
#endif

    void stepperMotor_init();
    void stepSpeed(int speed);
    void init_timer1();
    void stepMotor(int step);
    void stopMotor();



#ifdef	__cplusplus
}
#endif

#endif	/* DEHM0036_STEPPERMOTOR_H */

