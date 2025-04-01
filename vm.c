#include "vm.h"

void vm_frame_push(vm_t *vm,frame_t *frame){
    if(vm==NULL || frame==NULL){
        return;
    }
    stack_push(vm->frames,frame);
}

frame_t *vm_new_frame(vm_t *vm){
    frame_t *frame=malloc(sizeof(frame_t));
    frame->references=stack_new(8);
    stack_push(vm->frames,frame);
    return frame;
}

void frame_free(frame_t *frame){
    stack_free(frame->references);
    free(frame);
}

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