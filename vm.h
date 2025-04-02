#pragma once
#include "moosestack.h"
#include "mooseobject.h"

typedef struct VirtualMachine
{
    stack_t *frames;
    stack_t *objects;
} vm_t;

typedef struct StackFrame {
    stack_t *references;
} frame_t;

vm_t *vm_new();
void vm_free(vm_t *vm);

void vm_frame_push(vm_t *vm,frame_t *frame);
frame_t *vm_new_frame(vm_t *vm);

void frame_free(frame_t *frame);
void frame_reference_object(frame_t *frame, moose_object_t *obj);
void vm_track_object(vm_t *vm, moose_object_t *obj);

void mark(vm_t* vm);
void trace(vm_t* vm);
void sweep(vm_t* vm);

void trace_backlen_object(stack_t *gray_objects, moose_object_t* ref);
void trace_mark_object(stack_t *gray_objects, moose_object_t* ref);