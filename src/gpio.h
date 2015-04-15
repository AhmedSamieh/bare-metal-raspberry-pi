/******************************************************************************
 * gpio.h
 *  by Ahmed Samieh
 *
 * gpio.h contains the functions for manipulation of the GPIO ports.
 ******************************************************************************/
#include <stdint.h>

/* GPIO FUNCTION */
#define GPIO_INPUT  (0)
#define GPIO_OUTPUT (1)

/* GPIO VALUE */
#define GPIO_OFF    (0)
#define GPIO_ON     (1)

/* GPIO PIN */
#define GPIO_PWR    (35)
#define GPIO_ACT    (47)

void gpio_set_function(uint8_t pin_number, uint8_t function);
void gpio_set(uint8_t pin_number, uint8_t value);
uint8_t  gpio_get(uint8_t pin_number);
