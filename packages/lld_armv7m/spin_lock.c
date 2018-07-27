#include <stdint.h>

/*
 * the spin lock based on bus monitor, it works when ldrex/strex pair apears.
 * note: it can monitor DMA & CPU's memory access.
 *
 * TODO use memory barrier to make the instructions ordered in pipeline
 */
void spin_lock(uint32_t *lock)
{
	uint32_t result;
	uint32_t value;

	__asm__ __volatile__ (
	"1: ldrex %0, [%2]\n"
	"   teq %0, #0\n"
	"   bne 1b\n"			/* wait for current core releas the lock */
	"   strex %1, #1, [%2]\n"	/* try to take the lock */
	"   teq %2, #0\n"
	"   bne 1b"
	: (value), (result)
	: (lock)
	);
}

void spin_unlock(uint32_t *lock)
{	
	*lock = 0;		/* break loop */
}
