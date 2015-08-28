/******************************************************************************
 * timer.h
 *  auther  Ahmed Samieh
 *  email   ahmed.samieh@gmail.com
 *
 * timer.h contains the code that interacts with the system timer.
 ******************************************************************************/
#ifndef TIMER_H
#define TIMER_H
#include <stdint.h>

uint64_t get_system_time();
void usleep(const uint32_t delay_usec);
#endif // TIMER_H
