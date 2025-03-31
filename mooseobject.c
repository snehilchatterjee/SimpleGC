#include<string.h>
#include<stdlib.h>

#include "mooseobject.h"

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

moose_object_t *new_moose_vector3(moose_object_t *x, moose_object_t *y, moose_object_t *z){
    if(x==NULL || y==NULL || z==NULL) return NULL;
    moose_object_t* moose_obj=malloc(sizeof(moose_object_t));
    if(moose_obj==NULL){
        return NULL;
    }
    moose_obj->kind=VECTOR3;
    moose_vector_t vec={x,y,z};
    moose_obj->data.v_vector3=vec;
    return moose_obj;
}

moose_object_t *new_moose_array(size_t size){
    moose_object_t* moose_obj=malloc(sizeof(moose_object_t));
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

bool moose_array_set(moose_object_t *array,size_t index,moose_object_t *value){
    if(array==NULL || value==NULL || array->kind!=ARRAY || array->data.v_array.size<=index) return false;
    array->data.v_array.elements[index]=value;
    return true;
}


moose_object_t *moose_array_get(moose_object_t *array,size_t index){
    if(array==NULL || array->kind!=ARRAY || array->data.v_array.size<=index) return NULL;
    return array->data.v_array.elements[index];
}

int moose_length(moose_object_t *obj){
    if(obj==NULL) return -1;
    else if(obj->kind==INTEGER || obj->kind==FLOAT) return 1;
    else if(obj->kind==STRING) return strlen(obj->data.v_string);
    else if(obj->kind==VECTOR3) return 3;
    else if(obj->kind==ARRAY) return obj->data.v_array.size;
    return -1;
}