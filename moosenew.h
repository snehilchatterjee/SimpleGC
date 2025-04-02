#pragma once
#include "mooseobject.h"
#include "vm.h"

moose_object_t *_new_moose_object(vm_t* vm);
moose_object_t *new_moose_integer(vm_t* vm,int value);
moose_object_t *new_moose_float(vm_t* vm,float value);
moose_object_t *new_moose_string(vm_t* vm,char* value);
moose_object_t *new_moose_vector3(vm_t* vm,moose_object_t *x, moose_object_t *y, moose_object_t *z);
moose_object_t *new_moose_array(vm_t* vm,size_t size);
