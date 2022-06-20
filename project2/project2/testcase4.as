	lw 0 1 one
	noop 
	noop 
	noop 
start	beq 0 0 3 // branch harzard! Because comparing two register value is executed in EX stage and decide target instruction in MEM stage, pipelining processor don't know what is next instruction of beq instruction before beq is in MEM stage.
	add 1 1 1 // should not be executed
	add 1 1 2 // should not be executed
	add 1 1 3 // should not be executed
done halt 
one .fill 1 

