#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAIN_MEM_LEN 64000

/* Global variable for main memory. 
 * 4k*16 bit=64000 places. (assuming a word here is 16 bits?) -Ryan
 */
char mainMemory[MAIN_MEM_LEN];

/* We can change these from global variables later, if we wish. We'll want an auxiliary function to initialise all of these and the main memory
 * I honestly don't remember what most of these do. -Ryan
 */
char AC[16]; /*accumulator*/
char IR[16]; /*instruction register*/
char MBR[16]; /*memory buffer register*/
char PC[12]; /*program counter*/
char MAR[12]; /*memory address register*/

/*We also need input/output registers. I'll set these to 128 bits for now, but we need to decide later how big to make these. -Ryan*/
char inREG[128];
char outREG[128];

/*Auxiliary functions from part 2 of document*/
//Still to do
void load_content(void);
//Still to do
int int_to_binary(int integer); /*left return type as int for now.*/
//Still to do
int binary_to_int(int binary);
//Done
void display_memory(void); /*change from void later*/
//Still to do
void convertDisplay_assembly(void); /*change from void later*/
//Still to do
void user_mem_input(void); /*not sure if return type is void here*/
//Work in progress
void load_file_instruction(void); /*Is void the parameter here, or can we use a file as parameter?*/

/*From part 3. Document says "Write a C	function" so I think it only needs the one function, with assistance from the above auxiliaries.*/
//Still to do
void fetch_decode_execute(void);

void initialise(void);

/*Define Instruction Functions, feel free to rename and correct as you like*/
//I think they are all void, given all our globals, unless we pass them the current opcode and operand
//someone please verify
//also should we just name the functions, the mnemonics we gave them?
void loadX(void);
void storeX(void);
void subtX(void);
void addX(void);
void input(void);
void output(void);
void halt(void);
void skipcond(void);
void jumpX(void);

void andX(void);
void orX(void);
void multX(void);


/*main is part 4*/
//Still to do
int main(char argv){
    //on terminal, we would type ./program -f, if we want to read from file

	if ( ! strcmp(argv[1], "-f")) {
		printf("Reading contents from file into memory\n");
		load_file_instruction();
		//load_file_instruction should take filename maybe?
		//load_file_instruction(filename);
	}
	else if ( ! strcmp(argv[1], "-d")) {
		printf("Loading default content into memory.\n");   
		initialise();
		//Our default memory is all 0's
	}
	else if ( ! strcmp(argv[1], "-c")) {
		printf("Reading user input to be stored into memory.\n");
		user_mem_input();
	}
	else{
	    printf("Invalid command line. /n");
	    return 0;
	}
	//now that we have loaded memeory, we must execute the program stored in memory
	//starting at address location 0
	
	//once done, we must print the contents of memory and the value of the Accumulator 
	//after execution on the screen
	
	return 0;
}

void determineInstruction(void){
    //Basic outline
    
    //Take Binary Opcode of 4 bits and convert to decimal
    //binary_to_int(current opcode);
    //I'm pretty sure in the lecture he wanted us to determine what instruction to used from comparting decimals
    
    
    switch(opcodeDecimal){
	case 0:
		halt();
		break;
	case 1:
		loadX();
		break;
	case 2:
		storeX();
		break;
	case 3:
		subtX();
		break;
	case 4:
		addX();
		break;
	case 5:
		input();
		break;
	case 6:
		output();
		break;
	case 7:
		skipcond();
		break;
	case 8:
		jumpX());
		break;
	case 9:
		andX();
		break;
	case 10:
		orX();
		break;
	case 11:
		multX();
		break;
}



//initialises the main memory to all nulls, and the registers to all 0s
void initialise(void){
    
    int i;
	for(i = 0; i<MAIN_MEM_LEN; i++){
		mainMemory[i] = '\0';
	}
    for(i = 0; i<16; i++){
		AC[i] = '0';
		IR[i] = '0';
		MBR[i] = '0';
		if(i<12){
		    PC[i] = '0';
		    MAR[i] = '0';
		}
	}
}

/* Function should display the memory contents on screen and their respective memory locations
 * This works when I gave it memory contents composed of random binary digits.
 * Memory address is output in the form of a 7-digit number, eg: "4223104". If this is the wrong format for an address, let me know. -Ryan
 */
void display_memory(void){

	printf("ADDRESS|MEMORY CONTENTS\n");
	int i = 0, j;
	while(mainMemory[i] != '\0'){
		for(j=0; j<16; j++){
			if(j == 0){
				printf("%d", &mainMemory[i]);
				printf(" ");
			}
			printf("%c", mainMemory[i]);
			i++;
		}
		printf("\n");
	}
}

/*Changed function name to match above -Ryan*/
void load_file_instruction()
{
	FILE *binaryFile;
	char buff;
	
	binaryFile = fopen("FILE LOCATION HERE", "rb");
    if (!binaryFile) /* binary file does not exist */
	{
    	printf("Unable to open the file as it does not exist");
    	return;
	}
	
	/* some code below I think might help get us the size of the file */
	fseek(binaryFile, 0, SEEK_END);
	length = ftell(binaryFile);
	buffer = length;
	
	
    /*Sorry, I changed the layout of the below section to make it more readable. I hope you don't mind. -Ryan*/
    if(length/12 != 0){
	    printf("invalid file");
    	return;
    }
    	
    for(int i=0;i<length;i++){
        for(int i=0;i<12;i++){
            int digit = fgetc( FILE * binaryFile );
            if (digit != 0 && digit != 1){
    	        printf("invalid file");
    	        return;
	        }
	        else{
		// ADD DIGIT TO ITEM IN ARRAY
	        }
	    }		
    }
	fclose(binaryFile);
}

/* WORK IN PROGRESS - USER INPUT VALIDATOR */


void user_mem_input() {
  int getNext = 1;
  int inputLength;
  char input[100];
  int invalidCounter;

  while (getNext == 1) {

    printf("Enter a binary 16 bit value into the program: ");
    /* scan in the user input */
    scanf("%s", input);

    inputLength = strlen(input);
    printf("THE INPUT LENGTH IS %i \n", strlen(input));

    while (inputLength != 16) {
      printf("please enter an instruction which is 16 bits long: ");
      scanf("%s", input);
      inputLength = strlen(input);
      printf("\n THE INPUT LENGTH IS %i \n", strlen(input));

    }

    for (int i = 0; i < inputLength; i++) {
      /* IF the value specified in the index is not null */
      if (input[i] != 0 || input[i] != 1) {
        /* increment the 'correct counter' */
        invalidCounter++;
      }
    }

    while (invalidCounter > 0) {
      invalidCounter = 0;
      printf("please enter an instruction comprised of binary (1's and 0's) digits: \n");
      scanf("%s", input);
      inputLength = strlen(input);
      printf("\n THE INPUT LENGTH IS %i \n", strlen(input));
      for (int i = 0; i < inputLength; i++) {
        /* IF the value specified in the index is not null */
        if (input[i] == 0 || input[i] == 1) {
          /* increment the 'correct counter' */
          invalidCounter++;
        }
      }
    }

    printf("enter another 16 bit instruction into memory?");
    printf("\n 0: NO \n 1: YES \n");
    scanf("%i", getNext);
    while (getNext != 0 && getNext != 1) {
      printf("please enter a 16 bit integer comprised entirely of binary (1's and 0's) digits: ");
      scanf("%i", input);
    }
  }

}

//INSTRUCTIONS

