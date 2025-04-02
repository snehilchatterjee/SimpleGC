#pragma once
#include<stddef.h>

typedef struct Stack{
    size_t count;
    size_t capacity;
    void **data;
} stack_t;

stack_t *stack_new(size_t capacity);
void stack_push(stack_t* stk,void* obj);
void* stack_pop(stack_t* stk);
void stack_free(stack_t* stk);