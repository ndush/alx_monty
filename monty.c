#include "monty.h"

/**
 * is_numeric - Check if a string is numeric.
 * @str: String to check
 * Return: 1 if numeric, 0 otherwise
 */
void b(void);
int is_numeric(char *str)
{
	(void)str;  /* Suppress unused parameter warning */
	return (1);    /* Placeholder, modify as needed */
}

/**
 * push - Push a value onto the stack.
 * @stack: Pointer to the stack
 * @value: Value to push
 * @line_number: Line number in the file
 */
void push(stack_t **stack, int value, unsigned int line_number)
{
	stack_t *new_node;

	if (!stack)
	{
		fprintf(stderr, "L%d: Error: Invalid stack\n", line_number);
		exit(EXIT_FAILURE);
	}

	new_node = malloc(sizeof(stack_t));
	if (!new_node)
	{
		fprintf(stderr, "L%d: Error: malloc failed\n", line_number);
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
 * pall - Print all values on the stack.
 * @stack: Pointer to the stack
 */
void pall(stack_t **stack)
{
	stack_t *current;

	if (!stack)
	{
		fprintf(stderr, "Error: Invalid stack\n");
		exit(EXIT_FAILURE);
	}

	current = *stack;
	while (current != NULL)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}

/**
 * pint - Print the value at the top of the stack.
 * @stack: Pointer to the stack
 * @line_number: Line number in the file
 */
void pint(stack_t **stack, unsigned int line_number)
{
	if (!stack || !*stack)
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}

	printf("%d\n", (*stack)->n);
}

/**
 * pop - Pop the top element off the stack.
 * @stack: Pointer to the stack
 * @line_number: Line number in the file
 */
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (!stack || !*stack)
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}

	temp = *stack;
	*stack = (*stack)->next;
	free(temp);
}

/**
 * swap - Swap the top two elements of the stack.
 * @stack: Pointer to the stack
 * @line_number: Line number in the file
 */
void swap(stack_t **stack, unsigned int line_number)
{
	int temp;

	if (!stack || !*stack || !(*stack)->next)
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	temp = (*stack)->n;
	(*stack)->n = (*stack)->next->n;
	(*stack)->next->n = temp;
}

/**
 * add - Add the top two elements of the stack.
 * @stack: Pointer to the stack
 * @line_number: Line number in the file
 */
void add(stack_t **stack, unsigned int line_number)
{
	if (!stack || !*stack || !(*stack)->next)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	(*stack)->next->n += (*stack)->n;
	pop(stack, line_number);
}

/**
 * nop - No operation.
 * @stack: Pointer to the stack
 */
void nop(stack_t **stack)
{
	(void)stack;
}

/**
 * sub - Subtract the top element of the stack from the second top element.
 * @stack: Pointer to the stack
 * @line_number: Line number in the file
 */
void sub(stack_t **stack, unsigned int line_number)
{
	if (!stack || !*stack || !(*stack)->next)
	{
		fprintf(stderr, "L%d: can't sub, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	(*stack)->next->n -= (*stack)->n;
	pop(stack, line_number);
}

/* Implementations for other opcodes go here */

/**
 * execute_opcode - Execute the specified opcode.
 * @opcode: Opcode to execute
 * @arg: Argument associated with the opcode
 * @stack: Pointer to the stack
 * @line_number: Current line number in the file
 */
void execute_opcode(char *opcode, char *arg,
		stack_t **stack, unsigned int line_number)
{
	int value;

	if (!opcode)
		return;

	if (strcmp(opcode, "push") == 0)
	{
		if (!arg || !is_numeric(arg))
		{
			fprintf(stderr, "L%d: usage: push integer\n", line_number);
			exit(EXIT_FAILURE);
		}
		value = atoi(arg);
		push(stack, value, line_number);
	}
	else if (strcmp(opcode, "pall") == 0)
	{
		pall(stack);
	}
	else if (strcmp(opcode, "pint") == 0)
	{
		pint(stack, line_number);
	}
	else if (strcmp(opcode, "pop") == 0)
	{
		pop(stack, line_number);
	}
	else if (strcmp(opcode, "swap") == 0)
	{
		swap(stack, line_number);
	}
	else if (strcmp(opcode, "add") == 0)
	{
		add(stack, line_number);
	}
	else if (strcmp(opcode, "nop") == 0)
	{
		nop(stack);
	}
	else if (strcmp(opcode, "sub") == 0)
	{
		sub(stack, line_number);
	}
	/* Add cases for other opcodes here */
	else
	{
		fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
		exit(EXIT_FAILURE);
	}
}

/**
 * process_monty_file - Process a Monty bytecode file.
 * @filename: Name of the Monty bytecode file
 */
void process_monty_file(const char *filename)
{
	stack_t *local_stack = NULL;
	unsigned int local_line_number = 0;

	FILE *file = fopen(filename, "r");
	char *line = NULL;
	size_t len = 0;
	int read;

	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", filename);
		exit(EXIT_FAILURE);
	}

	while ((read = getline(&line, &len, file)) != -1)
	{
		char *opcode = strtok(line, " \t\n");
		char *arg = strtok(NULL, " \t\n");

		local_line_number++;

		if (opcode)
			execute_opcode(opcode, arg, &local_stack, local_line_number);
	}

	free(line);
	fclose(file);
}

