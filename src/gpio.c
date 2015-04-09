/******************************************************************************
 * gpio.c
 *  by Ahmed Samieh
 *
 * gpio.c contains the functions for manipulation of the GPIO ports.
 ******************************************************************************/
volatile unsigned int *const g_gpio_address = (unsigned int *)0x20200000;
void gpio_set_function(int pin_number, int function)
{
    if (pin_number <= 53 && function <= 7)
    {
        int shift = pin_number, word = 0, mask, value;
        while (shift >= 10)
        {
            shift -= 10;
            word++;
        }
        shift += (shift << 1); // shift *= 3
        mask = 7 << shift;
        value = function << shift;
        g_gpio_address[word] = (g_gpio_address[word] & (~mask)) | value;
    }
}
void gpio_set(int pin_number, int value)
{
    if (pin_number <= 53)
    {
        int shift = pin_number, word;
        if (value == 0)
        {
            word = 10; // g_gpio_address + 40 = (40:48) turn pin off
        }
        else
        {
            word = 7; // g_gpio_address + 28 = (28:36) turn pin on
        }
        if (shift >= 32)
        {
            shift -= 32;
            word++; // g_gpio_address + 32 or g_gpio_address + 44
        }
        g_gpio_address[word] |= (1 << shift);
    }
}
int gpio_get(int pin_number)
{
    if (pin_number <= 53)
    {
        int shift = pin_number, word = 13; // g_gpio_address + 52
        if (shift >= 32)
        {
            shift -= 32;
            word++; // g_gpio_address + 56
        }
        return ((g_gpio_address[word] >> shift) & 1);
    }
    return 0;
}
