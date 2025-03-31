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
       
       // Test array set and get
       moose_array_set(array_obj, 0, new_moose_integer(100));
       moose_array_set(array_obj, 1, new_moose_float(200.5));
       moose_array_set(array_obj, 2, new_moose_string("ArrayTest"));
       
       printf("Array Element 0: %d\n", moose_array_get(array_obj, 0)->data.v_int);
       printf("Array Element 1: %f\n", moose_array_get(array_obj, 1)->data.v_float);
       printf("Array Element 2: %s\n", moose_array_get(array_obj, 2)->data.v_string);
   } else {
       printf("Failed to allocate Array Object\n");
   }

   // Test length function
   printf("Length of Integer Object: %d\n", moose_length(int_obj));
   printf("Length of Float Object: %d\n", moose_length(float_obj));
   printf("Length of String Object: %d\n", moose_length(string_obj));
   printf("Length of Vector3 Object: %d\n", moose_length(vector_obj));
   printf("Length of Array Object: %d\n", moose_length(array_obj));

   for (size_t i = 0; i < array_size; i++) {
    free(array_obj->data.v_array.elements[i]);
    }
    free(array_obj->data.v_array.elements);
    free(array_obj);

    return 0;
}