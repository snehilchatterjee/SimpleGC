#include<stddef.h>

typedef enum moose_object_kind_t{
    INTEGER,
    FLOAT
} moose_object_kind_t;

typedef union moose_object_data_t{
    int v_int;
    float v_float;
} moose_object_data_t;

typedef struct moose_object_t{
    moose_object_kind_t kind;
    moose_object_data_t data;
} moose_object_t;

moose_object_t *new_moose_integer(int value);
moose_object_t *new_moose_float(float value);
