#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#define OPT 0xF000
#define OPR 0xFFF

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


void loadFile(const char* filename);
void printMemory();
void disassemble();
void execute();

uint16_t mainMemory[4000];
int16_t AC = 0; /*accumulator*/
uint16_t IR = 0; /*instruction register*/
uint16_t MBR = 0; /*memory buffer register*/
uint16_t PC = 0; /*program counter (12 bit)*/
uint16_t MAR = 0; /*memory address register (12 bit)*/
int16_t INPUT = 0;
int16_t OUTPUT = 0;

int main(void)
{
	loadFile("/mnt/c/Users/zwick/Desktop/ace/testMem.txt");
	//printMemory();
	//disassemble();
	execute();
	return 0;
}

void execute()
{
	for(PC = 0; PC < 4000; PC++)
	{
		IR = mainMemory[PC];
		uint8_t opt = (IR & OPT) >> 12;
		MAR = IR & OPR;
		MBR = mainMemory[MAR];
		switch(opt)
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
			case SKP:
				// to be implemented
				break;
			case JMP:
				PC = MAR;
				break;
			default:
				break;
		}
	}
}

void disassemble()
{
	int i;
	for(i = 0; i < 4000; i++)
	{
		uint8_t opt = (mainMemory[i] & OPT) >> 12;
		uint16_t opr = mainMemory[i] & OPR;
		if(opt == HLT) break;
		switch(opt)
		{
			case LDR:
				printf("LDR %d\n", opr);
				break;
			case STO:
				printf("STO %d\n", opr);
				break;
			case SUB:
				printf("SUB %d\n", opr);
				break;
			case ADD:
				printf("ADD %d\n", opr);
				break;
			case INP:
				printf("INP\n");
				break;
			case OUT:
				printf("OUT\n");
				break;
			case SKP:
				printf("SKP\n");
				break;
			case JMP:
				printf("JMP %d\n", opr);
				break;
			default:
				break;
		}
	}
	printf("HLT\n");
}

void printMemory()
{
	int i;
	for(i = 0; i<10; i++)
	{
		printf("%d: ", i);
		int j;
		for(j = 15; j>=0; j--)
		{
			int num = mainMemory[i] >> j;
			if(num & 1)
			{
				printf("1");
			}
			else
			{
				printf("0");
			}
		}
		printf("\n");
	}
}

void loadFile(const char* filename)
{
	FILE *binaryFile;
	char buff;
	int lengthCounter;
	
	binaryFile = fopen(filename, "r");
    if (!binaryFile) /* binary file does not exist */
	{
    	printf("Unable to open the file as it does not exist\n");
    	return;
	}

	int mem_index = 0;
	while(!feof(binaryFile) && mem_index < 4000)
	{
		while(!feof(binaryFile))
		{
			char c = fgetc(binaryFile);
			if(c == '1')
			{
				mainMemory[mem_index] <<= 1;
				mainMemory[mem_index] |= 1;
				lengthCounter ++;
			}
			else if(c == '0')
			{
				mainMemory[mem_index] <<= 1;
				lengthCounter++;
			}
			else if(c == ',')
			{
			  break;
			}
			else
			{
				fgetc(binaryFile);
			}
		}
		mem_index++;
	}
	fclose(binaryFile);
	return;
}
		

