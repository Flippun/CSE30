// file header
	.arch armv6                  // armv6 architecture
	.arm                         // arm 32-bit instruction set
	.fpu vfp                     // floating point co-processor
	.syntax unified              // modern syntax

	// .extern                   // symbol import - external references
	// .equ                      // file level definitions
	.equ EOF, -1
	// .bss                      // uncomment if needed
    // .data                        // uncomment if needed
	.section .rodata          // uncomment if needed
mode:	.string "r"
fmt1:	.string "%zu"
fmt2:	.string "%zu %zu"

	.text                        // start of text segment
	// function header (change main to function name in 5 places below)
	.global create_board         // make function global for linking to
	.type create_board, %function	// define as a function
	.equ FP_OFFSET, 		20            // (#regs pushed -1) * 4 is distance from sp
	.equ rows,				4 + FP_OFFSET
	.equ cols,				4 + rows
	.equ row,				4 + cols
	.equ col,				4 + row
	.equ PAD,				0 + col
	.equ FRMADD,			PAD - FP_OFFSET

	// Board struct offsets
	.equ buf1,				0
	.equ buf2,				4 + buf1
	.equ nrows,				4 + buf2
	.equ ncols,				4 + nrows
	.equ buffer,			4 + ncols
	.equ nextbuffer,		4 + buffer	
	.equ gen,				4 + nextbuffer
	.equ BRD_SIZE, 			4 + gen
	.equ EXIT_SUCCESS, 0         // return success (used by main)
	.equ EXIT_FAILURE, 1         // return failure (used by main)
create_board:
	// function prologue
	push {r4-r7, fp, lr}               // stack register save minimum: fp,lr (push in pairs!)
	add fp, sp, FP_OFFSET       	    // set frame pointer to frame base
	ldr r4, =FRMADD
	sub sp, sp, r4						// add space for locals

	// function begins
	ldr r1, =mode						// 					; r1 = "r"
	bl fopen							// FLE *fp = fopen(filename, "r");
	mov r4, r0							//						; r4 = fp
	mov r0, BRD_SIZE					//					; r0 = sizeof(Board)
 	bl malloc							// Board *bptr = malloc(sizeof(Board));		
	mov r5, r0							//						; r5 = bptr
	mov r0, r4							//					; r0 = FILE *
	ldr r1, =fmt1						//					; r1 = "%zu"
	add r2, fp, -rows					//					; r2 = &rows
	bl fscanf							// fscanf(fp, "%zu", &rows);
	ldr r6, [fp, -rows]					//						; r6 = rows
	str r6, [r5, nrows]					// bptr->nrows = rows;
	mov r0, r4							//					; r0 = FILE *
	ldr r1, =fmt1						//					; r1 = "%zu"
	add r2, fp, -cols					//					; r2 = &cols
	bl fscanf							// fscanf(fp, "%zu", &cols);
	ldr r7, [fp, -cols]					//						; r7 = cols
	str r7, [r5, ncols]			 		// bptr->ncols = cols;
	mul r0, r6, r7						
	bl malloc							// bptr->buf1 = malloc(rows * cols);
	str r0, [r5, buf1]					// .
	str r0, [r5, buffer]				// bptr->buffer = bptr->buf1;
	mul r0, r6, r7					
	bl malloc							// bptr->buf2 = malloc(rows * cols);
	str r0, [r5, buf2]					// .
	str r0, [r5, nextbuffer]			// bptr->next_buffer = bptr->buf2;
	mov r0, r5							
	bl clear_board						// clear_board(bptr);
.Lloop:
	mov r0, r4							//					; r0 = FILE *
	ldr r1, =fmt2						//					; r1 = "%zu %zu"
	add r2, fp, -row					//					; r2 = &row
	add r3, fp, -col					//					; r3 = &col
	bl fscanf							// while ( fscanf(fp, "%zu %zu", &row, &col) > 0 ) {	 						
	cmp r0, 0							// .
	ble .Lend							// .
	mov r0, r7							//					; r0 = cols
	ldr r1, [fp, -row]					//					; r1 = row
	ldr r2, [fp, -col]					//					; r2 = col
	bl get_index						//     index = get_index(cols, row, col);
	mov r2, 1
	ldr r1, [r5, nextbuffer]			//					; r1 = bptr->next_buffer
	strb r2, [r1, r0]					// 	   bptr->next_buffer[index] = 1;
	b .Lloop							// }
.Lend:
	mov r0, r4							// fclose(fp)
	bl fclose							// .
	mov r0, r5							// swap_buffers(bptr);
	bl swap_buffers						// .
	mov r1, 0
	str r1, [r5, gen]					// bptr->gen = 0;					 
	mov r0, r5							// return bptr;

	// function epilogue
	sub sp, fp, FP_OFFSET        // restore stack frame top
	pop {r4-r7, fp, lr}         // remove frame and restore registers
	bx lr                        // return to caller
	// function footer
	.size create_board, (. - create_board) // set size for function
	// file footer
	.section .note.GNU-stack, "", %progbits // stack/data non-exec
.end
