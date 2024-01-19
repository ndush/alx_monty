#include "monty.h"
unsigned int line_number = 0;

/**
 * is_numeric - Check if a string is a numeric value.
 * @str: String to check
 *
 * Return: 1 if numeric, 0 otherwise
 */
void b(void);
int is_numeric(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (!isdigit((unsigned char)str[i]) && str[i] != '-')
			return (0);
	}

	return (1);
}

/**
 * push - Push a value onto the stack.
 * @stack: Pointer to the stack
 * @value: Value to push
 */
void push(stack_t **stack, int value)
{
	stack_t *new_node;

	if (!stack)
	{
		fprintf(stderr, "Error: Invalid stack\n");
		exit(EXIT_FAILURE);
	}

	new_node = (stack_t *)malloc(sizeof(stack_t));
	if (!new_node)
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
 */
void pint(stack_t **stack)
{
	stack_t *temp;

	if (!stack || !*stack)
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}

	temp = *stack;
	printf("%d\n", temp->n);
}

/**
 * pop - Remove the top element of the stack.
 * @stack: Pointer to the stack
 */
void pop(stack_t **stack)
{
	stack_t *temp;

	if (!stack || !*stack)
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
 * swap - Swap the top two elements of the stack.
 * @stack: Pointer to the stack
 */
void swap(stack_t **stack)
{
	stack_t *temp;

	if (!stack || !*stack || !(*stack)->next)
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	temp = (*stack)->next;
	(*stack)->next = temp->next;
	if (temp->next != NULL)
		temp->next->prev = *stack;

	temp->prev = NULL;
	temp->next = *stack;
	(*stack)->prev = temp;
	*stack = temp;
}

/**
 * add - Add the top two elements of the stack.
 * @stack: Pointer to the stack
 */
void add(stack_t **stack)
{
	if (!stack || !*stack || !(*stack)->next)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	(*stack)->next->n += (*stack)->n;
	pop(stack);
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
		push(stack, value);
	}
	else if (strcmp(opcode, "pall") == 0)
	{
		pall(stack);
	}
	else if (strcmp(opcode, "pint") == 0)
	{
		pint(stack);
	}
	else if (strcmp(opcode, "pop") == 0)
	{
		pop(stack);
	}
	else if (strcmp(opcode, "swap") == 0)
	{
		swap(stack);
	}
	else if (strcmp(opcode, "add") == 0)
	{
		add(stack);
	}
	else if (strcmp(opcode, "nop") == 0)
	{
		nop(stack);
	}
	else
	{
		fprintf(stderr, "L%d: unknown instruction %s\n",
		line_number, opcode);
		exit(EXIT_FAILURE);
	}
}

/**
 * process_monty_file - Process a Monty bytecode file.
 * @filename: Name of the Monty bytecode file
 */
void process_monty_file(const char *filename)
{
	stack_t *stack = NULL;
	unsigned int line_number = 0;

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

		line_number++;

		if (opcode)
			execute_opcode(opcode, arg, &stack, line_number);
	}

	free(line);
	fclose(file);
}

