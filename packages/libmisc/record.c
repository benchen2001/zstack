// record.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdlib.h>
#include <string.h>

// for security & safe
#define MESSAGE_LEN_MAX		(100)

typedef struct _record_item_ {
	struct _record_item_	*prev;
	struct _record_item_	*next;
	int						length;
	char					payload[1];
} record_item_t;

typedef struct _record_ {
	record_item_t	*head;
	int				count;
	int				length;
	char			*view;
} record_t;

int record_open(const char *title)
{
	if (NULL == title) {
		title = "None";
	}

	int total = 0;
	int length = strlen(title);

	length = (length >= MESSAGE_LEN_MAX) ? MESSAGE_LEN_MAX : length;
	total = sizeof(record_item_t) + length; // include '\0'

	record_t *handle = (record_t *)malloc(sizeof(record_t));
	memset(handle, 0, sizeof(record_t));

	record_item_t *head = (record_item_t *)malloc(total);
	memset(head, 0, total);

	memcpy_s(head->payload, length, title, length);
	head->length = length;
	head->prev = head->next = head;

	handle->count = 1;
	handle->length = length;
	handle->head = head;

	return (int)handle;
}

void record_close(int handle)
{
	record_t *record = (record_t *)handle;

	record_item_t *a = record->head, *b = NULL;

	while (record->head != b) {
		b = a->next;
		free(a);
		a = b;
	}

	if (NULL != record->view) {
		free(record->view);
	}

	free(record);
}

void record(int handle, const char *message)
{
	record_t *record = (record_t *)handle;

	int total = 0;
	int length = strlen(message);

	length = (length >= MESSAGE_LEN_MAX) ? MESSAGE_LEN_MAX : length;
	total = sizeof(record_item_t) + length; // include '\0'

	record_item_t *package = (record_item_t *)malloc(total);
	memset(package, 0, total);

	memcpy_s(package->payload, length, message, length);
	package->length = length;

	record_item_t *head = record->head;
	record_item_t *prev = head->prev;

	prev->next = package; package->prev = prev;
	head->prev = package; package->next = head;

	record->count++;
	record->length += length;
}

const char *view_head = "\nRECORDER\n-------------------------\n     ";
const char *view_tail = "-------------------------\n";

char * record_view(int handle)
{
	record_t *record = (record_t *)handle;

	int total = record->length + record->count * sizeof('\n') + strlen(view_head)+1 + strlen(view_tail)+1;

	record->view = (char *)malloc(total);
	record->view[0] = '\0';

	snprintf(&record->view[strlen(record->view)], total, "%s", view_head);

	record_item_t *a = record->head, *b = NULL;

	while (record->head != b) {
		b = a->next;
		snprintf(&record->view[strlen(record->view)], total, "%s\n", a->payload);
		a = b;
	}

	snprintf(&record->view[strlen(record->view)], total, "%s", view_tail);

	return record->view;
}

int main()
{
	int handle = record_create("Hello Recorder");
	record(handle, "aaafdsavdxvdsgvdggdfg");
	record(handle, "bbb");

	printf("%s", record_view(handle));

    return 0;
}
