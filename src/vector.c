#include <scb.h>
#include <vector.h>

int main(void);

static void blocking_handler(void)
{
	while (1);
}

static void null_handler(void)
{
	/* Do nothing. */
}

__attribute__ ((section(".vectors")))
struct vector_table vector_table = {
	.initial_sp_value	= &_stack,
	.reset			= reset_handler,
	.nmi			= null_handler,
	.hard_fault		= blocking_handler,

	.memory_manage_fault	= blocking_handler,
	.bus_fault		= blocking_handler,
	.usage_fault		= blocking_handler,
	.debug_monitor		= null_handler,

	.sv_call		= null_handler,
	.pend_sv		= null_handler,
	.systick		= null_handler,
};

void __attribute__ ((weak)) reset_handler(void)
{
	volatile unsigned *src, *dest;

	for (src = &_data_loadaddr, dest = &_data;
		dest < &_edata;
		src++, dest++) {
		*dest = *src;
	}

	while (dest < &_ebss) {
		*dest++ = 0;
	}

	/* Ensure 8-byte alignment of stack pointer on interrupts */
	/* Enabled by default on most Cortex-M parts, but not M3 r1 */
	SCB_CCR |= SCB_CCR_STKALIGN;

	/* Call the application's entry point. */
	(void)main();
}
