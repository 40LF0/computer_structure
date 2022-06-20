	lw 0 1 one
	noop 
	noop 
	noop 
start	beq 0 0 3 
	noop 
	sw 0 1 ans  // sw instruction is not executed!
	noop 
done halt   	// branch instruction works fine!
one .fill 1 
ans .fill 0 
