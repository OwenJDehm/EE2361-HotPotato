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
    void setMovement(int step);
    void stopMotor();
    void startMotor();



#ifdef	__cplusplus
}
#endif

#endif	/* DEHM0036_STEPPERMOTOR_H */

