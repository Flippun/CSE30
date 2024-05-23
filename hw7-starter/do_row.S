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
	.global do_row               // make function global for linking to
	.type do_row, %function      // define as a function
	.equ FP_OFFSET, 	32            // (#regs pushed -1) * 4 is distance from sp
	.equ dest,			4 + FP_OFFSET			// local variables ...
	.equ src,			4 + dest
	.equ row,			4 + src
	.equ rows,			4 + row
	.equ neighbors,		4 + rows
	.equ index,			4 + neighbors
	.equ PAD,			4 + index
	.equ FRMADD,		PAD - FP_OFFSET

	.equ ARG5, 4
	.equ EXIT_SUCCESS, 0         // return success (used by main)
	.equ EXIT_FAILURE, 1         // return failure (used by main)
do_row:
	// function prologue
	push {r4-r10, fp, lr}           // stack register save minimum: fp,lr (push in pairs!)
	add fp, sp, FP_OFFSET        	// set frame pointer to frame base
	ldr r4, =FRMADD
	sub sp, sp, r4					// add space for locals	

	// function begins
	ldr r5, =dest					// store dest to stack
	str r0, [fp, -r5]
	ldr r5, =src					// store src to stack
	str r1, [fp, -r5]
	ldr r5, =row					// store row to stack
	str r2, [fp, -r5]
	ldr r5, =rows					// store rows to stack
	str r3, [fp, -r5]
	ldr r4, [fp, ARG5]				//							; r4 = cols	
	mov r5, 0						//							; r5 = col	
	cmp r5, r4						// for (col = 0; col < cols; col++) {
	bge .LendRow					// .
.LforRow:
	mov r6, 0						// 	  neighbors = 0
	ldr r0, =neighbors				
	str r6, [fp, -r0]				//							; store neighbors on stack
	mov r0, r4						// 	  index = get_index(cols, row, col);		
	ldr r1, =row					//	  .
	ldr r1, [fp, -r1]				//    .
	mov r2, r5						//    .
	bl get_index					//    .
	mov r6, r0						//    .
	ldr r0, =index					//							; store index on stack
	str r6, [fp, -r0]
	mov r6, 0						//							; r6 = j
	cmp r6, 3						//	  for (j = 0; j < 3; j++) {
	bge .LendJfor					//	  .
.LJfor:
	ldr r0, =row							  
	ldr r0, [fp, -r0]				//						; r0 = row
	ldr r1, =rows
	ldr r1, [fp, -r1]				//						; r1 = rows
	add r0, r0, r1					//		  cmp_row = mod(row + rows + j - 1, rows);
	add r0, r0, r6					//		  .
	sub r0, r0, 1				 	//		  .
	bl mod							//		  .
	mov r7, r0						//							; r7 = cmp_row
	mov r8, 0						//							; r8 = k
	cmp r8, 3						//		  for (k = 0; k < 3; k++) {					
	bge .LendKfor					//		  .
.LKfor:
	mov r0, r5						//						; r0 = col
	mov r1, r4						//						; r1 = cols
	add r0, r0, r1					//			  cmp_col = mod(col + cols + k - 1, cols);  
	add r0, r0, r8					//			  .
	sub r0, r0, 1					//			  .
	bl mod
	mov r9, r0						//							; r9 = cmp_col
	mov r0, r4						//						; r0 = cols
	mov r1, r7						//						; r1 = cmp_row
	mov r2, r9						//						; r2 = cmp_col
	bl get_index					//			  cmp_index = get_index(cols, cmp_row, cmp_col);
	mov r10, r0						//							; r10 = cmp_index
	ldr r0, =row							  
	ldr r0, [fp, -r0]				//						; r0 = row
	cmp r0, r1						//			  if (row == cmp_row && col == cmp_col) { continue; }
	bne .LendCif					//			  .		 			      
	cmp r5, r9						//			  .
	bne .LendCif					//			  .
	b .LcontinueKfor				//			  .
.LendCif:
	ldr r0, =src							  
	ldr r0, [fp, -r0]				//						; r0 = src
	ldrb r0, [r0, r10]				//					; r0 = src[cmp_index]
	cmp r0, 1				 		//			  if (src[cmp_index]) { 	
	bne .LcontinueKfor				//			  .
	ldr r1, =neighbors				//						; r0 = neighbors				  
	ldr r0, [fp, -r1]										
	add r0, r0, 1					//			  	  neighbors++;
	str r0, [fp, -r1]				//			  }
.LcontinueKfor:
	add r8, r8, 1					// 	  	  .
	cmp r8, 3						// 	  	  .
	blt .LKfor						// 	  	  }	
.LendKfor:
	add r6, r6, 1					// 	  .
	cmp r6, 3						// 	  .
	blt .LJfor						// 	  }	
.LendJfor:	
	// find src[index]
	ldr r3, =src							  
	ldr r0, [fp, -r3]				//						; r0 = src
	ldr r3, =index							  
	ldr r1, [fp, -r3]				//							; r1 = index
	ldrb r0, [r0, r1]				//							; r0 = src[index]	
	// load neighbors
	ldr r2, =neighbors				//							; r2 = neighbors				  
	ldr r2, [fp, -r2]				//							; r3 = dest[index]
	// If statements for neighbors
	cmp r0, 1						//	  if (src[index]) {
	bne .LdeadCell					//	  .
	cmp r2, 2						//	  	  if (neighbors != 2 && neighbors != 3) {
	beq .L2or3						//		  .
	cmp r2, 3						//		  .
	beq .L2or3						//		  .
	mov r3, 0						//		  	  dest[index] = 0; }
	b .LcontinueRow					//		  else {
.L2or3:
	mov r3, 1						//		  	  dest[index] = 1; }
	b .LcontinueRow					//	  else {
.LdeadCell:
	cmp r2, 3						//	  	  if (neighbors != 3 && neighbors != 6) {
	beq .L3or6						//		  .
	cmp r2, 6						//		  .
	beq .L3or6						//		  .
	mov r3, 0						//		  	  dest[index] = 0; }
	b .LcontinueRow					//		  else {
.L3or6:
	mov r3, 1						//		  	  dest[index] = 1; }
									//	  }
.LcontinueRow:
	ldr r0, =dest					//						; Updates Cell in dest	
	ldr r0, [fp, -r0]				//						; .
	strb r3, [r0, r1]				//						; .			
	add r5, r5, 1					// col++
	cmp r5, r4						// .
	blt .LforRow					// }
.LendRow:

	// function epilogue
	sub sp, fp, FP_OFFSET        // restore stack frame top
	pop {r4-r10, fp, lr}                 // remove frame and restore registers
	bx lr                        // return to caller
	// function footer
	.size do_row, (. - do_row)  // set size for function
	// file footer
	.section .note.GNU-stack, "", %progbits // stack/data non-exec
.end
