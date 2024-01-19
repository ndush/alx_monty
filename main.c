#include <stdio.h>
#include <stdlib.h>
#include "monty.h"
/**
 * main - Entry point for the Monty interpreter.
 * @argc: Number of command-line arguments
 * @argv: Array of command-line argument strings
 *
 * Return: success
 */

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		return (EXIT_FAILURE);
	}

	process_monty_file(argv[1]);

	return (EXIT_SUCCESS);
}

