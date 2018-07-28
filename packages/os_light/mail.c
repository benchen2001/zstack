/*
 * follow producer-consumer model
 */

#include <string.h>
#include <core.h>
#include <kernel.h>
#include <assert.h>

#include "os.h"

struct mailbox mailbox_array[CONFIG_MAILBOX_NUM];

int mail_post (int id, const struct mail *mail)
{
	int i;
	int slot;
	
	interrupt_disable();
	
	/* check if full, block the sender */
	if (CONFIG_MAILBOX_SIZE == mailbox_array[id].num) {
		tcb_array[current_task].ready_link = 0;
		tcb_array[current_task].event_link = 1;
		tcb_array[current_task].event_id = 0;
		goto end;
	}

	slot = mailbox_array[id].slot;

	/* TODO consider to use priority, no priority for easy verification */
	memcpy(&mailbox_array[id].queue[slot], mail, sizeof(struct mail));

	mailbox_array[id].num++;
	mailbox_array[id].slot = (slot + 1) % CONFIG_MAILBOX_SIZE; /* a ring buffer*/

end:
	interrupt_enable();

	software_interrupt(0);

	// NEVER GOES HERE	
	return 0;
}

// TODO if support priority, the mailbox ready/slot will change more flexible
int mail_take (int id, struct mail *mail)
{
	int ready;

	interrupt_disable();

	/* check if mailbox empty, if so, block reader */
	if (0 == mailbox_array[id].num) {
		tcb_array[current_task].ready_link = 0;
		tcb_array[current_task].event_link = 1; /* TODO use mailbox link */
		tcb_array[current_task].event_id = 0;	/* TODO use mailbox id */
		goto end;
	}

	ready = mailbox_array[id].ready;

	/* TODO consider to use priority, no priority for easy verification */
	memcpy(mail, &mailbox_array[id].queue[ready], sizeof(struct mail));

	mailbox_array[id].num--;

	/* attention, maybe there is no ready mail, but it can point to the mail slot */
	mailbox_array[id].ready = (ready + 1) % CONFIG_MAILBOX_SIZE;

	assert(mailbox_array[id].num >= 0); /* don't add if else here, for speed up, TODO add predictable if else */

end:
	interrupt_enable();

	software_interrupt(0);

	// NEVER GOES HERE
	return 0;
}

