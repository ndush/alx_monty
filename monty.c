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
 * pop - Function to remove the top element of the stack.
 * @stack: Pointer to the top of the stack.
 * @line_number: Line number in the file.
 */
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (*stack == NULL)
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}

	temp = *stack;
	*stack = (*stack)->next;

	if (*stack != NULL)
		(*stack)->prev = NULL;

	free(temp);
}

/**
 * pall - Function to print all values in the stack.
 * @stack: Pointer to the top of the stack.
 */
void pall(stack_t *stack)
{
	stack_t *current;

	current = stack;

	while (current != NULL)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}

/**
 * free_stack - Function to free the entire stack.
 * @stack: Pointer to the top of the stack.
 */
void free_stack(stack_t *stack)
{
	stack_t *current, *temp;

	current = stack;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
}

