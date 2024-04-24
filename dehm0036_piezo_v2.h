/* 
 * File:   dehm0036_piezo_v2.h
 * Author: owenj
 *
 * Created on April 11, 2024, 2:25 PM
 */

#ifndef DEHM0036_PIEZO_V2_H
#define	DEHM0036_PIEZO_V2_H

#ifdef	__cplusplus
extern "C" {
#endif

    void initTimer2();
    void piezoOn();
    void piezoOff();
    void setTone(int value);


#ifdef	__cplusplus
}
#endif

#endif	/* DEHM0036_PIEZO_V2_H */

