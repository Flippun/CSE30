//! functions to support life

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * time funcs
 */
//! start a time measurement
extern void start_meas();

//! stop a time measurement
extern void stop_meas();

//! get elapsed seconds
extern double get_secs();

/**
 *  predefined shapes
 */
//! create a glider
extern void glider(uint8_t *buf, size_t cols, size_t v, size_t h);

//! create a toad
extern void toad(uint8_t *buf, size_t cols, size_t v, size_t h);

//! create an acorn
extern void acorn(uint8_t *buf, size_t cols, size_t v, size_t h);

//! create an oscillator horiz orient
extern void oscillator(uint8_t *buf, size_t cols, size_t v, size_t h);

//! create an oscillator vertical
extern void oscillator_vert(uint8_t *buf, size_t cols, size_t v, size_t h);

/**
 * board plotting/printing
 */
extern void print_board(uint8_t *buf, size_t rows, size_t cols, size_t gen);
extern void clear_screen();

//! dump board to a file
extern void dump_board(uint8_t *buf, size_t rows, size_t cols, const char *dump);
