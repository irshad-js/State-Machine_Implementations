/*.$file${HSM::../src::ClockAlarm_SM.c} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*
* Model: StateMachine_ClockAlarm.qm
* File:  ${HSM::../src::ClockAlarm_SM.c}
*
* This code has been generated by QM 5.1.1 <www.state-machine.com/qm/>.
* DO NOT EDIT SECTIONS BETWEEN THE COMMENTS "$...vvv".."$end...^^^".
* All your changes in these sections will be lost.
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
/*.$endhead${HSM::../src::ClockAlarm_SM.c} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
#include "ClockAlarm_SM.h"
char DisplayStringFirstLine[30];
char DisplayStringSecondLine[30];
char DisplayStringThirdLine[30];
u8g2_t u8g2; // a structure which will contain all the data for one display


/*.$declare${HSM::Clock_Alarm} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*.${HSM::Clock_Alarm} .....................................................*/
typedef struct Clock_Alarm {
/* protected: */
    QHsm super;

/* private: */
    uint32_t alarmTime;
    uint8_t alarmStatus;
    uint8_t timeout_AlarmMessage;
    uint8_t timeout_AlarmMain;

/* private state histories */
    QStateHandler hist_MainClock;
} Clock_Alarm;

/* public: */
static uint32_t Clock_Alarm_get_current_time(void);
static void Clock_Alarm_update_current_time(void);
static void Clock_Alarm_set_current_time(uint32_t new_current_time);
extern uint32_t Clock_Alarm_currentTime;
extern Clock_Alarm Clock_Alarm_object;

/* protected: */
static QState Clock_Alarm_initial(Clock_Alarm * const me);
static QState Clock_Alarm_MainClock(Clock_Alarm * const me);
static QState Clock_Alarm_Ticking(Clock_Alarm * const me);
static QState Clock_Alarm_SettingsParent(Clock_Alarm * const me);
static QState Clock_Alarm_SetClock(Clock_Alarm * const me);
static QState Clock_Alarm_SetHour(Clock_Alarm * const me);
static QState Clock_Alarm_SetMin(Clock_Alarm * const me);
static QState Clock_Alarm_SetAlarm(Clock_Alarm * const me);
static QState Clock_Alarm_SetHour_Alarm(Clock_Alarm * const me);
static QState Clock_Alarm_SetMin_Alarm(Clock_Alarm * const me);
static QState Clock_Alarm_Arm_Alarm(Clock_Alarm * const me);
static QState Clock_Alarm_NotifyAlarm(Clock_Alarm * const me);
static QState Clock_Alarm_MessageON(Clock_Alarm * const me);
static QState Clock_Alarm_MessageOFF(Clock_Alarm * const me);
/*.$enddecl${HSM::Clock_Alarm} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*.$skip${QP_VERSION} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*. Check for the minimum required QP version */
#if (QP_VERSION < 690U) || (QP_VERSION != ((QP_RELEASE^4294967295U) % 0x3E8U))
#error qpn version 6.9.0 or higher required
#endif
/*.$endskip${QP_VERSION} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*.$define${HSM::Clock_Alarm_Constructor} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*.${HSM::Clock_Alarm_Constructor} .........................................*/
void Clock_Alarm_Constructor(void) {
    QHsm_ctor(&Clock_Alarm_object.super,Q_STATE_CAST(&Clock_Alarm_initial));
}
/*.$enddef${HSM::Clock_Alarm_Constructor} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*.$define${HSM::Clock_Alarm} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*.${HSM::Clock_Alarm} .....................................................*/
uint32_t Clock_Alarm_currentTime;
Clock_Alarm Clock_Alarm_object;
/*.${HSM::Clock_Alarm::get_current_time} ...................................*/
static uint32_t Clock_Alarm_get_current_time(void) {
}

/*.${HSM::Clock_Alarm::update_current_time} ................................*/
static void Clock_Alarm_update_current_time(void) {
    if(++Clock_Alarm_currentTime >= SecondsInDay)
    {
        Clock_Alarm_currentTime = 0;
    }

}

/*.${HSM::Clock_Alarm::set_current_time} ...................................*/
static void Clock_Alarm_set_current_time(uint32_t new_current_time) {
    Clock_Alarm_currentTime = new_current_time;
}

/*.${HSM::Clock_Alarm::SM} .................................................*/
static QState Clock_Alarm_initial(Clock_Alarm * const me) {
    /*.${HSM::Clock_Alarm::SM::initial} */
    Clock_Alarm_set_current_time(INITIAL_CURRENT_TIME);
    me->alarmTime = INITIAL_ALARM_TIME;
    me->alarmStatus = 0;
    /* state history attributes */
    /* state history attributes */
    me->hist_MainClock = Q_STATE_CAST(&Clock_Alarm_Ticking);
    return Q_TRAN(&Clock_Alarm_Ticking);
}
/*.${HSM::Clock_Alarm::SM::MainClock} ......................................*/
static QState Clock_Alarm_MainClock(Clock_Alarm * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /*.${HSM::Clock_Alarm::SM::MainClock} */
        case Q_EXIT_SIG: {
            /* save deep history */
            me->hist_MainClock = QHsm_state(me);
            status_ = Q_HANDLED();
            break;
        }
        /*.${HSM::Clock_Alarm::SM::MainClock::ALARM} */
        case ALARM_SIG: {
            me->timeout_AlarmMain =0;
            /*.${HSM::Clock_Alarm::SM::MainClock::ALARM::[(me->alarmStatus==ALARM_ON&&(Cl~} */
            if (( me->alarmStatus == ALARM_ON && (Clock_Alarm_currentTime/1000) == (me->alarmTime/1000))) {
                status_ = Q_TRAN(&Clock_Alarm_NotifyAlarm);
            }
            else {
                status_ = Q_UNHANDLED();
            }
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status_;
}
/*.${HSM::Clock_Alarm::SM::MainClock::Ticking} .............................*/
static QState Clock_Alarm_Ticking(Clock_Alarm * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /*.${HSM::Clock_Alarm::SM::MainClock::Ticking} */
        case Q_ENTRY_SIG: {
            if(me->alarmStatus == 1){
                sprintf(DisplayStringFirstLine,"Alarm - YES");
            }
            else{
                sprintf(DisplayStringFirstLine,"Alarm - NO");
            }

            sprintf(DisplayStringSecondLine,"%02d-%02d-%02d",((Clock_Alarm_currentTime/1000U/60U/60U)%24),((Clock_Alarm_currentTime/1000U/60U)%60U),((Clock_Alarm_currentTime/1000U)%60U));
            sprintf(DisplayStringThirdLine,"State TICK");
            RefreshDisplay(&DisplayStringFirstLine,&DisplayStringSecondLine,&DisplayStringThirdLine);
            status_ = Q_HANDLED();
            break;
        }
        /*.${HSM::Clock_Alarm::SM::MainClock::Ticking::SET} */
        case SET_SIG: {
            status_ = Q_TRAN(&Clock_Alarm_SetClock);
            break;
        }
        /*.${HSM::Clock_Alarm::SM::MainClock::Ticking::OK} */
        case OK_SIG: {
            status_ = Q_TRAN(&Clock_Alarm_SetAlarm);
            break;
        }
        /*.${HSM::Clock_Alarm::SM::MainClock::Ticking::TICK} */
        case TICK_SIG: {
            if(me->alarmStatus == 1){
                sprintf(DisplayStringFirstLine,"Alarm - YES");
            }
            else{
                sprintf(DisplayStringFirstLine,"Alarm - NO");
            }

            sprintf(DisplayStringSecondLine,"%02d-%02d-%02d",((Clock_Alarm_currentTime/1000U/60U/60U)%24),((Clock_Alarm_currentTime/1000U/60U)%60U),((Clock_Alarm_currentTime/1000U)%60U));
            sprintf(DisplayStringThirdLine,"State TICK");
            RefreshDisplay(&DisplayStringFirstLine,&DisplayStringSecondLine,&DisplayStringThirdLine);
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&Clock_Alarm_MainClock);
            break;
        }
    }
    return status_;
}
/*.${HSM::Clock_Alarm::SM::MainClock::SettingsParent} ......................*/
static QState Clock_Alarm_SettingsParent(Clock_Alarm * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /*.${HSM::Clock_Alarm::SM::MainClock::SettingsParent::OK} */
        case OK_SIG: {
                        if(me->alarmStatus == 1){
                            sprintf(DisplayStringFirstLine,"Alarm - YES");
                        }
                        else{
                            sprintf(DisplayStringFirstLine,"Alarm - NO");
                        }

                        sprintf(DisplayStringSecondLine,"%02d-%02d-%02d",((Clock_Alarm_currentTime/1000U/60U/60U)%24),((Clock_Alarm_currentTime/1000U/60U)%60U),((Clock_Alarm_currentTime/1000U)%60U));
                        sprintf(DisplayStringThirdLine,"Clock Set");
                        RefreshDisplay(&DisplayStringFirstLine,&DisplayStringSecondLine,&DisplayStringThirdLine);
            status_ = Q_TRAN(&Clock_Alarm_Ticking);
            break;
        }
        default: {
            status_ = Q_SUPER(&Clock_Alarm_MainClock);
            break;
        }
    }
    return status_;
}
/*.${HSM::Clock_Alarm::SM::MainClock::SettingsParent::SetClock} ............*/
static QState Clock_Alarm_SetClock(Clock_Alarm * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /*.${HSM::Clock_Alarm::SM::MainClock::SettingsParent::SetClock::initial} */
        case Q_INIT_SIG: {
            status_ = Q_TRAN(&Clock_Alarm_SetHour);
            break;
        }
        default: {
            status_ = Q_SUPER(&Clock_Alarm_SettingsParent);
            break;
        }
    }
    return status_;
}
/*.${HSM::Clock_Alarm::SM::MainClock::SettingsParent::SetClock::SetHour} ...*/
static QState Clock_Alarm_SetHour(Clock_Alarm * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /*.${HSM::Clock_Alarm::SM::MainClock::SettingsParent::SetClock::SetHour} */
        case Q_ENTRY_SIG: {
                        if(me->alarmStatus == 1){
                            sprintf(DisplayStringFirstLine,"Alarm - YES");
                        }
                        else{
                            sprintf(DisplayStringFirstLine,"Alarm - NO");
                        }

                        sprintf(DisplayStringSecondLine,"%02d-%02d-%02d",((Clock_Alarm_currentTime/1000U/60U/60U)%24),((Clock_Alarm_currentTime/1000U/60U)%60U),((Clock_Alarm_currentTime/1000U)%60U));
                        sprintf(DisplayStringThirdLine,"Hour Set");
                        RefreshDisplay(&DisplayStringFirstLine,&DisplayStringSecondLine,&DisplayStringThirdLine);
            status_ = Q_HANDLED();
            break;
        }
        /*.${HSM::Clock_Alarm::SM::MainClock::SettingsParent::SetClock::SetHour::SET} */
        case SET_SIG: {
            int hours = ((Clock_Alarm_currentTime/1000U/60U/60U)%24);
              int minutes = ((Clock_Alarm_currentTime/1000U/60U)%60);
              int seconds = ((Clock_Alarm_currentTime/1000U)%60);
              hours = (hours+1)%24;
              if(me->alarmStatus == 1){
                sprintf(DisplayStringFirstLine,"Alarm - YES");
              }
              else{
                sprintf(DisplayStringFirstLine,"Alarm - NO");
              }

              sprintf(DisplayStringSecondLine,"%02d-%02d-%02d",hours,minutes,seconds);
              sprintf(DisplayStringThirdLine,"Hour Set");
              Clock_Alarm_currentTime = (hours*60*60*1000)+(minutes*60*1000)+(seconds*1000);
            RefreshDisplay(&DisplayStringFirstLine,&DisplayStringSecondLine,&DisplayStringThirdLine);
            status_ = Q_HANDLED();
            break;
        }
        /*.${HSM::Clock_Alarm::SM::MainClock::SettingsParent::SetClock::SetHour::OK} */
        case OK_SIG: {
              int hours = ((Clock_Alarm_currentTime/1000U/60U/60U)%24);
              int minutes = ((Clock_Alarm_currentTime/1000U/60U)%60);
              int seconds = ((Clock_Alarm_currentTime/1000U)%60);
              minutes = (minutes+1)%60;
              if(me->alarmStatus == 1){
                sprintf(DisplayStringFirstLine,"Alarm - YES");
              }
              else{
                sprintf(DisplayStringFirstLine,"Alarm - NO");
              }

              sprintf(DisplayStringSecondLine,"%02d-%02d-%02d",hours,minutes,seconds);
              sprintf(DisplayStringThirdLine,"Clock Set");
            RefreshDisplay(&DisplayStringFirstLine,&DisplayStringSecondLine,&DisplayStringThirdLine);
            status_ = Q_TRAN(&Clock_Alarm_SetMin);
            break;
        }
        default: {
            status_ = Q_SUPER(&Clock_Alarm_SetClock);
            break;
        }
    }
    return status_;
}
/*.${HSM::Clock_Alarm::SM::MainClock::SettingsParent::SetClock::SetMin} ....*/
static QState Clock_Alarm_SetMin(Clock_Alarm * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /*.${HSM::Clock_Alarm::SM::MainClock::SettingsParent::SetClock::SetMin} */
        case Q_ENTRY_SIG: {
                        if(me->alarmStatus == 1){
                            sprintf(DisplayStringFirstLine,"Alarm - YES");
                        }
                        else{
                            sprintf(DisplayStringFirstLine,"Alarm - NO");
                        }

                        sprintf(DisplayStringSecondLine,"%02d-%02d-%02d",((Clock_Alarm_currentTime/1000U/60U/60U)%24),((Clock_Alarm_currentTime/1000U/60U)%60U),((Clock_Alarm_currentTime/1000U)%60U));
                        sprintf(DisplayStringThirdLine,"Minute Set");
                        RefreshDisplay(&DisplayStringFirstLine,&DisplayStringSecondLine,&DisplayStringThirdLine);
            RefreshDisplay(&DisplayStringFirstLine,&DisplayStringSecondLine,&DisplayStringThirdLine);
            status_ = Q_HANDLED();
            break;
        }
        /*.${HSM::Clock_Alarm::SM::MainClock::SettingsParent::SetClock::SetMin::SET} */
        case SET_SIG: {
              int hours = ((Clock_Alarm_currentTime/1000U/60U/60U)%24);
              int minutes = ((Clock_Alarm_currentTime/1000U/60U)%60);
              int seconds = ((Clock_Alarm_currentTime/1000U)%60);
              minutes = (minutes+1)%60;
              if(me->alarmStatus == 1){
                sprintf(DisplayStringFirstLine,"Alarm - YES");
              }
              else{
                sprintf(DisplayStringFirstLine,"Alarm - NO");
              }

              sprintf(DisplayStringSecondLine,"%02d-%02d-%02d",hours,minutes,seconds);
              sprintf(DisplayStringThirdLine,"Minute Set");

              Clock_Alarm_currentTime = (hours*60*60*1000)+(minutes*60*1000)+(seconds*1000);
            RefreshDisplay(&DisplayStringFirstLine,&DisplayStringSecondLine,&DisplayStringThirdLine);
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&Clock_Alarm_SetClock);
            break;
        }
    }
    return status_;
}
/*.${HSM::Clock_Alarm::SM::MainClock::SettingsParent::SetAlarm} ............*/
static QState Clock_Alarm_SetAlarm(Clock_Alarm * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /*.${HSM::Clock_Alarm::SM::MainClock::SettingsParent::SetAlarm::initial} */
        case Q_INIT_SIG: {
            status_ = Q_TRAN(&Clock_Alarm_SetHour_Alarm);
            break;
        }
        default: {
            status_ = Q_SUPER(&Clock_Alarm_SettingsParent);
            break;
        }
    }
    return status_;
}
/*.${HSM::Clock_Alarm::SM::MainClock::SettingsParent::SetAlarm::SetHour_Alarm} */
static QState Clock_Alarm_SetHour_Alarm(Clock_Alarm * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /*.${HSM::Clock_Alarm::SM::MainClock::SettingsParent::SetAlarm::SetHour_Alarm} */
        case Q_ENTRY_SIG: {
            int hours = ((me->alarmTime/1000U/60U/60U)%24);
            int minutes = ((me->alarmTime/1000U/60U)%60);
            int seconds = ((me->alarmTime/1000U)%60);
            if(me->alarmStatus == 1){
              sprintf(DisplayStringFirstLine,"Alarm - YES");
            }
            else{
              sprintf(DisplayStringFirstLine,"Alarm - NO");
            }

            sprintf(DisplayStringSecondLine,"%02d-%02d-%02d",hours,minutes,seconds);
            sprintf(DisplayStringThirdLine,"Alarm Hour");
            RefreshDisplay(&DisplayStringFirstLine,&DisplayStringSecondLine,&DisplayStringThirdLine);
            status_ = Q_HANDLED();
            break;
        }
        /*.${HSM::Clock_Alarm::SM::MainClock::SettingsParent::SetAlarm::SetHour_Alarm::SET} */
        case SET_SIG: {
            int hours = ((me->alarmTime/1000U/60U/60U)%24);
            int minutes = ((me->alarmTime/1000U/60U)%60);
            int seconds = ((me->alarmTime/1000U)%60);
            hours = (hours+1)%24;
            if(me->alarmStatus == 1){
              sprintf(DisplayStringFirstLine,"Alarm - YES");
            }
            else{
              sprintf(DisplayStringFirstLine,"Alarm - NO");
            }

            sprintf(DisplayStringSecondLine,"%02d-%02d-%02d",hours,minutes,seconds);
            sprintf(DisplayStringThirdLine,"Alarm Hour");
            me->alarmTime = (hours*60*60*1000)+(minutes*60*1000)+(seconds*1000);

            RefreshDisplay(&DisplayStringFirstLine,&DisplayStringSecondLine,&DisplayStringThirdLine);
            status_ = Q_HANDLED();
            break;
        }
        /*.${HSM::Clock_Alarm::SM::MainClock::SettingsParent::SetAlarm::SetHour_Alarm::OK} */
        case OK_SIG: {
            status_ = Q_TRAN(&Clock_Alarm_SetMin_Alarm);
            break;
        }
        default: {
            status_ = Q_SUPER(&Clock_Alarm_SetAlarm);
            break;
        }
    }
    return status_;
}
/*.${HSM::Clock_Alarm::SM::MainClock::SettingsParent::SetAlarm::SetMin_Alarm} */
static QState Clock_Alarm_SetMin_Alarm(Clock_Alarm * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /*.${HSM::Clock_Alarm::SM::MainClock::SettingsParent::SetAlarm::SetMin_Alarm} */
        case Q_ENTRY_SIG: {
            int hours = ((me->alarmTime/1000U/60U/60U)%24);
            int minutes = ((me->alarmTime/1000U/60U)%60);
            int seconds = ((me->alarmTime/1000U)%60);
            if(me->alarmStatus == 1){
              sprintf(DisplayStringFirstLine,"Alarm - YES");
            }
            else{
              sprintf(DisplayStringFirstLine,"Alarm - NO");
            }

            sprintf(DisplayStringSecondLine,"%02d-%02d-%02d",hours,minutes,seconds);
            sprintf(DisplayStringThirdLine,"Alarm Min");
            RefreshDisplay(&DisplayStringFirstLine,&DisplayStringSecondLine,&DisplayStringThirdLine);
            status_ = Q_HANDLED();
            break;
        }
        /*.${HSM::Clock_Alarm::SM::MainClock::SettingsParent::SetAlarm::SetMin_Alarm::SET} */
        case SET_SIG: {
            int hours = ((me->alarmTime/1000U/60U/60U)%24);
            int minutes = ((me->alarmTime/1000U/60U)%60);
            int seconds = ((me->alarmTime/1000U)%60);
            minutes = (minutes+1)%60;
            if(me->alarmStatus == 1){
              sprintf(DisplayStringFirstLine,"Alarm - YES");
            }
            else{
              sprintf(DisplayStringFirstLine,"Alarm - NO");
            }

            sprintf(DisplayStringSecondLine,"%02d-%02d-%02d",hours,minutes,seconds);
            sprintf(DisplayStringThirdLine,"Alarm Min");
            me->alarmTime = (hours*60*60*1000)+(minutes*60*1000)+(seconds*1000);

            RefreshDisplay(&DisplayStringFirstLine,&DisplayStringSecondLine,&DisplayStringThirdLine);
            status_ = Q_HANDLED();
            break;
        }
        /*.${HSM::Clock_Alarm::SM::MainClock::SettingsParent::SetAlarm::SetMin_Alarm::OK} */
        case OK_SIG: {
            status_ = Q_TRAN(&Clock_Alarm_Arm_Alarm);
            break;
        }
        default: {
            status_ = Q_SUPER(&Clock_Alarm_SetAlarm);
            break;
        }
    }
    return status_;
}
/*.${HSM::Clock_Alarm::SM::MainClock::SettingsParent::SetAlarm::Arm_Alarm} .*/
static QState Clock_Alarm_Arm_Alarm(Clock_Alarm * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /*.${HSM::Clock_Alarm::SM::MainClock::SettingsParent::SetAlarm::Arm_Alarm} */
        case Q_ENTRY_SIG: {
            int hours = ((me->alarmTime/1000U/60U/60U)%24);
            int minutes = ((me->alarmTime/1000U/60U)%60);
            int seconds = ((me->alarmTime/1000U)%60);
            if(me->alarmStatus == 1){
              sprintf(DisplayStringFirstLine,"Alarm - YES");
            }
            else{
              sprintf(DisplayStringFirstLine,"Alarm - NO");
            }

            sprintf(DisplayStringSecondLine,"%02d-%02d-%02d",hours,minutes,seconds);
            sprintf(DisplayStringThirdLine,"Alarm 1/0");
            RefreshDisplay(&DisplayStringFirstLine,&DisplayStringSecondLine,&DisplayStringThirdLine);
            status_ = Q_HANDLED();
            break;
        }
        /*.${HSM::Clock_Alarm::SM::MainClock::SettingsParent::SetAlarm::Arm_Alarm::SET} */
        case SET_SIG: {

            int hours = ((me->alarmTime/1000U/60U/60U)%24);
            int minutes = ((me->alarmTime/1000U/60U)%60);
            int seconds = ((me->alarmTime/1000U)%60);

            if(me->alarmStatus == 1){
              sprintf(DisplayStringFirstLine,"Released");
              me->alarmStatus = 0;
            }
            else{
              me->alarmStatus = 1;
              sprintf(DisplayStringFirstLine,"Armed");
            }

            sprintf(DisplayStringSecondLine,"%02d-%02d-%02d",hours,minutes,seconds);
            sprintf(DisplayStringThirdLine,"Alarm 1/0");

            RefreshDisplay(&DisplayStringFirstLine,&DisplayStringSecondLine,&DisplayStringThirdLine);
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&Clock_Alarm_SetAlarm);
            break;
        }
    }
    return status_;
}
/*.${HSM::Clock_Alarm::SM::NotifyAlarm} ....................................*/
static QState Clock_Alarm_NotifyAlarm(Clock_Alarm * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /*.${HSM::Clock_Alarm::SM::NotifyAlarm} */
        case Q_ENTRY_SIG: {
            (me->timeout_AlarmMessage) =0;
            sprintf(DisplayStringFirstLine,"* - Alarm - *");
            sprintf(DisplayStringSecondLine," Alarm ");
            sprintf(DisplayStringThirdLine,"* - Alarm - *");
            RefreshDisplay(&DisplayStringFirstLine,&DisplayStringSecondLine,&DisplayStringThirdLine);
            status_ = Q_HANDLED();
            break;
        }
        /*.${HSM::Clock_Alarm::SM::NotifyAlarm} */
        case Q_EXIT_SIG: {
            me->alarmStatus = ALARM_OFF;
            status_ = Q_HANDLED();
            break;
        }
        /*.${HSM::Clock_Alarm::SM::NotifyAlarm::initial} */
        case Q_INIT_SIG: {
            status_ = Q_TRAN(&Clock_Alarm_MessageON);
            break;
        }
        /*.${HSM::Clock_Alarm::SM::NotifyAlarm::OK} */
        case OK_SIG: {
            me->alarmStatus == ALARM_OFF;
            status_ = Q_TRAN_HIST(me->hist_MainClock);
            break;
        }
        /*.${HSM::Clock_Alarm::SM::NotifyAlarm::TICK} */
        case TICK_SIG: {
            /*.${HSM::Clock_Alarm::SM::NotifyAlarm::TICK::[++(me->timeout_AlarmMain)==16]} */
            if (++(me->timeout_AlarmMain) == 16) {
                status_ = Q_TRAN(&Clock_Alarm_Ticking);
            }
            else {
                status_ = Q_UNHANDLED();
            }
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status_;
}
/*.${HSM::Clock_Alarm::SM::NotifyAlarm::MessageON} .........................*/
static QState Clock_Alarm_MessageON(Clock_Alarm * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /*.${HSM::Clock_Alarm::SM::NotifyAlarm::MessageON} */
        case Q_ENTRY_SIG: {
            (me->timeout_AlarmMessage) = 0;
            sprintf(DisplayStringFirstLine,"* - Alarm - *");
            sprintf(DisplayStringSecondLine," Alarm ");
            sprintf(DisplayStringThirdLine,"* - Alarm - *");
            RefreshDisplay(&DisplayStringFirstLine,&DisplayStringSecondLine,&DisplayStringThirdLine);
            status_ = Q_HANDLED();
            break;
        }
        /*.${HSM::Clock_Alarm::SM::NotifyAlarm::MessageON::TICK} */
        case TICK_SIG: {
            /*.${HSM::Clock_Alarm::SM::NotifyAlarm::MessageON::TICK::[(++(me->timeout_AlarmMessage)==~} */
            if (( ++(me->timeout_AlarmMessage) == 1 && ++(me->timeout_AlarmMain) < 15 )) {
                status_ = Q_TRAN(&Clock_Alarm_MessageOFF);
            }
            else {
                status_ = Q_UNHANDLED();
            }
            break;
        }
        default: {
            status_ = Q_SUPER(&Clock_Alarm_NotifyAlarm);
            break;
        }
    }
    return status_;
}
/*.${HSM::Clock_Alarm::SM::NotifyAlarm::MessageOFF} ........................*/
static QState Clock_Alarm_MessageOFF(Clock_Alarm * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /*.${HSM::Clock_Alarm::SM::NotifyAlarm::MessageOFF} */
        case Q_ENTRY_SIG: {
            (me->timeout_AlarmMessage) = 0;
            sprintf(DisplayStringFirstLine,"*     - - -         *");
            sprintf(DisplayStringSecondLine,"    - - - ");
            sprintf(DisplayStringThirdLine,"*     - - -         *");
            RefreshDisplay(&DisplayStringFirstLine,&DisplayStringSecondLine,&DisplayStringThirdLine);
            status_ = Q_HANDLED();
            break;
        }
        /*.${HSM::Clock_Alarm::SM::NotifyAlarm::MessageOFF::TICK} */
        case TICK_SIG: {
            /*.${HSM::Clock_Alarm::SM::NotifyAlarm::MessageOFF::TICK::[(++(me->timeout_AlarmMessage)==~} */
            if (( ++(me->timeout_AlarmMessage) == 1 && ++(me->timeout_AlarmMain) < 15 )) {
                status_ = Q_TRAN(&Clock_Alarm_MessageON);
            }
            else {
                status_ = Q_UNHANDLED();
            }
            break;
        }
        default: {
            status_ = Q_SUPER(&Clock_Alarm_NotifyAlarm);
            break;
        }
    }
    return status_;
}
/*.$enddef${HSM::Clock_Alarm} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

/*.$define${HSM::SuperClass_Qhsm_Clock} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*.${HSM::SuperClass_Qhsm_Clock} ...........................................*/
QHsm * const SuperClass_Qhsm_Clock = &Clock_Alarm_object.super;
/*.$enddef${HSM::SuperClass_Qhsm_Clock} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void MilliSecondInterrupt_Cb(struct k_timer * Handle){

    Clock_Alarm_update_current_time();

    milliSecondCounter+=1;

}


void RefreshDisplay(char * FirstLine,char * SecondLine,char * ThirdLine){

  u8g2_FirstPage(&u8g2);

  do {

    u8g2_SetFont(&u8g2,u8g2_font_ncenB14_tr);

    u8g2_DrawStr(&u8g2,0,16,FirstLine);

    u8g2_DrawStr(&u8g2,0+Offset,16+Offset,SecondLine);

    u8g2_DrawStr(&u8g2,0,16+40,ThirdLine);

  } while ( u8g2_NextPage(&u8g2) );

}

