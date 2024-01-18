#ifndef MONTY_H
#define MONTY_H

#include <stdio.h>
#include <stdlib.h>

/* Struct for stack node */
typedef struct stack_s
{
    int n;
    struct stack_s *prev;
    struct stack_s *next;
} stack_t;

/* Function prototypes for monty.c */
void push(int value);
void pall(void);

/* Global variable for the stack */
extern stack_t *global_stack;

#endif /* MONTY_H */

