.globl	_start
 
.text
_start:
	xor $2,$2
	addi $2, $2, 0x100
	xor $sp,$sp
	jr $2
	

