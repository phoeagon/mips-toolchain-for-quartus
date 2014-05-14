.globl	_start
 
.text
_start:
	xor $2,$2
	addi $2, $2, 0x100
	xor $sp,$sp
	//addi $sp,$sp, 0x518
	nop
	jr $2
	

