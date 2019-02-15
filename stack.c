#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

int empty(Stack S)
{
    return (S==NULL);
}

void init(Stack *S)
{
    *S=NULL;
}

void push(Stack *S, int d)
{
    Stack s = malloc(sizeof(node));
    s->prev = *S;
    s->num = d;
    *S = s;
}

int pop(Stack *S)
{
    int d;
    Stack old;

    if (*S != NULL) {
        d = (*S)->num;
        old = *S;
        d = (*S)->num;
        free(old);
        *S = (*S)->prev;
        return d;
    } else {
        printf("Error pop: stack empty\n");
        exit(1);
    }
}
