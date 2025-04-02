#include <stdlib.h>

#include "vm.h"

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


void frame_reference_object(frame_t *frame, moose_object_t *obj) {
    if(frame==NULL || obj==NULL){
        return;
    }
    stack_push(frame->references,obj);
}

void vm_track_object(vm_t *vm,moose_object_t *obj){
    if(vm==NULL || obj==NULL){
        return;
    }
    stack_push(vm->objects,obj);
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

void trace(vm_t* vm){
    stack_t* gray_objects=stack_new(8);
    if(gray_objects==NULL) return;
    size_t countObj=vm->objects->count;
    for(size_t i=0;i<countObj;i++){
        moose_object_t* obj=vm->objects->data[i];
        if(obj->is_marked){
            stack_push(gray_objects,obj);
        }
    }
    while(gray_objects->count){
        moose_object_t* obj=stack_pop(gray_objects);
        trace_backlen_object(gray_objects,obj);
    }
    free(gray_objects);
}

void sweep(vm_t* vm){
    size_t countObj=vm->objects->count;
    for(size_t i=0;i<countObj;i++){
        moose_object_t* obj=vm->objects->data[i];
        if(obj->is_marked){
            obj->is_marked=false;
            continue;
        }
        else{
            moose_object_free(obj);
            vm->objects->data[i]=NULL;
        }
    }
    stack_remove_nulls(vm->objects);
}

void vm_collect_garbage(vm_t *vm){
    mark(vm);
    trace(vm);
    sweep(vm);
}

void trace_mark_object(stack_t *gray_objects, moose_object_t* ref){
    if(ref==NULL) return;
    stack_push(gray_objects,ref);
}

void trace_backlen_object(stack_t *gray_objects, moose_object_t* ref){
    if(ref->kind==INTEGER || ref->kind==STRING || ref->kind==FLOAT) return;
    else if(ref->kind==VECTOR3){
        trace_mark_object(gray_objects,ref->data.v_vector3.x);
        trace_mark_object(gray_objects,ref->data.v_vector3.y);
        trace_mark_object(gray_objects,ref->data.v_vector3.z);
    }
    else if(ref->kind==ARRAY){
        size_t size=ref->data.v_array.size;
        for(size_t i=0;i<size;i++){
            trace_mark_object(gray_objects,ref->data.v_array.elements[i]);
        }
    }
    else return;
}

int main() {
    return 0;
}