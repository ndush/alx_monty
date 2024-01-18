#include "monty.h"

/**
 * push - Function to push a value onto the stack.
 * @stack: Pointer to the top of the stack.
 * @value: Integer value to be pushed onto the stack.
 */
void push(stack_t **stack, int value)
{
	stack_t *new_node = malloc(sizeof(stack_t));

	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	new_node->n = value;
	new_node->prev = NULL;
	new_node->next = *stack;

	if (*stack != NULL)
		(*stack)->prev = new_node;

	*stack = new_node;
}

/**
 * pall - Function to print all values in the stack.
 * @stack: Pointer to the top of the stack.
 */
void pall(stack_t *stack)
{
	stack_t *current; /* Move the declaration to the beginning */

	current = stack;

	while (current != NULL)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}

