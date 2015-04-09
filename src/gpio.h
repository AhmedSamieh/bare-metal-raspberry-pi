/******************************************************************************
 * gpio.h
 *  by Ahmed Samieh
 *
 * gpio.h contains the functions for manipulation of the GPIO ports.
 ******************************************************************************/
/* GPIO FUNCTION */
#define GPIO_INPUT  (0)
#define GPIO_OUTPUT (1)

/* GPIO VALUE */
#define GPIO_OFF    (0)
#define GPIO_ON     (1)

/* GPIO PIN */
#define GPIO_PWR    (35)
#define GPIO_ACT    (47)

void gpio_set_function(int pin_number, int function);
void gpio_set(int pin_number, int value);
int  gpio_get(int pin_number);
