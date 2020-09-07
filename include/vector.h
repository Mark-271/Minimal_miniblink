#ifndef VECTOR_H
#define VECTOR_H

typedef void (*vector_table_entry_t)(void);

struct vector_table {
	unsigned int *initial_sp_value; /**< Initial stack pointer value. */
	vector_table_entry_t reset;
	};

void reset_handler(void);

/* Common symbols exported by the linker script(s): */
extern unsigned _data_loadaddr, _data, _edata, _ebss, _stack;
extern struct vector_table vector_table;

#endif /* VECTOR_H */
