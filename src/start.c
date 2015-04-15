#include <stdint.h>

/* __bss_start__ and __bss_end__ are defined in the linker script */
extern uint32_t __bss_start__;
extern uint32_t __bss_end__;

void _start() __attribute__((section(".text.startup")));
void _start()
{
    asm("ldr sp, =0x8000");
    uint32_t *bss     = &__bss_start__;
    uint32_t *bss_end = &__bss_end__;
    while (bss < bss_end)
    {
        *bss++ = 0;
    }
    asm("b main");
    while (1);
}

