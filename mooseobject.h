#include<stddef.h>

typedef enum moose_object_kind_t{
    INTEGER
} moose_object_kind_t;

typedef union moose_object_data_t{
    int v_int;
} moose_object_data_t;

typedef struct moose_object_t{
    moose_object_kind_t kind;
    moose_object_data_t data;
} moose_object_t;