EXE = life
OBJS = main.c board.c sim.c
LIBS = -lcse30life
CFLAGS := -Wall -Wextra -ggdb3 -O0 --std=gnu17 -L/home/linux/ieng6/cs30wi24/public/lib

.PHONY: clean

$(EXE): $(OBJS) 
	gcc -o $@ $(CFLAGS) $(OBJS) $(LIBS)

clean :
	rm -f $(EXE)
