OBJS += 82540em.o

all: built-in.o

built-in.o: $(OBJS)
	$(LD) -melf_i386 -r -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.S
	$(CC) $(CFLAGS) -o $@ $<

%.d: %.c
	$(CC) -M -nostdinc -I$(REPO)/include $< > $@

%.d: %.S
	$(CC) -M -nostdinc -I$(REPO)/include $< > $@

-include $(OBJS:.o=.d)

clean:
	rm -f *.o

