#ifndef RTC_H
#define	RTC_H

#include "oled.h"
#include "keypad.h"
#include "reminders.h"

// Initialize RTC variables
void initRTC();

// ISR for RTC
ISR(RTC_CNT_vect);

#endif	/* RTC_H */

