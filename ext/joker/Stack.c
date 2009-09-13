#include <malloc.h>
#include "Stack.h"


void
Stack_freef(stack, functor)  // {{{1
    Stack *      stack;
    FreeFunctor  functor;
{
    Stack *      next;

    while (stack) {
        next = stack->next;
        (*functor)(stack->data);
        free(stack);
        stack = next;
    }
}


void
Stack_free(stack)  // {{{1
    Stack *  stack;
{
    Stack *  next;

    while (stack) {
        next = stack->next;
        free(stack->data);
        free(stack);
        stack = next;
    }
}


void
Stack_push(stack, data)  // {{{1
    Stack **  stack;
    void *    data;
{
    Stack *   front;

    front        = malloc(sizeof(Stack));
    front->next  = *stack;
    front->data  = data;
    *stack       = front;
}


void *
Stack_pop(stack)  // {{{1
    Stack **  stack;
{
    Stack *   next;
    void *    data;

    data    = (*stack)->data;
    next    = (*stack)->next;
    free(*stack);
    *stack  = next;
    return data;
}

