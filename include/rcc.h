#ifndef RCC_H
#define RCC_H

#include <common.h>
#include <memorymap.h>

#define _REG_BIT(base, bit)		(((base) << 5) + (bit))

/* V = value line F100
 * N = standart line F101, F102, F103
 * C = communication line F105, F107
 */
enum rcc_periph_clken {
	/* APB2 peripherals */
	RCC_GPIOC	= _REG_BIT(0x18, 4), /*VNC*/
};

void rcc_periph_clock_enable (enum rcc_periph_clken clken);

#endif /* RCC_H */
