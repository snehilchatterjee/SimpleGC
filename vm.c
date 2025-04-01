#include "vm.h"

vm_t *vm_new(){
    vm_t *vm=malloc(sizeof(vm_t));
    vm->frames=stack_new(8);
    return vm;
}

void vm_free(vm_t *vm){
    if(vm==NULL) return;
    stack_free(vm->frames);
    free(vm);
}