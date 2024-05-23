// file header
	.arch armv6                  // armv6 architecture
	.arm                         // arm 32-bit instruction set
	.fpu vfp                     // floating point co-processor
	.syntax unified              // modern syntax

	// .extern                   // symbol import - external references
	// .equ                      // file level definitions
	// .bss                      // uncomment if needed
	// .data                     // uncomment if needed
	// .section .rodata          // uncomment if needed

	.text                        // start of text segment
	// function header (change main to function name in 5 places below)
	.global sim_loop             // make function global for linking to
	.type sim_loop, %function    // define as a function
	.equ FP_OFFSET, 		28          		 // (#regs pushed -1) * 4 is distance from sp.
	.equ PAD, 				4 + FP_OFFSET
	.equ OARG5, 			4 + PAD	 
	.equ FRMADD,			OARG5 - FP_OFFSET
	
	// Board struct offsets
	.equ buf1,				0
	.equ buf2,				4 + buf1
	.equ nrows,				4 + buf2
	.equ ncols,				4 + nrows
	.equ buffer,			4 + ncols
	.equ nextbuffer,		4 + buffer
	.equ gen,				4 + nextbuffer

	.equ EXIT_SUCCESS, 0          // return success (used by main)
	.equ EXIT_FAILURE, 1          // return failure (used by main)
sim_loop:
	// function prologue
	push {r4-r9, fp, lr}         // stack register
	add fp, sp, FP_OFFSET         // set frame pointer to frame base
	ldr r4, =FRMADD
	sub sp, sp, r4				  // allocate space for locals & 5th arg
	
	// function start						  
	mov r4, r0					  // 						; r4 = b
	mov r5, r1					  //						; r5 = steps
	ldr r6, [r4, nrows]			  //						; r6 = b->nrows
	ldr r0, [r4, ncols]		  	  //						; store b->ncols as 5th param	
	str r0, [sp]	
	cmp r5, 0					  // while (steps > 0) {
	ble .Lendwh					  // .					
.Lwhile: 
	mov r7, 0					  // 						; r6 = i 
	cmp r7, r6 					  // 	for (i = 0; i < board->nrows; i++) {
	bge .Lendfor				  // 	.
	ldr r8, [r4, nextbuffer]	  //						; r8 = b->nextbuffer
	ldr r9, [r4, buffer]		  //						; r9 = b->buffer	
.Lfor:	
	mov r0, r8					  //					; r0 = b->nextbuffer
	mov r1, r9 					  //					; r1 = b->buffer
	mov r2, r7					  // 					; r2 = i
	mov r3, r6					  //					; r3 = b->nrows
	bl do_row				 	  //		do_row(b->next_buffer, b->buffer, i, b->nrows, b->ncols);
	add r7, r7, 1				  // 	.
	cmp r7, r6					  // 	.
	blt .Lfor					  // 	}
.Lendfor:
	mov r0, r4					  // 					; r0 = b
	bl swap_buffers				  //    swap_buffers(board);
	ldr r0, [r4, gen]	 		  //					; r0 = n->gen
	add r0, r0, 1				  // 	board->gen++; 
	str r0, [r4, gen]
	sub r5, r5, 1			      // 	steps--;
	cmp r5, 0					  // .
	bgt .Lwhile					  // }
.Lendwh:    
    
	// function epilogue
	sub sp, fp, FP_OFFSET         // restore stack frame top
	pop {r4-r9, fp, lr}          // remove frame and restore registers
	bx lr                         // return to caller
	// function footer
	.size sim_loop, (. - sim_loop) // set size for function
	// file footer
	.section .note.GNU-stack, "", %progbits // stack/data non-exec
.end
