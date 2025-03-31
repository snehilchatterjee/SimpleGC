#include "mooseobject.h"
#include<string.h>

moose_object_t *new_moose_integer(int value){
    moose_object_t* moose_obj=malloc(sizeof(moose_object_t));
    if(moose_obj==NULL){
        return NULL;
    }
    moose_obj->kind=INTEGER;
    moose_obj->data.v_int=value;
    return moose_obj;
}

moose_object_t *new_moose_float(float value){
    moose_object_t* moose_obj=malloc(sizeof(moose_object_t));
    if(moose_obj==NULL){
        return NULL;
    }
    moose_obj->kind=FLOAT;
    moose_obj->data.v_float=value;
    return moose_obj;
}

moose_object_t *new_moose_string(char* value){
    moose_object_t* moose_obj=malloc(sizeof(moose_object_t));
    if(moose_obj==NULL){
        return NULL;
    }
    size_t len=strlen(value);
    char* str=malloc(len+1);
    if(str==NULL){
        free(moose_obj);
        return NULL;
    }
    strcpy(str,value);
    moose_obj->kind=STRING;
    moose_obj->data.v_string=str;
    return moose_obj;
}