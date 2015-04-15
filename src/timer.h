/******************************************************************************
 * timer.c
 *  by Ahmed Samieh
 *
 * timer.h contains the code that interacts with the system timer.
 ******************************************************************************/
#include <stdint.h>

uint64_t get_system_time();
void usleep(uint32_t delay_usec);
