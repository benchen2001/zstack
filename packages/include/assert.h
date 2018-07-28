#ifndef ASSERT_H
#define ASSERT_H

#include <misc/printk.h>

#define assert(condition) do {						\
	if (!(condition)) {						\
		printk("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);	\
		while (1);
	} while (0);

#endif
