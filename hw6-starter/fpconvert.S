// === file header ===
	.arch armv6               // armv6 architecture
	.cpu cortex-a72           // our CPU model
	.arm                      // arm 32-bit IS
	.fpu vfp                  // floating point co-processor
	.syntax unified           // modern syntax
// === definitions applying to the entire source file ===
	.equ SIGN_MASK, 0x00008000
	.equ EXP_MASK, 0x00007f00
	.equ MANT_MASK, 0x000000ff
	// .data                  // uncomment if you need the data segment
	.text                     // start of text segment

// === fpconvert ===
	.global fpconvert         // make fpconvert global so the linker knows about it
	.type fpconvert, %function // define fpconvert to be a function
	.equ FP_OFFSET, 32 	      // (# of saved regs - 1) * 4 rounded up to multiples of 8
fpconvert:
// function prologue (do not edit)
	push {r4-r10, fp, lr}     // save registers to stack
	add fp, sp, FP_OFFSET     // set frame pointer to frame base
// you can use any of r0-r10 inclusive
// r0 is the parameter to the function
// the value of r0 upon bx lr is the value returned from the function

// YOUR CODE BEGINS
// === fpconvert function body ===

	and r4, r0, SIGN_MASK	// r4 = r0 & SIGN_MASK  ; mask out sign bit
	lsl r4, r4, 16			//						; move sign bit to msb
	and r5, r0, EXP_MASK	// r5 = r0 & EXP_MASK   ; mask out exponent bits
	ror r5, r5, 8			//						; move exp bit to lsb
	and r6, r0, MANT_MASK	// r6 = r0 & MANT_MASK	; mask out mantissa bits

// Process infinity case
	cmp r5, 0x7f			// if (r5 >= 0x7f) { 
	blt .Lfinite			// .
	bl convert_infinity		// 		convert_infinity(r0)
	b .Lend					// 		return r0
							// }
// Proces zero case
.Lfinite:			
	cmp r5, 0				// if (r5 == 0) {	
	bne .Lnormal			// .
	cmp r6, 0				//  	if (r6 == 0)
	bne .Lsubnormal			// 		.
	mov r0, r4				// 					   ; set r0 to just sign bit
	b .Lend					// 			return r0
							//		}
// Process nonzero subnormals
.Lsubnormal:	
	mov r1, 1				//		for (int i = 1; i < 9; i++) {
.Lfor:
	lsl r6, r6, 1			//			r6 = r6 << 1
	cmp r6, 0x100			//			if (r6 >= 0x100) {
	blt	.Lcontinue			//			.
	b .Lendfor				//				break
							//			}
.Lcontinue:
	add r1, r1, 1			//		.
	cmp r1, 9				//		.
	blt .Lfor				//		}
.Lendfor:
	mov r2, 65
	sub r5, r2, r1			//		r5 = 65 - i
	lsl r5, r5, 23			//						; move r5 to exponent slot
	and r6, r6, MANT_MASK	//						; re-mask mantissa
	lsl r6, r6, 15
	orr r0, r4, r5			//						; combine fields
	orr r0, r0, r6
	b .Lend					// 		return r0
							// }
// Process normals
.Lnormal:
	sub r5, r5, 63			// r5 = r5 - 63		; convert exponent
	add r5, r5, 127			// r5 = r5 + 127		
	lsl r5, r5, 23			//					; move r5 to exponent slot
	orr r0, r4, r5			//					; combine new components to r0
	lsl r6, r6, 15			//					; .
	orr r0, r0, r6			//					; .

.Lend:
	
// === end fpconvert function body ===
// YOUR CODE ENDS

// function epilogue - do not edit
	sub sp, fp, FP_OFFSET
	pop {r4-r10, fp, lr}      // must match list in prolog's push
	bx lr                     // return
// function footer
	.size fpconvert, (. - fpconvert) // set size for function

// === file footer ===
	.section .note.GNU-stack, "", %progbits // stack/data non-exec (linker)
	.end
