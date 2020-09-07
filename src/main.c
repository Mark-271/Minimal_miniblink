#include <gpio.h>
#include <rcc.h>
#include <stdint.h>

/* Generic memory-mapped I/O accessor function */
#define MMIO32(addr)			(*(volatile int32_t *)(addr))

/* APB2 Peripheral clock enable register */
#define RCC_APB2ENR			MMIO32(0x40021018)

/* Port C configuration register high */
#define GPIOC_CRH			MMIO32(0x40011004)

/* Port bit configuration */
#define GPIO_CNF_PUSHPULL		0x00

/* Output mode bits */
#define GPIO_MODE_OUTPUT_2_MHz		0x02

/* Pin number */
#define GPIO8				(1 << 8)

/* General purpose set/reset register */
#define GPIOC_BSRR			MMIO32(0x40011010)

/* General purpose reset register */
#define GPIOC_BRR			MMIO32(0x40011014)

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
