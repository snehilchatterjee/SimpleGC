#include "vm.h"
#include "mooseobject.h"

void vm_track_object(vm_t *vm,moose_object_t *obj){
    if(vm==NULL || obj==NULL){
        return;
    }
    stack_push(vm->objects,obj);
}

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
    size_t size=vm->frames->count;
    for(size_t i=0;i<size;i++){
        frame_free(vm->frames->data[i]);
    }
    for(size_t i=0;i<size;i++){
        moose_object_free(vm->objects->data[i]);
    }
    stack_free(vm->frames);
    free(vm);
}

void frame_reference_object(frame_t *frame, moose_object_t *obj) {
    if(frame==NULL || obj==NULL){
        return;
    }
    stack_push(frame->references,obj);
}
  

void mark(vm_t* vm){
    size_t totalFrames=vm->frames->count;
    for(size_t i=0;i<totalFrames;i++){
        frame_t *frame=vm->frames->data[i];
        size_t totalReferences=frame->references->count;
        for(size_t j=0;j<totalReferences;j++){
            moose_object_t* obj=frame->references->data[j];
            obj->is_marked=true;
        }
    }
}