#ifndef STACK_H_GUARD
#define STACK_H_GUARD


/*
 * Represents a Stack.
 *
 * The empty stack is represented by a
 * NULL-pointer, allowing you to test for
 * emptyness with
 *
 *  if (stack) { ... }
 *
 * Use Stack_push() and Stack_pop() to modify
 * the Stack.
 *
 * Use Stack_free() and Stack_freef() to delete any stack.
 *
 */
typedef struct stack {  // {{{1
    void *          data;
    struct stack *  next;
} Stack;


typedef void (*FreeFunctor)(void *);


/*
 * Deletes a Stack.
 *
 * Calls free() on all data members.
 *
 */
void Stack_free(  // {{{1
    Stack *  stack
);

/*
 * Deletes a Stack, executing the given functor for every
 * data member in the stack.
 *
 * The functor is required to free the data member.
 *
 */
void Stack_freef(  // {{{1
    Stack *      stack,
    FreeFunctor  functor
);

/*
 * Pushes a data member onto the Stack.
 *
 * Changes the Stack's address!
 *
 */
void Stack_push(  // {{{1
    Stack **  stack,
    void *    data
);

/*
 * Pops a data member from the Stack and
 * returns the pointer to it.
 *
 * Changes the Stack's address!
 *
 */
void * Stack_pop(  // {{{1
    Stack **  stack
);


#endif

