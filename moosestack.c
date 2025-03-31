#include<stddef.h>
#include "moosestack.h"

stack_t *stack_new(size_t capacity){
    stack_t *stk_ptr=malloc(sizeof(stack_t));
    if(stk_ptr==NULL){
        return NULL;
    }
    stk_ptr->capacity=capacity;
    stk_ptr->count=0;
    stk_ptr->data=malloc(sizeof(void*)*capacity);
    if(stk_ptr->data==NULL){
        free(stk_ptr);
        return NULL;
    }
    return stk_ptr;
}

void stack_push(stack_t* stk,void* obj){
    if(stk->count==stk->capacity){
        void* new_stk_data=realloc(stk->data,sizeof(void*)*(stk->capacity*2));
        if(new_stk_data==NULL) return;
        else{
            stk->data=new_stk_data;
            stk->capacity*=2;
        }
    }
    stk->data[stk->count]=obj;
    stk->count++;
}