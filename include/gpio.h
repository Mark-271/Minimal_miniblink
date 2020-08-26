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

/* Port output data register (GPIOx_ODR) */
#define GPIO_ODR(port)			MMIO32((port) + 0x0c)
#define GPIOC_ODR			GPIO_ODR(GPIOC)

/* Port configuration register low (GPIOx_CRL) */
#define GPIO_CRL(port)			MMIO32((port) + 0x00)
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

/* --- GPIO Registers ------------------------------------------------------ */

/* Port bit set/reset register (GPIOx_BSRR) */
#define GPIO_BSRR(port)			MMIO32((port) + 0x10)
#define GPIOA_BSRR			GPIO_BSRR(GPIOA)
#define GPIOB_BSRR			GPIO_BSRR(GPIOB)
#define GPIOC_BSRR			GPIO_BSRR(GPIOC)
#define GPIOD_BSRR			GPIO_BSRR(GPIOD)
#define GPIOE_BSRR			GPIO_BSRR(GPIOE)
#define GPIOF_BSRR			GPIO_BSRR(GPIOF)
#define GPIOG_BSRR			GPIO_BSRR(GPIOG)

/* Port bit reset register (GPIOx_BRR) */
#define GPIO_BRR(port)			MMIO16((port) + 0x14)
#define GPIOA_BRR			GPIO_BRR(GPIOA)
#define GPIOB_BRR			GPIO_BRR(GPIOB)
#define GPIOC_BRR			GPIO_BRR(GPIOC)
#define GPIOD_BRR			GPIO_BRR(GPIOD)
#define GPIOE_BRR			GPIO_BRR(GPIOE)
#define GPIOF_BRR			GPIO_BRR(GPIOF)
#define GPIOG_BRR			GPIO_BRR(GPIOG)


void gpio_set_mode(uint32_t gpioport, uint8_t mode, uint8_t cnf,
		   uint16_t gpios);
void gpio_toggle(uint32_t gpioport, uint16_t gpios);

#endif /* GPIO_H */
