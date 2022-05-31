/* LC-2K Instruction-level simulator */
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#define NUMMEMORY 65536 /* maximum number of words in memory */ 
#define NUMREGS 8 /* number of machine registers */ 
#define MAXLINELENGTH 1000

typedef struct stateStruct { 
    int pc; 
    int mem[NUMMEMORY]; 
    int reg[NUMREGS]; 
    int numMemory;
} stateType;

void printState(stateType *); 
int main(int argc, char *argv[]) {
    char line[MAXLINELENGTH];
    stateType state; 
    FILE *filePtr; 
    stateType *statePtr = malloc(sizeof(stateType));
	int instr_num;
    if (argc != 2) { 
        printf("error: usage: %s <machine-code file>\n", argv[0]); 
        exit(1);
    } 
    filePtr = fopen(argv[1], "r"); 
    if (filePtr == NULL) { 
        printf("error: can't open file %s", argv[1]); 
        perror("fopen"); 
        exit(1);
    }
    /* read in the entire machine-code file into memory */ 
    for (state.numMemory = 0; fgets(line, MAXLINELENGTH, filePtr) != NULL; 
        state.numMemory++) {
        if (sscanf(line, "%d", state.mem+state.numMemory) != 1) { 
            printf("error in reading address %d\n", state.numMemory); 
            exit(1);
        } 
        printf("memory[%d]=%d\n", state.numMemory, state.mem[state.numMemory]); 
		 statePtr->mem[state.numMemory]=state.mem[state.numMemory];
	}
	statePtr->numMemory = state.numMemory;
	
	for(instr_num = 1;;instr_num++){
		int pc = statePtr->pc;
		int instr = statePtr->mem[pc];
			printState(statePtr);
			int regA,regB,destReg,offsetField;
			switch((instr>>22)&0b111){
				case 0 :
					regA = (instr>>19)&0b111;
					regB = (instr>>16)&0b111;
					destReg = instr&0b111;
					statePtr->reg[destReg] = 
						statePtr->reg[regA]+statePtr->reg[regB];
					statePtr->pc ++;
					break;
				case 1 :
                    regA = (instr>>19)&0b111;
                    regB = (instr>>16)&0b111;
                    destReg = instr&0b111;
					statePtr->reg[destReg] =
                        ~(statePtr->reg[regA]|statePtr->reg[regB]);
                    statePtr->pc ++;
					break;
                case 2 : 
                    regA = (instr>>19)&0b111;
                    regB = (instr>>16)&0b111;
                    offsetField = instr&0xFFFF;
					statePtr->reg[regB] = 
						statePtr->mem[offsetField + statePtr->reg[regA]];
					statePtr->pc ++;
                    break;
                case 3 :
                    regA = (instr>>19)&0b111;
                    regB = (instr>>16)&0b111;
                    offsetField = instr&0xFFFF;
                    statePtr->mem[offsetField + statePtr->reg[regA]] =
						statePtr->reg[regB];
                    statePtr->pc ++;					
                    break;
                case 4 : 
					statePtr->pc ++;
                    regA = (instr>>19)&0b111;
                    regB = (instr>>16)&0b111;
                    offsetField = instr&0xFFFF;
					int off = offsetField;
					if((offsetField>>15)&0b1==1){
						off = (-offsetField)&0xFFFF;
						off = -off;
					}
					if(statePtr->reg[regA] == statePtr->reg[regB]){
						statePtr->pc = statePtr->pc + off;
						printf("off%d %d\n",offsetField,off);
					}
                    break;
                case 5 :
                    regA = (instr>>19)&0b111;
                    regB = (instr>>16)&0b111;
					statePtr->reg[regB] = statePtr->pc + 1;
					statePtr->pc = statePtr->reg[regA];
                    break;
				case 6 :
					statePtr->pc ++;
					printf("machine halted\n");
					printf("total of %d instructions executed\n",instr_num);
					printf("final state of machine:\n");
					printState(statePtr);
					return(0);
                case 7 :
					statePtr->pc ++;
                    break;
				default:
						printf("wrong\n");
						return(0);
			}
			
		
	}
	printf("wrong\n");
    
 
    return(0); 
}

void printState(stateType *statePtr){ 
    int i;
    printf("\n@@@\nstate:\n"); 
    printf("\tpc %d\n", statePtr->pc); 
    printf("\tmemory:\n"); 
    for (i=0; i<statePtr->numMemory; i++) { 
        printf("\t\tmem[ %d ] %d\n", i, statePtr->mem[i]);
    }
    printf("\tregisters:\n"); 
    for (i=0; i<NUMREGS; i++) { 
        printf("\t\treg[ %d ] %d\n", i, statePtr->reg[i]);
    } 
    printf("end state\n");
}
