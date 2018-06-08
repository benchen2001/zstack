extern unsigned char *section_bss_start, *section_bss_end;

void bss_clear (void)
{
	unsigned char *bss;

	for (bss=section_bss_start; bss<section_bss_end; bss++) {
		*bss = 0;
	}
}
 
