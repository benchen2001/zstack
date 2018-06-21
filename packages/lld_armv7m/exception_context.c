#include <core.h>

struct core_exception_context {
	uint32_t r0;
	uint32_t r1;
	uint32_t r2;
	uint32_t r3;
	uint32_t r12;
	uint32_t lr;
	uint32_t pc;
	uint32_t xpsr;
};

int core_exception_context_size = sizeof(struct core_exception_context);

void core_exception_context_init(uint32_t base, uint32_t entry, uint32_t end)
{
	struct core_exception_context *context = base;

	context->pc = entry;
	context->lr = end;
	context->xpsr = 0x01000000;
}

