#include <stdint.h>
#include "timer.h"
#include "gpio.h"

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
    /* turn on ACT if we are in System Mode, if not turn it OFF */
    asm volatile ("loop: mrs r0, cpsr");
    asm volatile ("and r0, r0, #0x1f");
    asm volatile ("cmp r0, #0x1f");
    asm volatile ("bne clear");
    /*gpio_set(GPIO_ACT, GPIO_ON);*/
    asm volatile ("mov r0, #47");
    asm volatile ("mov r1, #1");
    asm volatile ("bl gpio_set");
    asm volatile ("b done");
    /*gpio_set(GPIO_ACT, GPIO_OFF);*/
    asm volatile ("clear: mov r0, #47");
    asm volatile ("mov r1, #0");
    asm volatile ("bl gpio_set");
    asm volatile ("done: b loop");
}
