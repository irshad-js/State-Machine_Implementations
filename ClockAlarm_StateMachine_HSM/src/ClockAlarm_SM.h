/*.$file${HSM::../src::ClockAlarm_SM.h} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*
* Model: StateMachine_ClockAlarm.qm
* File:  ${HSM::../src::ClockAlarm_SM.h}
*
* This code has been generated by QM 5.1.1 <www.state-machine.com/qm/>.
* DO NOT EDIT THIS FILE MANUALLY. All your changes will be lost.
*
* This program is open source software: you can redistribute it and/or
* modify it under the terms of the GNU General Public License as published
* by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
* or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
* for more details.
*/
/*.$endhead${HSM::../src::ClockAlarm_SM.h} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
#ifndef CLOCK_H
#define CLOCK_H
#include "qpn.h"
#include "csrc/u8g2.h"
#include<kernel.h>
#include <stdio.h>

#define SecondsInDay 86400000
#define INITIAL_CURRENT_TIME (13UL*60UL*60UL*1000UL)+(45*60*1000)+(45*1000)
#define INITIAL_ALARM_TIME (13UL*60UL*60UL*1000UL)+(46*60*1000)+(00*1000)

enum ClockAlarm_Signals{
    SET_SIG= Q_USER_SIG,
    OK_SIG,
    ALARM_SIG,
    TICK_SIG,
    MAX_SIG

};

enum Alarm_Status{
    ALARM_OFF,
    ALARM_ON
};

/*.$declare${HSM::SuperClass_Qhsm_Clock} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
extern QHsm * const SuperClass_Qhsm_Clock;
/*.$enddecl${HSM::SuperClass_Qhsm_Clock} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*.$declare${HSM::Clock_Alarm_Constructor} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*.${HSM::Clock_Alarm_Constructor} .........................................*/
void Clock_Alarm_Constructor(void);
/*.$enddecl${HSM::Clock_Alarm_Constructor} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

extern uint32_t milliSecondCounter;

void MilliSecondInterrupt_Cb(struct k_timer * Handle);

void RefreshDisplay(char * FirstLine,char * SecondLine,char * ThirdLine);

#define Offset 20

#endif