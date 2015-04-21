#define PERIPHERALS_BASE (0x20000000)

#define GPIO_BASE  (PERIPHERALS_BASE + 0x200000)
#define GPIO_FSEL0 (GPIO_BASE)
#define GPIO_FSEL1 (GPIO_BASE + 0x4)
#define GPIO_FSEL2 (GPIO_BASE + 0x8)
#define GPIO_FSEL3 (GPIO_BASE + 0xC)
#define GPIO_FSEL4 (GPIO_BASE + 0x10)
#define GPIO_FSEL5 (GPIO_BASE + 0x14)
#define GPIO_SET0  (GPIO_BASE + 0x1C)
#define GPIO_SET1  (GPIO_BASE + 0x20)
#define GPIO_CLR0  (GPIO_BASE + 0x28)
#define GPIO_CLR1  (GPIO_BASE + 0x2C)

#define SYSTEM_TIMER_BASE (PERIPHERALS_BASE + 0x3000)

#define INTERRUPT_CONTROLLER_BASE (PERIPHERALS_BASE + 0xB200)

#define TIMER_BASE (PERIPHERALS_BASE + 0xB400)


