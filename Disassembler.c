
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Auxiliary functions from part 2 of document*/
void load_content(void);
int int_to_binary(int integer); /*left return type as int for now.*/
int binary_to_int(int binary);
void display_memory(void); /*change from void later*/
void convertDisplay_assembly(void); /*change from void later*/
void user_mem_input(void); /*not sure if return type is void here*/
void load_file_instruction(void); /*Is void the parameter here, or can we use a file as parameter?*/

/*From part 3. Document says "Write a C	function" so I think it only needs the one function, with assistance from the above auxiliaries.*/
void fetch_decode_execute(void);

/*main is part 4*/
int main(void){
	return 0;
}
