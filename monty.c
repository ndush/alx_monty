#include "monty.h"

/**
 * push - Function to push a value onto the stack
 * @value: The integer value to push
 */
void push(int value)
{
	stack_t *new_node = malloc(sizeof(stack_t));

	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	new_node->n = value;
	new_node->prev = NULL;
	new_node->next = global_stack;

	if (global_stack != NULL)
		global_stack->prev = new_node;

	global_stack = new_node;
}

/**
 * pall - Function to print all values in the stack
 */
void pall(void)
{
	stack_t *current = global_stack;

	while (current != NULL)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}

