#include "monty.h"

int main(int argc, char *argv[])
{
    FILE *file;
    int line_number;
    char opcode[256];
    char *endptr;
    int value;

    if (argc != 2)
    {
        fprintf(stderr, "USAGE: %s file\n", argv[0]);
        return EXIT_FAILURE;
    }

    file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    line_number = 0;

    while (fscanf(file, "%s", opcode) != EOF)
    {
        line_number++;

        switch (opcode[0])
        {
        case 'p':
            switch (opcode[1])
            {
            case 'u':
                if (fscanf(file, "%s", opcode) == EOF)
                {
                    fprintf(stderr, "L%d: usage: push integer\n", line_number);
                    fclose(file);
                    return EXIT_FAILURE;
                }

                value = strtol(opcode, &endptr, 10);

                if (*endptr != '\0')
                {
                    fprintf(stderr, "L%d: usage: push integer\n", line_number);
                    fclose(file);
                    return EXIT_FAILURE;
                }

                push(value);
                break;

            case 'a':
                if (global_stack != NULL)
                    pall();
                break;

            default:
                fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
                fclose(file);
                return EXIT_FAILURE;
            }
            break;

        default:
            fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
            fclose(file);
            return EXIT_FAILURE;
        }
    }

    fclose(file);
    return EXIT_SUCCESS;
}

