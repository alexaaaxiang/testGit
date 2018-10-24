#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "InstrUtils.h"
#include "Utils.h"

int identifier(Instruction *head);
void optimizer(Instruction *head);

int main()
{
	Instruction *head;

	head = ReadInstructionList(stdin);
	if (!head) {
		WARNING("No instructions\n");
		exit(EXIT_FAILURE);
	}
	/* YOUR CODE GOES HERE */
	Instruction *curr;
	/*
	Instruction *ptr;
	Instruction *tail;*/
	
	/*
	ptr = (Instruction *)malloc(sizeof(Instruction));
	*/
	curr = head;
	/*tail = LastInstruction(head);*/

	/*
	while(curr->next != NULL){
		if(curr->opcode == READ){
			curr->critical = 'k';
		}
		if(curr->opcode == WRITE){
			curr->critical = 'k';
		}
		if(curr->opcode == STORE){
			curr->critical = 'k';
		}
		curr = curr->next;
	}
	while(curr->prev != NULL){
		curr = curr->prev;
	}
	*/


	while(identifier(curr)){
		optimizer(curr);
		head = curr;
	}

	if (head) {
		PrintInstructionList(stdout, head);
		DestroyInstructionList(head);
	}
	

	return EXIT_SUCCESS;
}

int identifier(Instruction *head){
	Instruction *first;
	Instruction *second;
	Instruction *third;

	
	first = head;
	second = head->next;
	third = head->next->next;

	if(first == NULL || second == NULL || third == NULL){
		return 0;
	}else{
		while(third != NULL){
			if(first->opcode != LOADI){
				third = third->next;
				second = second->next;
				first = first->next;
				continue;
			}
			if(second->opcode != LOADI){
				third = third->next;
				second = second->next;
				first = first->next;
				continue;
			}
			if(third->opcode == ADD || third->opcode == SUB || third->opcode == MUL){
				return 1;
			}else{
				third = third->next;
				second = second->next;
				first = first->next;
				continue;
			}
			/*
			if(third->opcode != ADD || third->opcode != SUB || third->opcode != MUL){
				third = third->next;
				second = second->next;
				first = first->next;
				continue;
			}
			
			return 1;
			*/
		}
		return 0;

	}
	return 0;
}

void optimizer(Instruction *head){
	Instruction *curr;
	Instruction *ptr;
	

	curr = head;

	while(curr != NULL){
		if(curr->opcode == LOADI){
			ptr = curr->next;
			if(ptr->opcode == LOADI){
				if(ptr->next->opcode == ADD){
					curr->opcode = LOADI;
					curr->field1 = ptr->next->field1;
					curr->field2 = curr->field2 + ptr->field2;
					curr->next = ptr->next->next;
					curr->next->prev = curr->prev;
					curr = curr->next;
				

					/*
					ptr->opcode = LOADI;
					ptr->field1 = ptr->next->field1;
					ptr->field2 = curr->field2 + ptr->field2;
					ptr->prev = curr->prev;
					curr->prev->next = ptr;
					ptr->next = ptr->next->next;
				
					ptr->next->opcode = LOADI;
					ptr->next->field2 = curr->field2 + ptr->field2;
					ptr->next->field3 = NULL;
					ptr->next->prev = curr->prev;
					
					curr = ptr->next;
					*/
				}else if(ptr->next->opcode == SUB){
					curr->opcode = LOADI;
					curr->field1 = ptr->next->field1;
					curr->field2 = curr->field2 - ptr->field2;
					curr->next = ptr->next->next;
					curr->next->prev = curr->prev;
					curr = curr->next;
					/*
					ptr->opcode = LOADI;
					ptr->field1 = ptr->next->field1;
					ptr->field2 = curr->field2 - ptr->field2;
					ptr->prev = curr->prev;
					curr->prev->next = ptr;
					ptr->next = ptr->next->next;
					
					ptr->next->opcode = LOADI;
					ptr->next->field2 = curr->field2 - ptr->field2;
					ptr->next->field3 = NULL;
					ptr->next->prev = curr->prev;
					
					curr = ptr->next;
					*/
				}else if(ptr->next->opcode == MUL){
					curr->opcode = LOADI;
					curr->field1 = ptr->next->field1;
					curr->field2 = curr->field2 * ptr->field2;
					curr->next = ptr->next->next;
					curr->next->prev = curr->prev;
					curr = curr->next;
					/*
					ptr->opcode = LOADI;
					ptr->field1 = ptr->next->field1;
					ptr->field2 = curr->field2 * ptr->field2;
					ptr->prev = curr->prev;
					curr->prev->next = ptr;
					ptr->next = ptr->next->next;
					
					ptr->next->opcode = LOADI;
					ptr->next->field2 = curr->field2 * ptr->field2;
					ptr->next->field3 = NULL;
					ptr->next->prev = curr->prev;
					
					curr = ptr->next;
					*/
				}else{
					curr = curr->next;
				}
			}else{
				curr = curr->next;
			}
		}else{
			curr = curr->next;
		}

	}
}
