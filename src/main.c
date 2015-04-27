#include <stdint.h>
#include "timer.h"
#include "gpio.h"

void task0(void)
{
    uint8_t act_status = 0;
    while (1)
    {
        gpio_set(GPIO_ACT, (act_status ^= GPIO_ON));
        usleep(100 * 1000);
    }
}
void task1(void)
{
    uint8_t pwr_status = 0;
    while (1)
    {
        gpio_set(GPIO_PWR, (pwr_status ^= GPIO_ON));
        usleep(500 * 1000);
    }
}

void main_task()
{
    /*gpio_set_function(GPIO_PWR, GPIO_OUTPUT);*/
    asm volatile ("mov r0, #35");
    asm volatile ("mov r1, #1");
    asm volatile ("bl gpio_set_function");
    /*gpio_set_function(GPIO_ACT, GPIO_OUTPUT);*/
    asm volatile ("mov r0, #47");
    asm volatile ("mov r1, #1");
    asm volatile ("bl gpio_set_function");

    asm volatile ("ldr r0, =g_task");
    asm volatile ("ldr r1, =g_task_id");
    asm volatile ("ldr r2, [r1]");
    asm volatile ("ldr sp, [r0, r2, lsl #2]");

    asm volatile ("pop {r0, r1}");
    asm volatile ("msr cpsr, r0");
    asm volatile ("pop {lr}");
    asm volatile ("mov lr, r1");
    asm volatile ("pop {r0-r12}");
    asm volatile ("subs pc, lr, #4");
    while (1);
}
