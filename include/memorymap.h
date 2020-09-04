#ifndef MEMORYMAP_H
#define MEMORYMAP_H

/* --- STM32 speccific peripheral definitions ------------------------ */

/* Memory map for buses*/
#define FLASH_BASE			(0x08000000U)
#define PERIPH_BASE			(0x40000000U)
#define PERIPH_BASE_APB2		(PERIPH_BASE + 0x10000)
#define PERIPH_BASE_AHB			(PERIPH_BASE + 0x18000)

/* Register boundary adresses */

/* APB2 */
#define GPIO_PORT_C_BASE		(PERIPH_BASE_APB2 + 0X1000)

/* PERIPH_BASE_AHB + 0x8800 (0x4002 0800 -0x4002 0FFF): Reserved */
#define RCC_BASE			(PERIPH_BASE_AHB + 0x09000)

/* --- ARM CORTEX-M3 specific definitions ----------------------------- */

/* Private peripheral bus - Internal */
#define PPBI_BASE			(0xE0000000U)

#define SCS_BASE			(PPBI_BASE + 0xE000)

/* --- SCS: System Control Space --- */

/* SCB: System Control Block */
#define SCB_BASE			(SCS_BASE + 0x0D00)

/* NVIC: Nested Vector Interrupt Controller */
#define NVIC_BASE			(SCS_BASE + 0x0100)

#endif /* MEMORYMAP_H */
