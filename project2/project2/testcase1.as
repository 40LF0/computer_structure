        lw      0 1 five    
        lw      0 2 neg1       
start   add     1 2 3       // data hazard! register 1,2 is not updated yet when start instruction excuted in ex stage // reg3 should be 4  but, because of data hazard, reg1 value is 0(reg1 is not updated)+0(reg2 is not updated) = 0;
done    halt            
five    .fill   5 
neg1	.fill	-1 
