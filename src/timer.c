/******************************************************************************
 * timer.c
 *  auther  Ahmed Samieh
 *  email   ahmed.samieh@gmail.com
 *
 * timer.c contains the code that interacts with the system timer.
 ******************************************************************************/
/*
 * The system timer runs at 1MHz, and just counts always. Thus we can deduce
 * timings by measuring the difference between two readings.
 */
#include <stdint.h>
#include "rpibplus.h"

volatile uint64_t * const g_system_timer_address = (uint64_t * const)SYSTEM_TIMER_BASE;
uint64_t get_system_time()
{
    return *(g_system_timer_address + 1);
}
/* cpu consumer */
void usleep(uint32_t delay_usec)
{
    uint64_t start = get_system_time();
    while ((get_system_time() - start) < delay_usec);
}

