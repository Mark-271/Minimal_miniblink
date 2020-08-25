#include <rcc.h>
#include <common.h>
#include <memorymap.h>

#define _RCC_REG( i) MMIO32(RCC_BASE + ((i) >> 5))
#define _RCC_BIT( i) (1 << ((i) & 0x1f))

/* --------------------------------------------------------------------- */
/** @brief Enable peripheral clock in running mode.
 *
 * Enable the clock on particular peripheral
 *
 * @param[in] clken rcc_periph_clken Peripheral RCC
 *
 * For available constants, see #rcc_periph_clken (GPIOC for example)
 */

void rcc_periph_clock_enable(enum rcc_periph_clken clken)
{
	_RCC_REG(clken) |= _RCC_BIT(clken);
}
