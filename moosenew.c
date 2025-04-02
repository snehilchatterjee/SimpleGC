#include <stdlib.h>
#include <string.h>

#include "moosenew.h"
#include "mooseobject.h"
#include "vm.h"

moose_object_t* _new_moose_object(vm_t* vm){
    moose_object_t* moose_obj=malloc(sizeof(moose_object_t));
    if(moose_obj==NULL){
        return NULL;
    }
    vm_track_object(vm,moose_obj);
    moose_obj->is_marked=false;
    return moose_obj;
}

moose_object_t *new_moose_integer(vm_t* vm,int value){
    moose_object_t* moose_obj=_new_moose_object(vm);
    if(moose_obj==NULL){
        return NULL;
    }
    moose_obj->kind=INTEGER;
    moose_obj->data.v_int=value;
    return moose_obj;
}

moose_object_t *new_moose_float(vm_t* vm,float value){
    moose_object_t* moose_obj=_new_moose_object(vm);
    if(moose_obj==NULL){
        return NULL;
    }
    moose_obj->kind=FLOAT;
    moose_obj->data.v_float=value;
    return moose_obj;
}

moose_object_t *new_moose_string(vm_t* vm,char* value){
    moose_object_t* moose_obj=_new_moose_object(vm);
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

moose_object_t *new_moose_vector3(vm_t* vm,moose_object_t *x, moose_object_t *y, moose_object_t *z){
    if(x==NULL || y==NULL || z==NULL) return NULL;
    moose_object_t* moose_obj=_new_moose_object(vm);
    if(moose_obj==NULL){
        return NULL;
    }
    moose_obj->kind=VECTOR3;
    moose_vector_t vec={x,y,z};
    moose_obj->data.v_vector3=vec;
    refcount_inc(x);
    refcount_inc(y);
    refcount_inc(z);
    return moose_obj;
}

moose_object_t *new_moose_array(vm_t* vm,size_t size){
    moose_object_t* moose_obj=_new_moose_object(vm);
    if(moose_obj==NULL){
        return NULL;
    }
    moose_object_t** arr=calloc(size,sizeof(moose_object_t*));
    if(arr==NULL){
        free(moose_obj);
        return NULL;
    }
    moose_obj->kind=ARRAY;
    moose_array_t list={size,arr};
    moose_obj->data.v_array=list;
    return moose_obj;
}