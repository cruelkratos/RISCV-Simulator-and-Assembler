main:
	andi t0 , t0 , 0
	la a0 , 0XFFFFFFFF
	lw t0 , 0(a0)
	andi t1 , t1 ,0
	addi t1 , t1 ,1 
	andi t2 , t2 ,0
	addi t2 , t2 , 2
loop:
	mul t1 , t1 , t2
	addi t2 , t2 , 1
	bne t0 , t2 , loop
sw t1 , 4(a0)
 
