# we declare the object we want to build in the variable EXE
# we list the objects we want to compile (from c) in OBJS
# we provide a phony target clean to rm all the .o files

EXE = fpconvert
SRC = main.c fpconvert.S convert_inf.S
OBJS = main.o fpconvert.o convert_inf.o
LIBS =
CC = gcc
DEBUG = -ggdb3 -O0
WARN = -Wall -Wextra -Wformat-security
CFLAGS = -I. -std=gnu17 $(DEBUG) $(WARN)

AS = gcc
ASLIST = -Wa,-adhln
ASFLAGS = -I.

%.o : %.S
	$(AS) -c $(ASFLAGS) $(DEBUG) $< -o $@

.PHONY: clean

$(EXE) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $@

clean :
	rm -rf $(OBJS) $(EXE)
