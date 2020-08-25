#ifndef GPIO_H
#define GPIO_H

#include <common.h>
#include <memorymap.h>

/* GPIO port base addresses (for convenience) */
#define GPIOC				GPIO_PORT_C_BASE

/* GPIO number definitions (for convenience) */
/** @defgroup gpio_pin_id GPIO Pin Identifiers
@ingroup gpio_definitions

@{*/
#define GPIO8				(1 << 8)
#define GPIO_ALL			0xffff
/**@}*/

/* --- GPIO registres ---------------------------------------------------- */

/* Port configuration register low (GPIOx_CRL) */
#define GPIO_CRL(port)			MMIO32((port) + 0x00
#define GPIOC_CRL			GPIOC_CRL(GPIOC)

/* Port configuration register high (GPIOx_CRH) */
#define GPIO_CRH(port)			MMIO32((port) + 0x04)
#define GPIOC_CRH			GPIO_CRH(GPIOC)

/* --- GPIO_CRL/GPIO_CRH values ------------------------------------------ */

/* Pin configuration (CNF[1:0]) when MODE[1:0] is != 00
 * (one of the output modes)
 */
#define GPIO_CNF_OUTPUT_PUSHPULL	0x00

/* Pin mode (MODE[1:0]) values */
#define GPIO_MODE_OUTPUT_2MHz		0x02



void gpio_set_mode(uint32_t gpioport, uint8_t mode, uint8_t cnf,
		   uint16_t gpios);
void gpio_toggle(uint32_t gpioport, uint16_t gpios);

#endif /* GPIO_H */
