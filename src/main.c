#include <stdint.h>
#include "timer.h"
#include "gpio.h"

int main()
{
    /*gpio_set_function(GPIO_PWR, GPIO_OUTPUT);*/
    asm("mov r0, #35");
    asm("mov r1, #1");
    asm("bl gpio_set_function");
    /*gpio_set_function(GPIO_ACT, GPIO_OUTPUT);*/
    asm("mov r0, #47");
    asm("mov r1, #1");
    asm("bl gpio_set_function");
    /* turn on ACT if we are in System Mode, if not turn it OFF */
    asm("loop: mrs r0, cpsr");
    asm("and r0, r0, #0x1f");
    asm("cmp r0, #0x1f");
    asm("bne clear");
    /*gpio_set(GPIO_ACT, GPIO_ON);*/
    asm("mov r0, #47");
    asm("mov r1, #1");
    asm("bl gpio_set");
    asm("b done");
    /*gpio_set(GPIO_ACT, GPIO_OFF);*/
    asm("clear: mov r0, #47");
    asm("mov r1, #0");
    asm("bl gpio_set");
    asm("done: b loop");
}
