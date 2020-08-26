#include <gpio.h>
/** @brief Set GPIO Pin Mode

Set the mode (input/output) and configuration (analog/digital and
open drain/push pull), for a set of GPIO pins on a given GPIO port.

@param[in] gpioport Unsigned int32. Pin identifier
@param[in] mode Unsigned int8. Pin mode
@param[in] cnf Unsigned int8. Pin configuration
@param[in] gpios Unsigned int16. Pin identifiers

*/

void gpio_set_mode(uint32_t gpioport, uint8_t mode, uint8_t cnf, uint16_t gpios)
{
	uint16_t i, offset = 0;
	uint32_t crl = 0, crh = 0, tmp32 = 0;

	/*
	 * We want to set the config only for the pins mentioned in gpios,
	 * but keeping the others, so read out the actual config first.
	 */
	crl = GPIO_CRL(gpioport);
	crh = GPIO_CRH(gpioport);

	/* Iterate over all bits, use  i as the bitnumber. */
	for (i = 0; i < 16; i++) {
		/* Only set the config if the bit is set in gpios. */
		if(!((1 << i) & gpios)) {
			continue;
		}

	/* Calculate bit offset. */
	offset = (i < 8) ? (i * 4) : ((i - 8) * 4);

	/* Use tmp32 to either modify crl or crh. */
	tmp32 = (i < 8) ? crl : crh;

	/* Modify bits are neede. */
	tmp32 &= ~(0xf << offset);	/* Clear the bits first */
	tmp32 |= (mode << offset) | (cnf << (offset + 2));

	/* Write tmp32 into crl or crh, leavve the other unchanged. */
		crl = (i < 8) ? tmp32 : crl;
		crh = (i >= 8) ? tmp32 : crh;
	 }

	GPIO_CRL(gpioport) = crl;
	GPIO_CRH(gpioport) = crh;
}

/** @brief Toggle a Group of Pins

Toggle one or more pins of the given GPIO port. The toggling is not atomic, but
the non-toggled pins are not affected.

@param[in] gpioport Unsigned int32. Port identifier.
@param[in] gpios Unsigned int16. Pin identifiers.
	     If multiple pins are to be changed, use bitwise OR '|' to separate
	     them.
*/
void gpio_toggle(uint32_t gpioport, uint16_t gpios)
{
	uint32_t port = GPIO_ODR(gpioport);
	GPIO_BSRR(gpioport) = ((port & gpios) << 16) | (~port & gpios);
}

