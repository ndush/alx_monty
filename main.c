#include "monty.h"

/**
 * main - Entry point for the Monty interpreter.
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line arguments.
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
void b(void);
int main(int argc, char *argv[])
{
	stack_t *global_stack = NULL;
	FILE *file;
	int line_number = 0;
	char opcode[256];
	int value;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: %s file\n", argv[0]);
		return (EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		return (EXIT_FAILURE);
	}

	while (fscanf(file, "%s", opcode) != EOF)
	{
		line_number++;

		switch (opcode[0])
		{
			case 'p':
				switch (opcode[1])
				{
					case 'u':
						if (fscanf(file, "%d", &value) == EOF)
						{
							fprintf(stderr, "L%d: usage: push integer\n", line_number);
							fclose(file);
							return (EXIT_FAILURE);
						}

						push(&global_stack, value);
						break;

					case 'a':
						if (global_stack != NULL)
							pall(global_stack);
						break;

					default:
						fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
						fclose(file);
						return (EXIT_FAILURE);
				}
				break;

			default:
				fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
				fclose(file);
				return (EXIT_FAILURE);
		}
	}

	fclose(file);
	return (EXIT_SUCCESS);
}

