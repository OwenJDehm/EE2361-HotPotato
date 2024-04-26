/*
 * Code by Owen Dehm and Robert Chandler
 * File Purpose: This is the header file, the header file contains all the 
 * the function declarations needed to be used in the main file. This file 
 * solely contains the functions that are used to control the step motor.
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

