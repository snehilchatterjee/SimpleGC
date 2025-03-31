# Moose Object System

A simple C-based object system supporting integers, floats, strings, vectors, and arrays with reference counting for memory management.

## Features
- Dynamic object creation for multiple data types.
- Reference counting to manage memory efficiently.
- Basic arithmetic operations for integers, floats, and vectors.
- String concatenation and array merging.
- Safe memory allocation with proper cleanup.

## Supported Data Types
- **INTEGER**: Stores an integer value.
- **FLOAT**: Stores a floating-point value.
- **STRING**: Stores a dynamically allocated string.
- **VECTOR3**: Represents a 3D vector with three components.
- **ARRAY**: A dynamic array of `moose_object_t` elements.

## Usage
### Creating Objects
```c
moose_object_t *num = new_moose_integer(42);
moose_object_t *flt = new_moose_float(3.14);
moose_object_t *str = new_moose_string("Hello, World!");
moose_object_t *vec = new_moose_vector3(num, flt, num);
moose_object_t *arr = new_moose_array(5);
```

### Working with Arrays
```c
moose_array_set(arr, 0, num);
moose_array_set(arr, 1, flt);
moose_array_set(arr, 2, str);
moose_object_t *elem = moose_array_get(arr, 2);
```

### Arithmetic Operations
```c
moose_object_t *sum = moose_add(num, flt); // Integer + Float
moose_object_t *concat = moose_add(str, new_moose_string(" Moose")); // String concatenation
moose_object_t *merged_arr = moose_add(arr, new_moose_array(3));
```

### Reference Counting
```c
refcount_inc(num); // Increase reference count
refcount_dec(num); // Decrease reference count (frees when refcount reaches 0)
```

## Memory Management
- Every object is dynamically allocated and must be properly freed.
- Reference counting ensures safe deallocation when no references remain.
- Use `refcount_dec()` to release objects when they are no longer needed.

## Compilation
Compile using GCC:
```sh
gcc main.c mooseobject.c -o test_moose.out
./test_moose.out
```

## Future Improvements
- Improve error handling and logging.
- Optimize memory usage for large arrays.
- Extend support for additional data types like dictionaries.

