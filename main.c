/**************************************************************************
 * Assessment Title:
 *
 *
 * Number of Submitted C Files: 1
 *
 *
 * Date: 24/11/2017
 *
 *
 * Authors:
 *	1. Ryan Baillie, Reg no: 201603243
 *	2. Paul Dannenberg, Reg no: 201645284
 *	3. Kevin Green, Reg no: 201614681
 *	4. Maisie McGregor, Reg no: 201739203
 *
 *
 *	Statement: We confirm that this submission is all our own work.
 *
 *	(Signed)_____________________________________Ryan Baillie
 *
 * 	(Signed)_____________________________________Paul Dannenberg
 *
 *	(Signed)_____________________________________Kevin Green
 *
 *	(Signed)_____________________________________Maisie McGregor
 *
 **************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#define OPR 0xFFF // 0000 1111 1111 1111 bitmask to get operand

// instructions
#define HLT 0
#define LDR 1
#define STO 2
#define SUB 3
#define ADD 4
#define AND 5
#define OR 6
#define SKP 7
#define JMP 8
#define INP 9
#define OUT 10
#define MUL 11
#define ADDI 12
#define SUBI 13
#define SLL 14
#define SRL 15

void loadFile(const char* filename);
void initialise();
void printMemory();
void user_mem_input();
void disassemble();
void execute();
void load_default();
char* int_to_string(int16_t input);


// int16_t => exactly 16 bits (more portable), u => unsigned
uint16_t mainMemory[4000]; // main memory array
int16_t AC; // accumulator
uint16_t IR; // instruction register
int16_t MBR; // memory buffer register
uint16_t PC; // program counter (12 bit)
uint16_t MAR; // memory address register (12 bit

int16_t s; // used for sign extension

/*
 * Main function, entry point
 * Checks for command line arguments and calls functions based on arguments
 * Parameters: argc, argv
 */
int main(int argc, char** argv)
{
	if(argc <= 1)
	{
		printf("Invalid command.\n");
		printf("please enter one of the following:\n");
		printf("-f: read contents from file into memory\n");
		printf("-d: load default contents into memory\n");
		printf("-c: read user input into memory\n\n");
		return 0;
	}

	initialise();
	
	if(argv[1][0] == '-' && argv[1][1] == 'f')
	{
		printf("Reading contents from file into memory\n");
		loadFile(argv[2]);
	}
	else if(argv[1][0] == '-' && argv[1][1] == 'd')
	{
		printf("Loading default content into memory.\n");
		load_default();
	}
	else if (argv[1][0] == '-' && argv[1][1] == 'c')
	{
		printf("Reading user input to be stored into memory.\n");
		user_mem_input();
	}
	printf("\n");
	execute();
	printf("\n");
	printMemory();
	printf("\n");
	disassemble();
	return 0;
}

/*
 * Initialises main memory and registers to 0
 */
void initialise(void)
{
	int i;
	for(i = 0; i < 4000; i++)
	{
		mainMemory[i] = 0;
	}
	AC = 0;
	IR = 0;
	MBR = 0;
	PC = 0;
	MAR = 0;
}

/*
 * Executes instructions in memory
 */
void execute()
{
	for(PC = 0; PC < 4000; PC++)
	{
		IR = mainMemory[PC]; // put instruction into IR
		uint8_t opt = IR >> 12; // extract optcode using bitmask (shift right by 12 to get rid of operand and keep 4 MSBs)
		MAR = IR & OPR; // use bitmask to make 4 MSBs zero => extract operand
		memcpy(&MBR, &mainMemory[MAR], 17);
		//MBR = mainMemory[MAR]; // get memory content at address MAR
		switch(opt) // execute instruction
		{
			case LDR:
				AC = MBR;
				break;
			case STO:
				mainMemory[MAR] = AC;
				break;
			case SUB:
				AC -= MBR;
				break;
			case ADD:
				AC += MBR;
				break;
			case INP:
				printf("Input: ");
				scanf("%" SCNd16, &AC);
				break;
			case OUT:
				printf("Output: %" PRId16 "\n", AC);
				break;
			case MUL:
				AC *= MBR;
				break;
			case SKP:
				if(AC != 0)
				{
					PC += 1;
				}
				break;
			case JMP:
				PC = MAR;
				break;
			case ADDI:
				s = MAR << 4;
				s = s >> 4;
				AC += s;
				break;
			case SUBI:
				s = MAR << 4;
				s = s >> 4;
				AC -= s;
				break;
			case SLL:
				AC = AC << MAR;
				break;
			case SRL:
				AC = AC >> MAR;
				break;
			case AND:
				AC = AC & MBR;
				break;
			case OR:
				AC = AC | MBR;
				break;
			default:
				break;
		}
	}
}

/*
  Converts machine language to assembly
*/
void disassemble()
{
	for(int i = 0; i < 4000; i++)
	{
		uint8_t opt = mainMemory[i] >> 12; // extract optcode
		uint16_t opr = mainMemory[i] & OPR; // extract operator
		if(opt == HLT) break;
		switch(opt) // print instructions
		{
			case LDR:
				printf("LDR\t%d\n", opr);
				break;
			case STO:
				printf("STO\t%d\n", opr);
				break;
			case SUB:
				printf("SUB\t%d\n", opr);
				break;
			case ADD:
				printf("ADD\t%d\n", opr);
				break;
			case INP:
				printf("INP\n");
				break;
			case OUT:
				printf("OUT\n");
				break;
			case MUL:
				printf("MUL\t%d\n", opr);
				break;
			case SKP:
				printf("SKP\n");
				break;
			case JMP:
				printf("JMP\t%d\n", opr);
				break;
			case ADDI:
				s = opr << 4;
				s = s >> 4;
				printf("ADDI\t%d\n", s);
				break;
			case SUBI:
				s = opr << 4;
				s = s >> 4;
				printf("SUBI\t%d\n", s);
				break;
			case SLL:
				printf("SLL\t%d\n", opr);
				break;
			case SRL:
				printf("SRL\t%d\n", opr);
				break;
			case AND:
				printf("AND\t%d\n", opr);
				break;
			case OR:
				printf("OR\t%d\n", opr);
			default:
				break;
		}
	}
	printf("HLT\n");
}

/*
 * Prints memory contents with addresses
 */
void printMemory()
{
	int until = 0;
	for(int i = 0; i<4000; i++)
	{
		if(mainMemory[i] != 0)
		{
			until = i;
		}
	}
	if(until % 2 == 0)
	{
		until +=2;
	}
	else
	{
		until++;
	}
	printf("ADDRESS\tMEMORY\tADDRESS\tMEMORY\n");
	int i = 0;
	while(i < until)
	{
		printf("0x%x\t", i);
		printf("%s\t", int_to_string(mainMemory[i]));
		printf("0x%x\t", i+1);
		printf("%s\n", int_to_string(mainMemory[i+1]));
		i += 2;
	}
}

/*
 * Loads a file into memory
 * Parameters: filename
 */
void loadFile(const char* filename)
{
	FILE *binaryFile;

	binaryFile = fopen(filename, "r");
    if (!binaryFile) /* binary file does not exist */
	{
    	printf("Unable to open the file as it does not exist\n");
    	return;
	}

	int mem_index = 0;
	while(!feof(binaryFile) && mem_index < 4000) // loop through memory locations, stop if full
	{
		while(!feof(binaryFile)) // loop through chars in file
		{
			char c = fgetc(binaryFile);
			if(c == '1')
			{
				mainMemory[mem_index] <<= 1; // XXXX XXXX XXXX XXXX -> XXXX XXXX XXXX XXX0
				mainMemory[mem_index] |= 1; // XXXX XXXX XXXX XXX0 -> XXXX XXXX XXXX XXX1
			}
			else if(c == '0')
			{
				mainMemory[mem_index] <<= 1; // XXXX XXXX XXXX XXXX -> XXXX XXXX XXXX XXX0
			}
			else if(c == ',') // next memory location
			{
				break;
			}
			else // skip invalid char
			{
				fgetc(binaryFile);
			}
		}
		mem_index++; // increment address index
	}
	fclose(binaryFile);
	return;
}

/*
 * Allows the user to input to memory directly
 */
void user_mem_input()
{
	// declare and initialise variables for storing the value of user's
	// 'get next' choice, the input length, and input itself
	int mem_index = 0;
	// while the user has chosen to enter another instruction
	while (1)
	{
		char input[17] = {};
		// prompt user input
		printf("Enter a binary 16 bit values line by line, type R to run the program: ");
		// scanner takes in user input
		scanf(" %17s", input);
		// exit condition
		if(input[0] == 'R')
		{
			break;
		}
		// for each character in the sixteen bit instruction
		for(int i = 0; i < 16; i++)
		{
			char c = input[i];
			if(c == '1')
			{
				mainMemory[mem_index] <<= 1; // XXXX XXXX XXXX XXXX -> XXXX XXXX XXXX XXX0
				mainMemory[mem_index] |= 1; // XXXX XXXX XXXX XXX0 -> XXXX XXXX XXXX XXX1
			}
			else if(c == '0')
			{
				mainMemory[mem_index] <<= 1; // XXXX XXXX XXXX XXXX -> XXXX XXXX XXXX XXX0
			}
			else // invalid input
			{
				printf("Invalid input.\n");
				mem_index--;
				break;
			}
		}
		mem_index++;
    }
}

/*
 * Loads default program into memory
 */
void load_default()
{
	mainMemory[0] = (1 << 12) + 3;
	mainMemory[1] = (10 << 12);
	mainMemory[2] = 0;
	mainMemory[3] = 42;
}

/*
 * Converts int16_t to binary string
 */
char* int_to_string(int16_t input)
{
	static char str[17];
	int j = 0;
	for(int i = 15; i>=0; i--)
	{
		int num = input >> i;
		if(num & 1)
		{
			str[j] = '1';
		}
		else
		{
			str[j] = '0';
		}
		j++;
	}
	str[17] = '\0';
	return str;
}