#include <stdint.h>
#include "rpibplus.h"
#include "gpio.h"

/* BCM2835 ARM Peripherals manual, section 7.5 */

#define TIMER_IRQ (1)

#define TIMER_CTRL_23BIT        (1 << 1)
#define TIMER_CTRL_PRESCALE_16  (1 << 2)
#define TIMER_CTRL_PRESCALE_256 (2 << 2)
#define TIMER_CTRL_INT_ENABLE   (1 << 5)
#define TIMER_CTRL_ENABLE       (1 << 7)

volatile uint32_t * const g_interrupt_controller_address = (uint32_t * const)INTERRUPT_CONTROLLER_BASE;
volatile uint32_t * const g_timer_address = (uint32_t * const)TIMER_BASE;
uint32_t g_task[2] = {0};
uint32_t g_task_id = 0;
void __attribute__((naked, section(".text.startup"))) _start(void)
{
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
    /* reset vector */
    asm volatile ("reset_vector: mov sp, #0x5000");
    asm volatile ("mov r0, #0x8000");
    asm volatile ("mov r1, #0x0000");
    asm volatile ("ldmia r0!,{r2, r3, r4, r5, r6, r7, r8, r9}");
    asm volatile ("stmia r1!,{r2, r3, r4, r5, r6, r7, r8, r9}");
    asm volatile ("ldmia r0!,{r2, r3, r4, r5, r6, r7, r8, r9}");
    asm volatile ("stmia r1!,{r2, r3, r4, r5, r6, r7, r8, r9}");
    /* zero init bss section */
    asm volatile ("mov r0, #0");
    /* __bss_start__ and __bss_end__ are defined in the linker script */
    asm volatile ("ldr r1, =__bss_start__");
    asm volatile ("ldr r2, =__bss_end__");
    asm volatile ("b bss_test");
    asm volatile ("zero_init: str r0, [r1]");
    asm volatile ("add r1, #4");
    asm volatile ("bss_test: cmp r1, r2");
    asm volatile ("bne zero_init");
    /* Enable the timer interrupt IRQ */
    *((volatile uint32_t * const)(g_interrupt_controller_address + 6)) = TIMER_IRQ;
    /* Setup the system timer interrupt */
    /* Timer frequency = Clk/256 * 0x100 */
    *((volatile uint32_t * const)(g_timer_address + 0)) = 0x100; /* Load */
    *((volatile uint32_t * const)(g_timer_address + 2)) = TIMER_CTRL_23BIT |
                                                          TIMER_CTRL_PRESCALE_256 |
                                                          TIMER_CTRL_INT_ENABLE |
                                                          TIMER_CTRL_ENABLE; /* Cotrol */
    /* Switch to System Mode - b11111 */
    asm volatile ("cps #0x1F");
    /*asm volatile ("mrs r0, cpsr");
    asm volatile ("orr r0, r0, #0x1F");
    asm volatile ("msr cpsr, r0");*/

    /* setup task0 */
    asm volatile ("mov sp, #0x7000");
    /* push r0-r12, lr, spsr, (pc+4) into stack */
    asm volatile ("mov r0, #0");
    asm volatile ("push {r0}"); /* r0 */
    asm volatile ("push {r0}"); /* r1 */
    asm volatile ("push {r0}"); /* r2 */
    asm volatile ("push {r0}"); /* r3 */
    asm volatile ("push {r0}"); /* r4 */
    asm volatile ("push {r0}"); /* r5 */
    asm volatile ("push {r0}"); /* r6 */
    asm volatile ("push {r0}"); /* r7 */
    asm volatile ("push {r0}"); /* r8 */
    asm volatile ("push {r0}"); /* r9 */
    asm volatile ("push {r0}"); /* r10 */
    asm volatile ("push {r0}"); /* r11 */
    asm volatile ("push {r0}"); /* r12 */
    asm volatile ("push {r0}"); /* lr */
    asm volatile ("bic r0, r0, #0x80"); /* clear bit 7 in Program Status Register to enable IRQ */
    asm volatile ("ldr r1, =task0");
    asm volatile ("add r1, r1, #4");
    asm volatile ("push {r0, r1}"); /* spsr, pc + 4 */
    asm volatile ("mov %0, sp" : "=r" (g_task[0]));

    /* setup task1 */
    asm volatile ("mov sp, #0x8000");
    /* push r0-r12, lr, spsr, (pc+4) into stack */
    asm volatile ("mov r0, #0");
    asm volatile ("push {r0}"); /* r0 */
    asm volatile ("push {r0}"); /* r1 */
    asm volatile ("push {r0}"); /* r2 */
    asm volatile ("push {r0}"); /* r3 */
    asm volatile ("push {r0}"); /* r4 */
    asm volatile ("push {r0}"); /* r5 */
    asm volatile ("push {r0}"); /* r6 */
    asm volatile ("push {r0}"); /* r7 */
    asm volatile ("push {r0}"); /* r8 */
    asm volatile ("push {r0}"); /* r9 */
    asm volatile ("push {r0}"); /* r10 */
    asm volatile ("push {r0}"); /* r11 */
    asm volatile ("push {r0}"); /* r12 */
    asm volatile ("push {r0}"); /* lr */
    asm volatile ("bic r0, r0, #0x80"); /* clear bit 7 in Program Status Register to enable IRQ */
    asm volatile ("ldr r1, =task1");
    asm volatile ("add r1, r1, #4");
    asm volatile ("push {r0, r1}"); /* spsr, pc+4 */
    asm volatile ("mov %0, sp" : "=r" (g_task[1]));

    asm volatile ("mov sp, #0x6000");
    asm volatile ("b main_task");
    while (1);
}
void __attribute__((naked)) undefined_instruction_vector(void)
{
    while (1);
}
void __attribute__((naked)) software_interrupt_vector(void)
{
    while (1);
}
void __attribute__((naked)) instruction_fetch_memory_abort_vector(void)
{
    while (1);
}
void __attribute__((naked)) data_access_memory_abort_vector(void)
{
    while (1);
}
void __attribute__((naked)) interrupt_vector(void)
{
    /* save running task context */
    asm volatile ("cps #0x1F");          /* switch to system mode */
    asm volatile ("push {r0-r12,lr}");   /* push context registers into task stack */
    asm volatile ("cps #0x12");          /* switch to IRQ mode */
    asm volatile ("mrs r0, spsr");       /* copy system mode cpsr from irq mode spsr */
    asm volatile ("mov r1, lr");         /* copy lr (system mode pc + 4) */
    asm volatile ("cps #0x1F");          /* switch to system mode */
    asm volatile ("push {r0, r1}");      /* push context cpsr and (pc + 4) into task stack */

    /* save task sp into g_task and load another task sp */
    asm volatile ("ldr r0, =g_task");
    asm volatile ("ldr r1, =g_task_id");
    asm volatile ("ldr r2, [r1]");
    asm volatile ("str sp, [r0, r2, lsl #2]");
    asm volatile ("eor r2, r2, #1");
    asm volatile ("ldr sp, [r0, r2, lsl #2]");
    asm volatile ("str r2, [r1]");

    /* load address of g_timer_address pointer into r0 */
    asm volatile ("ldr r0, =g_timer_address");
    /* load g_timer_address pointer into r0 */
    asm volatile ("ldr r0, [r0]");
    asm volatile ("mov r1, #1");
    asm volatile ("str r1, [r0, #12]");

    asm volatile ("pop {r0, r1}");       /* pop context (pc + 4) from task stack */
    asm volatile ("cps #0x12");          /* switch to IRQ mode */
    asm volatile ("msr spsr, r0");
    asm volatile ("mov lr, r1");         /* restore lr (system mode pc + 4) */
    asm volatile ("cps #0x1F");          /* switch to system mode */
    /* restore task status r0-r12, lr*/
    asm volatile ("pop {r0-r12,lr}");
    /* switch to IRQ mode */
    asm volatile ("cps #0x12");
    asm volatile ("subs pc, lr, #4");
}
void __attribute__((naked)) fast_interrupt_vector(void)
{
    while (1);
}
