/* Assembler code fragment for LC-2K */ 
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#define MAXLINELENGTH 1000 
char *inFileString, *outFileString;

int readAndParse(FILE *, char *, char *, char *, char *, char *); 
int isNumber(char *); 

int fun_f(char *string, int* anw){
		FILE *inFilePtr2;
		int ret,i,j;
		if(isNumber(string)){
            sscanf(string, "%d", &ret);
			return ret;
        } 
        else{
			inFilePtr2 = fopen(inFileString, "r");
			char label_[MAXLINELENGTH], opcode_[MAXLINELENGTH], arg0_[MAXLINELENGTH]; 
			char arg1_[MAXLINELENGTH], arg2_[MAXLINELENGTH];
			char label__[MAXLINELENGTH], opcode__[MAXLINELENGTH], arg0__[MAXLINELENGTH]; 
            char arg1__[MAXLINELENGTH], arg2__[MAXLINELENGTH];
			
			for(i=0;;i++){
				if (! readAndParse(inFilePtr2, label_, opcode_, arg0_, arg1_, arg2_) ) {
					/* reached end of file */

					printf("%s label not exits\n",string);
					fclose(inFilePtr2);
					*anw = 1;
					return -1;
				}
				if(!strcmp(string,label_)){
					for(j=i+1;;j++){
						 if (!readAndParse(inFilePtr2, label__, opcode__, arg0__, arg1__, arg2__) ) {
							break;
						}

						if(!strcmp(string,label__)){
							printf("%s is duplicated\n",string);
							fclose(inFilePtr2);
							*anw = 1;
							return -1;
						}
					}
					if(strcmp(opcode_,".fill")){
						fclose(inFilePtr2);
						return i;
					}
					else{
						if(isNumber(arg0_)){
							fclose(inFilePtr2);
							return i;
						}
						else{
							fclose(inFilePtr2);
							return fun_f(arg0_,anw);
						}
					}
				
				}
			}
        }
}
int main(int argc, char *argv[]) {
    FILE *inFilePtr, *outFilePtr; 
    char label[MAXLINELENGTH], opcode[MAXLINELENGTH], arg0[MAXLINELENGTH], arg1[MAXLINELENGTH], arg2[MAXLINELENGTH];
    int i,num,n_opcode,n_arg0,n_arg1,n_arg2;
    int* anw;
    int num1 = 0;
    anw = &num1;
	int f = 0;
    if (argc != 3) 
    { 
		printf("error: usage: %s <assembly-code-file> <machine-code-file>\n", argv[0]);
		exit(1);
    }
    inFileString = argv[1];
    outFileString = argv[2];
    inFilePtr = fopen(inFileString, "r");
	if (inFilePtr == NULL) {
		printf("error in opening %s\n", inFileString);
		exit(1);
	}
	outFilePtr = fopen(outFileString, "w");
	if (outFilePtr == NULL) {
		printf("error in opening %s\n", outFileString);
		exit(1);
	}
    /* here is an example for how to use readAndParse to read a line from
    inFilePtr */
	for(i=0;;i++){
		if (! readAndParse(inFilePtr, label, opcode, arg0, arg1, arg2) ) {
			/* reached end of file */
			printf("reached end of file\n");
			goto GOOD;
		}
		

		if(f == 1){
		    goto FILL;
	   }


		
		if(n_arg0 == -1 || n_arg1 == -1 || n_arg2 == -1){
			goto BAD;
		}

	else if(!strcmp(opcode,"add")){
				n_opcode = 0;
				goto R;
	}
	else if(!strcmp(opcode,"nor")){
                n_opcode = 1;
				goto R;
	}
	else if(!strcmp(opcode,"lw")){
                n_opcode = 2;
				goto I;
	}
	else if(!strcmp(opcode,"sw")){
                n_opcode = 3;
				goto I;
	}
	else if(!strcmp(opcode,"beq")){
                n_opcode = 4;
				goto I;
	}
	else if(!strcmp(opcode,"jalr")){
                n_opcode = 5;
				goto J;
	}
	else if(!strcmp(opcode,"halt")){
                n_opcode = 6;
				f = 1;
				goto O;
	}
	else if(!strcmp(opcode,"noop")){

                n_opcode = 7;
				goto O;
	}
	else{
				printf("error in opcode\n");
                goto BAD;
	}

		R: 	
			n_arg0 = fun_f(arg0,anw);
			n_arg1 = fun_f(arg1,anw);
			n_arg2 = fun_f(arg2,anw);
			if(*anw == 1)
			  goto BAD;

			if(((n_opcode >> 3) != 0)||((n_arg0 >> 3) != 0)||((n_arg1 >> 3) != 0)||((n_arg2 >> 3) != 0) ){
				printf("R type instruction error");
                goto BAD;
			}
			num = (n_opcode << 22) + (n_arg0 << 19) + (n_arg1 << 16) + n_arg2;
            fprintf(outFilePtr,"%d\n",num);
			printf("l:%s o:%s 0:%s 1:%s 2:%s\n",label,opcode,arg0,arg1,arg2);
            continue;


		I:
			n_arg0 = fun_f(arg0,anw);
			n_arg1 = fun_f(arg1,anw);
			n_arg2 = fun_f(arg2,anw);
			if(*anw == 1)
			  goto BAD;
		printf("%d\n",n_arg2);
		if(n_arg2 >> 15 == 0x00000 ){
		}
		else if((n_arg2 >> 16)&0xffff == 0xffff ){
			if(n_arg2 >>15 & 0xf == 0xf){
		
			}
			else{
				printf("I type instruction error: unfitted offset\n");
                		goto BAD;
			}
		}
		else{
			printf("I type instruction error: unfitted offset\n");
                	goto BAD;
		}
		n_arg2 = n_arg2&0xffff;
		if(!strcmp(opcode,"beq")){
			  if(!isNumber(arg2)){
					n_arg2 = n_arg2 - (i+1);
					n_arg2 = n_arg2 & 0xffff;
					printf("%d\n",n_arg2);	
				}
			  }

	

            if(((n_opcode >> 3) != 0)||((n_arg0 >> 3) != 0)||((n_arg1 >> 3) != 0)||((n_arg2 >> 16) != 0) ){
                printf("I type instruction error");
                goto BAD;
            }
			
            num = (n_opcode << 22) + (n_arg0 << 19) + (n_arg1 << 16) + n_arg2;
            fprintf(outFilePtr,"%d\n",num);
			printf("l:%s o:%s 0:%s 1:%s 2:%s\n",label,opcode,arg0,arg1,arg2);
            continue;


		J:
			n_arg0 = fun_f(arg0,anw);
			n_arg1 = fun_f(arg1,anw);
			if(*anw == 1)
			  goto BAD;


            if(((n_opcode >> 3) != 0)||((n_arg0 >> 3) != 0)||((n_arg1 >> 3) != 0)){
                printf("J type instruction error");
                goto BAD;
            }
            num = (n_opcode << 22) + (n_arg0 << 19) + (n_arg1 << 16);
            fprintf(outFilePtr,"%d\n",num);
			printf("l:%s o:%s 0:%s 1:%s\n",label,opcode,arg0,arg1);
			continue;


		O:
			if(((n_opcode >> 3) != 0)){
				printf("O type instruction error");
				goto BAD;
			}
			num = n_opcode << 22;
			fprintf(outFilePtr,"%d\n",num);
			printf("l:%s o:%s\n",label,opcode);
			continue;
		FILL:
			n_arg0 = fun_f(arg0,anw);


			if(strcmp(opcode,".fill")){
				printf("%s syntax error\n",label);
			}
			n_arg0 = fun_f(arg0,anw);
			num = n_arg0;
            fprintf(outFilePtr,"%d\n",num);
			printf("l:%s o:%s 0:%s\n",label,opcode,arg0);
            continue;	
		BAD:
			fclose(inFilePtr);
            fclose(outFilePtr);
            exit(1);


		GOOD:
            fclose(inFilePtr);
            fclose(outFilePtr);
            exit(0);

	}
    /* this is how to rewind the file ptr so that you start reading from the
    beginning of the file */
    //rewind(inFilePtr);
    /* after doing a readAndParse, you may want to do the following to test the
    opcode */
    //if (!strcmp(opcode, "add")) {
    /* do whatever you need to do for opcode "add" */
    //}
    
    //fprintf(outFilePtr,"%d\n",num);
    return(0);
}
/*
* Read and parse a line of the assembly-language file. Fields are returnedx
* in label, opcode, arg0, arg1, arg2 (these strings must have memory already
* allocated to them).
*
* Return values:
*
0 if reached end of file
*
1 if all went well
*
* exit(1) if line is too long.
*/
int 
readAndParse(FILE *inFilePtr, char *label, char *opcode, char *arg0,
char *arg1, char *arg2)
{ 
    char line[MAXLINELENGTH];
    char *ptr = line; 
    /* delete prior values */ 
    label[0] = opcode[0] = arg0[0] = arg1[0] = arg2[0] = '\0'; 
    /* read the line from the assembly-language file */ 
    if (fgets(line, MAXLINELENGTH, inFilePtr) == NULL) 
    {
        /* reached end of file */ 
        return(0);
    }
    /* check for line too long (by looking for a \n) */ 
    if (strchr(line, '\n') == NULL) 
    { 
        /* line too long */ 
        printf("error: line too long\n"); 
        exit(1);
    }

    /* is there a label? */ 
    ptr = line; 
    if (sscanf(ptr, "%[^\t\n\r ]", label)) 
    { 
        /* successfully read label; advance pointer over the label */ 
        ptr += strlen(label);
    }
    /* * Parse the rest of the line. Would be nice to have real regular * expressions, but scanf will suffice. */
    sscanf(ptr, "%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]", opcode, arg0, arg1, arg2);
    return(1);
} 
int isNumber(char *string) {
    /* return 1 if string is a number */
    int i; 
    return( (sscanf(string, "%d", &i)) == 1);
}
