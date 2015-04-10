#include "gpio.h"
#include "timer.h"

void main()
{
    unsigned char pattern = 0b00010001;
    int status = 0;
    gpio_set_function(GPIO_PWR, GPIO_OUTPUT);
    gpio_set_function(GPIO_ACT, GPIO_OUTPUT);
    while (1)
    {
        int i;
        gpio_set(GPIO_ACT, (status ^= 1) ? GPIO_ON : GPIO_OFF);
        for (i = 0; i < 8; i++)
        {
            gpio_set(GPIO_PWR, (pattern & (1 << i)) ? GPIO_ON : GPIO_OFF);
            usleep(1000 * 1000);
        }
    }
}
