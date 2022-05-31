	lw 0 6 arg_max	Load arg_max to reg 6 (symbolic) 
	lw 0 7 arg_min	Load arg_min to reg 7 (symbolic) 
	lw 6 6 32767 	load 0 to reg 6 (numeric) 
	beq 3 6 1	
	sw 0 3 check	# instruction cannnot be executed. 
	lw 7 7 -32768 	load 0 to reg 7 (numeric) 
	beq 3 6 1	 
	sw 0 3 check	# instruction cannnot be executed. 
	noop
done 	halt  
zero .fill 0  
arg_max .fill -32757  	#to test max offest value 32767 
arg_min .fill 32778  	#to test min offest value -32768 
five	.fill 5 
check .fill 1		# check value is always 1 
