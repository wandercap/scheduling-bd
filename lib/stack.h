#ifndef _STACK_H
#define _STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack_node {
    void *content;
    struct stack_node *next;
} stack_node_t, *stack_node_p;

typedef struct stack {
    unsigned int length;
    stack_node_p first;
} stack_t, *stack_p;

stack_p create_stack(void);

int destroy_stack(stack_p stack);

stack_node_p create_stack_node(void *content);

void push(stack_p stack, stack_node_p node);

stack_node_p pop(stack_p stack);

#endif