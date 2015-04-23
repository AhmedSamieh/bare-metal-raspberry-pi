#include <stdint.h>
#include "rpibplus.h"
#include "gpio.h"

/* __bss_start__ and __bss_end__ are defined in the linker script */
extern uint32_t __bss_start__;
extern uint32_t __bss_end__;

/* BCM2835 ARM Peripherals manual, section 7.5 */

#define TIMER_IRQ (1)

#define TIMER_CTRL_23BIT        (1 << 1)
#define TIMER_CTRL_PRESCALE_16  (1 << 2)
#define TIMER_CTRL_PRESCALE_256 (2 << 2)
#define TIMER_CTRL_INT_ENABLE   (1 << 5)
#define TIMER_CTRL_ENABLE       (1 << 7)

volatile uint32_t *g_interrupt_controller_address = (uint32_t *)INTERRUPT_CONTROLLER_BASE;
volatile uint32_t *g_timer_address = (uint32_t *)TIMER_BASE;
uint32_t g_task_id = 0;
void __attribute__((section(".text.startup"))) _start(void)
{
    uint32_t *bss     = &__bss_start__;
    uint32_t *bss_end = &__bss_end__;
    /* Supervisor Mode - b10011 */
    asm volatile ("ldr pc, reset_vector_address");
    asm volatile ("ldr pc, undefined_instruction_vector_address");
    asm volatile ("ldr pc, software_interrupt_vector_address");
    asm volatile ("ldr pc, instruction_fetch_memory_abort_vector_address");
    asm volatile ("ldr pc, data_access_memory_abort_vector_address");
    asm volatile ("ldr pc, unused_handler_address");
    asm volatile ("ldr pc, interrupt_vector_address");
    asm volatile ("ldr pc, fast_interrupt_vector_address");
    asm volatile ("reset_vector_address: .word reset_vector");
    asm volatile ("undefined_instruction_vector_address: .word undefined_instruction_vector");
    asm volatile ("software_interrupt_vector_address: .word software_interrupt_vector");
    asm volatile ("instruction_fetch_memory_abort_vector_address: .word instruction_fetch_memory_abort_vector");
    asm volatile ("data_access_memory_abort_vector_address: .word data_access_memory_abort_vector");
    asm volatile ("unused_handler_address: .word reset_vector");
    asm volatile ("interrupt_vector_address: .word interrupt_vector");
    asm volatile ("fast_interrupt_vector_address: .word fast_interrupt_vector");
    asm volatile ("reset_vector: mov r0, #0x8000");
    asm volatile ("mov r1, #0x0000");
    asm volatile ("ldmia r0!,{r2, r3, r4, r5, r6, r7, r8, r9}");
    asm volatile ("stmia r1!,{r2, r3, r4, r5, r6, r7, r8, r9}");
    asm volatile ("ldmia r0!,{r2, r3, r4, r5, r6, r7, r8, r9}");
    asm volatile ("stmia r1!,{r2, r3, r4, r5, r6, r7, r8, r9}");
    while (bss < bss_end)
    {
        *bss++ = 0;
    }
    /* Enable the timer interrupt IRQ */
    *((volatile uint32_t *)(g_interrupt_controller_address + 6)) = TIMER_IRQ;
    /* Setup the system timer interrupt */
    /* Timer frequency = Clk/256 * 0x1000 */
    *((volatile uint32_t *)(g_timer_address + 0)) = 0x1000; /* Load */
    *((volatile uint32_t *)(g_timer_address + 2)) = TIMER_CTRL_23BIT |
                                                    TIMER_CTRL_PRESCALE_256 |
                                                    TIMER_CTRL_INT_ENABLE |
                                                    TIMER_CTRL_ENABLE; /* Cotrol */
    /* Switch to System Mode - b11111 */
    asm volatile ("cps #0x1F");
    /* set sp on system mode */
    asm volatile ("mov sp, #0x8000");
    /* clear bit 7 in Program Status Register to enable global interrupts */
    /* IRQ enable*/
    asm volatile ("cpsie i");
    asm volatile ("b main_task");
    while (1);
}
void __attribute__((interrupt("UNDEF"))) undefined_instruction_vector(void)
{
    while( 1 )
    {
    }
}
void __attribute__((interrupt("SWI"))) software_interrupt_vector(void)
{
}
void __attribute__((interrupt("ABORT"))) instruction_fetch_memory_abort_vector(void)
{
}
void __attribute__((interrupt("ABORT"))) data_access_memory_abort_vector(void)
{
}
void __attribute__((interrupt("IRQ"))) interrupt_vector(void)
{
    *((volatile uint32_t *)(g_timer_address + 3)) = 1;
    gpio_set(GPIO_PWR, (g_task_id ^= GPIO_ON));
    gpio_set(GPIO_ACT, GPIO_OFF);
}
void __attribute__((interrupt("FIQ"))) fast_interrupt_vector(void)
{
}
