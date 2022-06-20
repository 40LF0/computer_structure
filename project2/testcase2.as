	lw 0 1 one  //lw operation works fine
 	lw 0 2 two
	noop  
	noop  
	noop  
start	add 1 2 6  
	noop  
	noop  
	noop  
	sw 0 6 ans  //add operation and sw operation works fine
done	halt
one	.fill 1
two	.fill 2
three	.fill 3
four	.fill 4
five	.fill 5
ans	.fill -1
