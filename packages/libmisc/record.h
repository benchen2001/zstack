#ifndef RECORD_H
#define RECORD_H

int	record_ope	(const char *title);
void	record		(int handle, const char *message);
char *	record_view	(int handle); // a work item will clear the temporary buffer, or by record_delete
void	record_close	(int handle);

#endif
