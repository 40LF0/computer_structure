	lw 0 1 five	reg 1 has a 5
	lw 0 2 five	reg 2 has a 5
	lw 0 3 one	reg 3 has a 1	
	noop  
	noop 
	noop 
	nor 1 2 4	reg 4 has a 5 nor 5
	noop  
	noop 
	noop 
	add 4 3 5	reg 5 value is reverse of reg1 value
	noop  
	noop 
	noop 
        sw 0 5 ans	save reg 5 to ans // nor operation works fine
done	halt
five	.fill 5
one	.fill 1
ans	.fill -1 
