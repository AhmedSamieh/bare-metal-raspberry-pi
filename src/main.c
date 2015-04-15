#include <stdint.h>
#include "timer.h"
#include "gpio.h"

int main()
{
    uint8_t pwr_status = 0, act_status = 0;
    uint8_t i;

    gpio_set_function(GPIO_PWR, GPIO_OUTPUT);
    gpio_set_function(GPIO_ACT, GPIO_OUTPUT);
    gpio_set(GPIO_PWR, GPIO_OFF);
    gpio_set(GPIO_ACT, GPIO_OFF);
    usleep(2 * 1000 * 1000);
    while (1)
    {
        gpio_set(GPIO_PWR, (pwr_status ^= GPIO_ON));
        for (i = 0; i < 20; i++)
        {
            gpio_set(GPIO_ACT, (act_status ^= GPIO_ON));
            usleep(50 * 1000);
        }
    }
}

