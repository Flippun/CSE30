// === file header ===
	.arch armv6               // armv6 architecture
	.cpu cortex-a72           // our CPU model
	.arm                      // arm 32-bit IS
	.fpu vfp                  // floating point co-processor
	.syntax unified           // modern syntax
// === definitions applying to the entire source file ===
	// .data                  // uncomment if you need the data segment
	.text                     // start of text segment

// === convert_infinity ===
// Returns a 32-bit IEEE +Inf or -Inf.
	.global convert_infinity
	.type convert_infinity, %function
	.equ FP_OFFSET, 32 	       // (# of saved regs - 1) * 4 rounded up to multiples of 8
convert_infinity:
// you should not depend on the values of r1-r3 because convert_infinity takes no arguments
	mov r1, 28
	mov r2, 61
	mov r3, 5
// function prologue (do not edit)
	push {r4-r10, fp, lr}    // save regs
	add fp, sp, FP_OFFSET
// you can use any of r0-r10 inclusive
// R0 is the parameter to the function
// the last value of R0 is the value
// returned from the function
// r4-r10 are local to this function
// changes to these values will not be reflected
// in the main function.

// YOUR CODE BEGINS
// === convert_infinity function body ===

	ldr r4, =0x8000				// r4 = 0x8000
	ldr r5, =0x7f80				// r5 = 0x7f80

	and r0, r0, r4				//		; mask out sign bit
	orr r0, r0, r5				//		; set all exponent of r0 to 1
	lsl r0, 16					//		; move to 32-bit format

// === end convert_infinity function body ===
// YOUR CODE ENDS

// function epilogue (do not edit)
	sub	sp, fp, FP_OFFSET
	pop {r4-r10, fp, lr}       // restore regs
	bx lr                      // return
// function footer
	.size convert_infinity, (. - convert_infinity)

// === file footer ===
	.section .note.GNU-stack, "", %progbits // stack/data non-exec (linker)
	.end
