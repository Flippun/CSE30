// CES30 assignment template
// 
// Describe target Hardware to the assembler
.arch   armv6
.cpu    cortex-a53
.syntax unified
/////////////////////////////////////////////////////////

.text                       // start of the text segment
/////////////////////////////////////////////////////////
// function hash_asm
/////////////////////////////////////////////////////////
.type   hash_asm, %function  // define as a function
.global hash_asm             // export function name
.equ    FP_OFFSET, 28       // (regs - 1) * 4
/////////////////////////////////////////////////////////

// put any .equ for hash_asm here - delete this line

/////////////////////////////////////////////////////////

hash_asm:
    push    {r4-r9, fp, lr}     // use r4-r9 protected regs
    add     fp, sp, FP_OFFSET   // locate our frame pointer
    // DO NOT EDIT PROLOGUE ABOVE
    // You can use temporary r0-r3 and preserved r4-r9
    // Store return value (results) in r0
    ///////////////////////////////////////////////////////
    
    LSL R2, R1, #5
	ADD R2, R2, R1
	ADD R0, R2, R0
    
    ///////////////////////////////////////////////////////
    // DO NOT EDIT EPILOGUE BELOW
    sub     sp, fp, FP_OFFSET   // restore sp
    pop     {r4-r9, fp, lr}     // restore saved registers
    bx      lr                  // function return
    .size   hash_asm,(.-hash_asm)
