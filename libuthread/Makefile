# Target library
lib     := libuthread.a
#objs    := context.o preempt.o queue.o uthread.o
objs    := queue.o
CC      := gcc
CFLAGS  := -Wall -Werror
CFLAGS  += -g
PANDOC  := pandoc
all: $(lib)

$(lib): $(objs)
	@echo "CC $@"
	ar cr $@ $^

#%.o: %.c context.h preempt.h uthread.h
	#@echo "CC $@"
	#$(CC) $(CFLAGS) -c -o $@make $<

#%.o: %.c preempt.h uthread.h
	#@echo "CC $@"
	#$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.c queue.h
	@echo "CC $@"
	$(CC) $(CFLAGS) -c -o $@ $<

#%.o: %.c uthread.h preempt.h queue.h context.h
	#@echo "CC $@"
	#$(CC) $(CFLAGS) -c -o $@ $<

%.html: %.md
	@echo "MD $@"
	$(PANDOC) -o $@ $<

clean:
	@echo "CLEAN"
	rm -f $(lib) $(objs)