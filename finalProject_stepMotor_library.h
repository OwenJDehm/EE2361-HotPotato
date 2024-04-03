/* Date: April 26th, 2024
 * Name: Robert Chandler, Owen Dehm, Joe Thomas, Maverick Plsek
 * Student ID number: 5791316
 * Course number: EE 2361
 * Term: Spring 2024
 * Lab/assignment number: Final Project - Hot Potato Game
 * Created on March 24, 2024, 12:21 PM
 * 
 * File Purpose: This is the header file, the header file contains all the 
 * the function declarations needed to be used in the main file. This file 
 * solely contains the functions that are used to control the step motor.
 */

#ifndef FINALPROJECT_STEPMOTOR_LIBRARY_H
#define	FINALPROJECT_STEPMOTOR_LIBRARY_H

#ifdef	__cplusplus
extern "C" {
#endif
    void stepMotor_init(int num);
    void stepMotor_setSpeed(long int speed);
    void stepMotor_movement(int steps);
    void stepMotor(int this_step);
    void delay_mus(unsigned int mus);
#ifdef	__cplusplus
}
#endif

#endif	/* FINALPROJECT_STEPMOTOR_LIBRARY_H */

