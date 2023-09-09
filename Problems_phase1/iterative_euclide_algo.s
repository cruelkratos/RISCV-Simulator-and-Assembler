main:
	andi t0 , t0 ,0
	andi t1 , t1 ,0
	la a0 , 0x7B7A7971
	lw t0 0(a0)
	andi a0 , a0 , 0
	la a0  ,0x7F7E7D7C
	lw t1 0(a0)
beq t1 , t2 , endo
loop:
	
blt t2 , t1 , sub2
sub t2 , t2 , t1
	sub2:
	sub t1 , t1 , t2	
bne t1 , t2 , loop

endo:
sw t1 , 4(a0)

