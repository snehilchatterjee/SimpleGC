#include<stddef.h>

typedef struct moose_object_t moose_object_t;


typedef struct moose_vector_t{
    moose_object_t* x;
    moose_object_t* y;
    moose_object_t* z;
} moose_vector_t;

typedef enum moose_object_kind_t{
    INTEGER,
    FLOAT,
    STRING,
    VECTOR3
} moose_object_kind_t;

typedef union moose_object_data_t{
    int v_int;
    float v_float;
    char* v_string;
    moose_vector_t v_vector3;
} moose_object_data_t;

typedef struct moose_object_t{
    moose_object_kind_t kind;
    moose_object_data_t data;
} moose_object_t;

moose_object_t *new_moose_integer(int value);
moose_object_t *new_moose_float(float value);
moose_object_t *new_moose_string(char* value);
moose_object_t *new_moose_vector3(moose_object_t *x, moose_object_t *y, moose_object_t *z);
