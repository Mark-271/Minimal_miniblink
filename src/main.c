#include <stdint.h>
#include <vector.h>

/* Generic memory-mapped I/O accessor function */
#define MMIO32(addr)			(*(volatile int32_t *)(addr))

/* System control block configuration and control register */
#define SCB_CCR				MMIO32(0xE000ED14)

/* APB2 Peripheral clock enable register */
#define RCC_APB2ENR			MMIO32(0x40021018)

/* Port C configuration register high */
#define GPIOC_CRH			MMIO32(0x40011004)

/* Port bit configuration */
#define GPIO_CNF_OUTPUT_PUSHPULL		0x00

/* Output mode bits */
#define GPIO_MODE_OUTPUT_2_MHz		0x02

/* Pin number */
#define GPIO8				(1 << 8)

/* General purpose set/reset register */
#define GPIOC_BSRR			MMIO32(0x40011010)

/* General purpose reset register */
#define GPIOC_BRR			MMIO32(0x40011014)

typedef void (*vector_table_entry_t)(void);

struct vector_table {
	unsigned int *initial_sp_value; /**< Initial stack pointer value. */
	vector_table_entry_t reset;
	};

void reset_handler(void);

/* Common symbols exported by the linker script(s): */
extern unsigned _data_loadaddr, _data, _edata, _ebss, _stack;
extern struct vector_table vector_table;

int main(void);

__attribute__ ((section(".vectors")))
struct vector_table vector_table = {
	.initial_sp_value	= &_stack,
	.reset			= reset_handler,
};

void __attribute__((weak)) reset_handler(void)
{
	volatile unsigned *src, *dest;

	for (src = &_data_loadaddr, dest = &_data;
		dest < &_edata;
		src++, dest++) {
		*dest = *src;
	}

	/* Ensure 8-byte aligment of stack pointer on interrupts */
	SCB_CCR |= (1 << 9);

	/* Call the application's entry point. */
	(void)main();
}

/* ------------------------------------------------------------------------- */

int main(void)
{
	int i;

	/* Enable GPIOC clock. */
	RCC_APB2ENR |= (1 << 4);

	/* Set GPIO8 (in GPIO port C) to 'output push-pull'. */
	GPIOC_CRH = (GPIO_CNF_OUTPUT_PUSHPULL << (((8 - 8) * 4) + 2));
	GPIOC_CRH |= (GPIO_MODE_OUTPUT_2_MHz << ((8 - 8) * 4));

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
