#pragma once
#include<stddef.h>
#include<stdbool.h>

typedef struct moose_object_t moose_object_t;


typedef struct moose_vector_t{
    moose_object_t* x;
    moose_object_t* y;
    moose_object_t* z;
} moose_vector_t;

typedef struct moose_array_t{
    size_t size;
    moose_object_t** elements;
} moose_array_t;


typedef enum moose_object_kind_t{
    INTEGER,
    FLOAT,
    STRING,
    VECTOR3,
    ARRAY
} moose_object_kind_t;

typedef union moose_object_data_t{
    int v_int;
    float v_float;
    char* v_string;
    moose_vector_t v_vector3;
    moose_array_t v_array;
} moose_object_data_t;

typedef struct moose_object_t{
    bool is_marked;
    moose_object_kind_t kind;
    moose_object_data_t data;
} moose_object_t;

bool moose_array_set(moose_object_t *array,size_t index,moose_object_t *value);
moose_object_t *moose_array_get(moose_object_t *array,size_t index);
int moose_length(moose_object_t *obj);
moose_object_t* moose_add(moose_object_t *a,moose_object_t *b);
void moose_object_free(moose_object_t *obj);
void refcount_dec(moose_object_t* moose_obj);
void refcount_inc(moose_object_t* moose_obj);
