#include <stdio.h>
#include <stdlib.h>
#include "mooseobject.h"

int main() {
    // Test integer object
    moose_object_t *int_obj = new_moose_integer(42);
    if (int_obj) {
        printf("Integer Object: %d\n", int_obj->data.v_int);
        free(int_obj);
    } else {
        printf("Failed to allocate Integer Object\n");
    }

    // Test float object
    moose_object_t *float_obj = new_moose_float(3.14);
    if (float_obj) {
        printf("Float Object: %f\n", float_obj->data.v_float);
        free(float_obj);
    } else {
        printf("Failed to allocate Float Object\n");
    }

    // Test string object
    moose_object_t *string_obj = new_moose_string("Hello, Moose!");
    if (string_obj) {
        printf("String Object: %s\n", string_obj->data.v_string);
        free(string_obj->data.v_string);
        free(string_obj);
    } else {
        printf("Failed to allocate String Object\n");
    }

    // Test vector3 object
    moose_object_t *vec_x = new_moose_integer(1);
    moose_object_t *vec_y = new_moose_integer(2);
    moose_object_t *vec_z = new_moose_integer(3);
    moose_object_t *vector_obj = new_moose_vector3(vec_x, vec_y, vec_z);
    if (vector_obj) {
        printf("Vector3 Object: (%d, %d, %d)\n", 
               vector_obj->data.v_vector3.x->data.v_int, 
               vector_obj->data.v_vector3.y->data.v_int, 
               vector_obj->data.v_vector3.z->data.v_int);
        free(vec_x);
        free(vec_y);
        free(vec_z);
        free(vector_obj);
    } else {
        printf("Failed to allocate Vector3 Object\n");
    }

    // Test array object
    size_t array_size = 3;
    moose_object_t *array_obj = new_moose_array(array_size);
    if (array_obj) {
        printf("Array Object: Initialized with size %zu\n", array_obj->data.v_array.size);
        free(array_obj->data.v_array.elements);
        free(array_obj);
    } else {
        printf("Failed to allocate Array Object\n");
    }

    return 0;
}