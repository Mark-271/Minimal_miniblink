#include <rcc.h>
#include <gpio.h>

static void gpio_setup(void)
{
	/* Enable GPIOC clock. */
	rcc_periph_clock_enable(RCC_GPIOC);

	/* Set GPIO8 (in GPIO port C) to 'output push-pull'. */
	gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHz,
		      GPIO_CNF_OUTPUT_PUSHPULL, GPIO8);
}

int main(void)
{
	int i;

	gpio_setup();

	/* Blink the LED (PC8) on the board. */
	while (1) {
		gpio_toggle(GPIOC, GPIO8);	/* LED on/off */
		for (i = 0; i < 800000; i++)	/* Wait a bit. */
			__asm__("nop");
	}
}
