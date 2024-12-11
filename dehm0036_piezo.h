/* 
 * File:   dehm0036_piezo.h
 * Author: owenj
 *
 * Created on March 24, 2024, 12:21 PM
 */

#ifndef DEHM0036_PIEZO_H
#define	DEHM0036_PIEZO_H

#ifdef	__cplusplus
extern "C" {
#endif

    void initPiezo();
    void initTimer2();
    void piezoOff();
    void piezoOn();
    void setTone(int tone);


#ifdef	__cplusplus
}
#endif

#endif	/* DEHM0036_PIEZO_H */

