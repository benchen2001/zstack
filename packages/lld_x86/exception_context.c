#include <core.h>
#include "selector.h"

struct core_exception_context {
	uint32_t pc;
	uint32_t cs;
	uint32_t eflags;
	uint32_t sp;
	uint32_t ds;
};

int core_exception_context_size = sizeof(struct core_exception_context);

void core_exception_context_init(uint32_t base, uint32_t entry, uint32_t exit)
{
	struct core_exception_context *context = (void *)base;

	context->cs = SS_TASK_INIT_CODE;
	context->ds = SS_TASK_INIT_DATA;
	context->eflags = 0x206;
	context->pc = entry;
	context->sp = base;
}

