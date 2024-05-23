LIBS = -lcse30liferevisited
CC = gcc
CFLAGS := -O0 -ggdb3 --std=gnu17 -L/home/linux/ieng6/cs30wi24/public/liblife

.PHONY: all clean

all: life-ccc life-scc life-csc life-ccs life-ssc life-scs life-css life-sss

life-ccc: create_board_c.o sim_loop_c.o do_row_c.o
	gcc -o $@ $(CFLAGS) $^ $(LIBS)
life-scc: create_board.o sim_loop_c.o do_row_c.o
	gcc -o $@ $(CFLAGS) $^ $(LIBS)
life-csc: create_board_c.o sim_loop.o do_row_c.o
	gcc -o $@ $(CFLAGS) $^ $(LIBS)
life-ccs: create_board_c.o sim_loop_c.o do_row.o
	gcc -o $@ $(CFLAGS) $^ $(LIBS)
life-ssc: create_board.o sim_loop.o do_row_c.o
	gcc -o $@ $(CFLAGS) $^ $(LIBS)
life-scs: create_board.o sim_loop_c.o do_row.o
	gcc -o $@ $(CFLAGS) $^ $(LIBS)
life-css: create_board_c.o sim_loop.o do_row.o
	gcc -o $@ $(CFLAGS) $^ $(LIBS)
life-sss: create_board.o sim_loop.o do_row.o
	gcc -o $@ $(CFLAGS) $^ $(LIBS)

do_row.o: do_row.S cse30liferevisited.h
	gcc $(CFLAGS) -c $<
sim_loop.o: sim_loop.S cse30liferevisited.h
	gcc $(CFLAGS) -c $<
create_board.o: create_board.S cse30liferevisited.h
	gcc $(CFLAGS) -c $<

do_row_c.o: do_row.c cse30liferevisited.h
	gcc $(CFLAGS) -c $< -o do_row_c.o
sim_loop_c.o: sim_loop.c cse30liferevisited.h
	gcc $(CFLAGS) -c $< -o sim_loop_c.o
create_board_c.o: create_board.c cse30liferevisited.h
	gcc $(CFLAGS) -c $< -o create_board_c.o

clean:
	rm -f *.o life-ccc life-scc life-csc life-ccs life-ssc life-scs life-css life-sss
