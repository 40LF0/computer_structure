	lw 0 1 five
	lw 0 2 ne1
start	jalr 7 7
	add 1 2 1
	beq 0 1 2
	beq 0 0 start
	noop
done	halt
five	.fill 5
ne1	.fill -1
