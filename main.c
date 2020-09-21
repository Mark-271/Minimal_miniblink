#include <stdint.h>

#define MMIO32(addr)			(*(volatile int32_t *)(addr))
#define SCB_CCR				MMIO32(0xE000ED14)
#define RCC_APB2ENR			MMIO32(0x40021018)
#define GPIOC_CRH			MMIO32(0x40011004)
#define GPIO_CNF_MASK			0x03
#define GPIO_MODE_PP			0x02
#define GPIO8				(1 << 8)
#define GPIOC_BSRR			MMIO32(0x40011010)
#define GPIOC_BRR			MMIO32(0x40011014)

struct vector_table {
	unsigned int *initial_sp_value; /* Initial stack pointer value. */
	void (*reset)(void);
};

/* Common symbols exported by the linker script(s): */
extern unsigned _data_loadaddr, _data, _edata, _ebss, _stack;
extern struct vector_table vector_table;

int main(void)
{
	int i;

	/* Enable GPIOC clock. */
	RCC_APB2ENR |= (1 << 4);

	/* Set GPIO8 (in GPIO port C) to 'output push-pull'. */
	GPIOC_CRH = (GPIOC_CRH &= ~(GPIO_CNF_MASK << 2)) | (GPIO_MODE_PP << 0);

	/* Blink the LED (PC8) on the board. */
	while (1) {
		GPIOC_BSRR = GPIO8;		/* LED on */
		for (i = 0; i < 800000; i++)	/* Wait a bit. */
			__asm__("nop");

		GPIOC_BRR = GPIO8;		/* LED off */
		for (i = 0; i < 800000; i++)	/* Wait a bit. */
			__asm__("nop");
	}
}

void reset_handler(void)
{
	volatile unsigned *src, *dest;

	for (src = &_data_loadaddr, dest = &_data;
		dest < &_edata; src++, dest++) {
		*dest = *src;
	}

	while (dest < &_ebss) {
		*dest++ = 0;
	}

	/* Ensure 8-byte aligment of stack pointer on interrupts */
	SCB_CCR |= (1 << 9);

	/* Call the application's entry point. */
	(void)main();
}

__attribute__ ((section(".vectors")))
struct vector_table vector_table = {
	.initial_sp_value	= &_stack,
	.reset			= reset_handler,
};
