#include<string.h>
#include<stdlib.h>

#include "mooseobject.h"
#include "moosenew.h"


void moose_object_free(moose_object_t* moose_obj){
    // If int or float directly free
    if(moose_obj->kind==STRING){
        free(moose_obj->data.v_string);
    }
    else if(moose_obj->kind==ARRAY){
        free(moose_obj->data.v_array.elements);
    } 
    free(moose_obj);
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

moose_object_t* moose_add(vm_t* vm,moose_object_t *a,moose_object_t *b){
    if(a==NULL || b==NULL) return NULL;
    else if(a->kind==INTEGER){
        if(b->kind==INTEGER) return new_moose_integer(vm,a->data.v_int+b->data.v_int);
        else if(b->kind==FLOAT) return new_moose_float(vm,a->data.v_int+b->data.v_float);
        else return NULL;
    }
    else if(a->kind==FLOAT){
        if(b->kind==INTEGER) return new_moose_float(vm,a->data.v_float+b->data.v_int);
        else if(b->kind==FLOAT) return new_moose_float(vm,a->data.v_float+b->data.v_float);
        else return NULL;
    }
    else if(a->kind==STRING){
        if(b->kind!=STRING) return NULL;
        size_t len=strlen(a->data.v_string)+strlen(b->data.v_string)+1;
        char* newStr=calloc(len,sizeof(char));
        strcpy(newStr,a->data.v_string);
        strcat(newStr,b->data.v_string);
        moose_object_t* new_str_obj=new_moose_string(vm,newStr);
        free(newStr);
        return new_str_obj;
    }
    else if(a->kind==VECTOR3){
        if(b->kind!=VECTOR3) return NULL;
        moose_object_t *newX=moose_add(vm,a->data.v_vector3.x,b->data.v_vector3.x);
        moose_object_t *newY=moose_add(vm,a->data.v_vector3.y,b->data.v_vector3.y);
        moose_object_t *newZ=moose_add(vm,a->data.v_vector3.z,b->data.v_vector3.z);
        moose_object_t *newVec=new_moose_vector3(vm,newX,newY,newZ);
        return newVec;
    }
    else if(a->kind==ARRAY){
        if(b->kind!=ARRAY) return NULL;
        size_t a_size=a->data.v_array.size;
        size_t b_size=b->data.v_array.size;
        
        moose_object_t *newArr=new_moose_array(vm,a_size+b_size);
        
        for(size_t i=0;i<a_size;i++){
            moose_array_set(newArr,i,moose_array_get(a,i));
        }
        for (size_t i=0;i<b_size;i++) { 
            moose_array_set(newArr,a_size+i,moose_array_get(b,i));
        }
        return newArr;
    }
    else return NULL;
}
