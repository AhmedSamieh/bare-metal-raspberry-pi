/******************************************************************************
 * system_timer.c
 *  by Ahmed Samieh
 *
 * system_time.c contains the code that interacts with the system timer.
 ******************************************************************************/
/*
 * The system timer runs at 1MHz, and just counts always. Thus we can deduce
 * timings by measuring the difference between two readings.
 */
volatile unsigned int *const g_system_timer_address = (unsigned int *)0x20003000;
unsigned long long get_system_time()
{
    return *((volatile unsigned long long *)(g_system_timer_address + 1));
}
void usleep(unsigned int delay_usec)
{
    unsigned long long start = get_system_time();
    while ((get_system_time() - start) < delay_usec);
}

