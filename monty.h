#ifndef MONTY_H
#define MONTY_H

#include <stdio.h>
#include <stdlib.h>

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer value stored in the node
 * @prev: pointer to the previous element in the stack (or queue)
 * @next: pointer to the next element in the stack (or queue)
 *
 * Description: This structure represents each element in a doubly linked
 * list used as a stack (or queue) in the Monty language interpreter.
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: This structure associates an opcode with its corresponding
 * function to execute in the Monty language interpreter.
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

extern stack_t *global_stack;

void push(stack_t **stack, int value);
void pall(stack_t *stack);

#endif

