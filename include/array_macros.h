#ifndef ARRAY_MACROS_H
#define ARRAY_MACROS_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DECLARE_ARRAY_STRUCT(prefix, name, type) \
    typedef struct prefix##_array                \
    {                                            \
        type *data;                              \
        size_t count;                            \
        size_t capacity;                         \
    } name##Array;

#define DECLARE_ARRAY_FUNCTIONS(prefix, name, type)                                   \
    name##Array prefix##_array_create(size_t initial_capacity);                       \
    void prefix##_array_free(name##Array *prefix##_array);                            \
                                                                                      \
    type *prefix##_array_get_data(name##Array *prefix##_array);                       \
    size_t prefix##_array_get_count(const name##Array *prefix##_array);               \
                                                                                      \
    void prefix##_array_push(name##Array *prefix##_array, type item);                 \
    void prefix##_array_insert(name##Array *prefix##_array, size_t index, type item); \
    void prefix##_array_set(name##Array *prefix##_array, size_t index, type item);    \
                                                                                      \
    void prefix##_array_remove(name##Array *prefix##_array, size_t index);            \
                                                                                      \
    type *prefix##_array_get(name##Array *prefix##_array, size_t index);

#define DEFINE_ARRAY_FUNCTIONS(prefix, name, type)                                            \
    static inline void prefix##_array_grow_impl(name##Array *prefix##_array);                 \
                                                                                              \
    name##Array prefix##_array_create(size_t initial_capacity)                                \
    {                                                                                         \
        if (initial_capacity == 0)                                                            \
        {                                                                                     \
            fprintf(                                                                          \
                stderr,                                                                       \
                #prefix "_array_create: initial capacity cannot be 0\n");                     \
            exit(EXIT_FAILURE);                                                               \
        }                                                                                     \
                                                                                              \
        name##Array prefix##_array = {0};                                                     \
                                                                                              \
        if (initial_capacity > SIZE_MAX / sizeof(*prefix##_array.data))                       \
        {                                                                                     \
            fprintf(                                                                          \
                stderr,                                                                       \
                "" #prefix "_array_create: initial capacity cannot be "                       \
                "greater than %zu\n",                                                         \
                SIZE_MAX / sizeof(*prefix##_array.data));                                     \
            exit(EXIT_FAILURE);                                                               \
        }                                                                                     \
                                                                                              \
        prefix##_array.capacity = initial_capacity;                                           \
        prefix##_array.data = malloc(prefix##_array.capacity * sizeof(*prefix##_array.data)); \
                                                                                              \
        if (!prefix##_array.data)                                                             \
        {                                                                                     \
            perror(#prefix "_array_create: malloc failed");                                   \
            exit(EXIT_FAILURE);                                                               \
        }                                                                                     \
                                                                                              \
        return prefix##_array;                                                                \
    }                                                                                         \
                                                                                              \
    void prefix##_array_free(name##Array *prefix##_array)                                     \
    {                                                                                         \
        free(prefix##_array->data);                                                           \
        prefix##_array->data = NULL;                                                          \
        prefix##_array->count = 0;                                                            \
        prefix##_array->capacity = 0;                                                         \
    }                                                                                         \
                                                                                              \
    type *prefix##_array_get_data(name##Array *prefix##_array)                                \
    {                                                                                         \
        return prefix##_array->data;                                                          \
    }                                                                                         \
                                                                                              \
    size_t prefix##_array_get_count(const name##Array *prefix##_array)                        \
    {                                                                                         \
        return prefix##_array->count;                                                         \
    }                                                                                         \
                                                                                              \
    void prefix##_array_push(name##Array *prefix##_array, type item)                          \
    {                                                                                         \
        prefix##_array_grow_impl(prefix##_array);                                             \
                                                                                              \
        prefix##_array->data[prefix##_array->count++] = item;                                 \
    }                                                                                         \
                                                                                              \
    void prefix##_array_insert(name##Array *prefix##_array, size_t index, type item)          \
    {                                                                                         \
        if (index > prefix##_array->count)                                                    \
        {                                                                                     \
            fprintf(                                                                          \
                stderr,                                                                       \
                #prefix "_array_insert: index (%zu) out of bounds (%zu)\n",                   \
                index,                                                                        \
                prefix##_array->count);                                                       \
            exit(EXIT_FAILURE);                                                               \
        }                                                                                     \
                                                                                              \
        prefix##_array_grow_impl(prefix##_array);                                             \
                                                                                              \
        if (index == prefix##_array->count)                                                   \
        {                                                                                     \
            prefix##_array->data[prefix##_array->count++] = item;                             \
            return;                                                                           \
        }                                                                                     \
                                                                                              \
        memmove(&prefix##_array->data[index + 1],                                             \
                &prefix##_array->data[index],                                                 \
                (prefix##_array->count - index) * sizeof(*prefix##_array->data));             \
                                                                                              \
        prefix##_array->data[index] = item;                                                   \
        prefix##_array->count++;                                                              \
    }                                                                                         \
                                                                                              \
    void prefix##_array_set(name##Array *prefix##_array, size_t index, type item)             \
    {                                                                                         \
        if (prefix##_array->count == 0)                                                       \
        {                                                                                     \
            fprintf(stderr, #prefix "_array_set: array is empty (count 0)\n");                \
            exit(EXIT_FAILURE);                                                               \
        }                                                                                     \
                                                                                              \
        if (index >= prefix##_array->count)                                                   \
        {                                                                                     \
            fprintf(                                                                          \
                stderr,                                                                       \
                #prefix "_array_set: index (%zu) out of bounds (%zu)\n",                      \
                index,                                                                        \
                prefix##_array->count);                                                       \
            exit(EXIT_FAILURE);                                                               \
        }                                                                                     \
                                                                                              \
        prefix##_array->data[index] = item;                                                   \
    }                                                                                         \
                                                                                              \
    void prefix##_array_remove(name##Array *prefix##_array, size_t index)                     \
    {                                                                                         \
        if (prefix##_array->count == 0)                                                       \
        {                                                                                     \
            fprintf(                                                                          \
                stderr,                                                                       \
                #prefix "_array_remove: array is empty (count 0)\n");                         \
            exit(EXIT_FAILURE);                                                               \
        }                                                                                     \
                                                                                              \
        if (index >= prefix##_array->count)                                                   \
        {                                                                                     \
            fprintf(                                                                          \
                stderr,                                                                       \
                #prefix "_array_remove: index (%zu) out of bounds (%zu)\n",                   \
                index,                                                                        \
                prefix##_array->count);                                                       \
            exit(EXIT_FAILURE);                                                               \
        }                                                                                     \
                                                                                              \
        if (index == prefix##_array->count - 1)                                               \
        {                                                                                     \
            prefix##_array->count--;                                                          \
            return;                                                                           \
        }                                                                                     \
                                                                                              \
        memmove(&prefix##_array->data[index],                                                 \
                &prefix##_array->data[index + 1],                                             \
                (prefix##_array->count - index + 1) * sizeof(*prefix##_array->data));         \
                                                                                              \
        prefix##_array->count--;                                                              \
    }                                                                                         \
                                                                                              \
    type *prefix##_array_get(name##Array *prefix##_array, size_t index)                       \
    {                                                                                         \
        if (prefix##_array->count == 0)                                                       \
        {                                                                                     \
            fprintf(stderr, #prefix "_array_get: array is empty (count 0)\n");                \
            exit(EXIT_FAILURE);                                                               \
        }                                                                                     \
                                                                                              \
        if (index >= prefix##_array->count)                                                   \
        {                                                                                     \
            fprintf(                                                                          \
                stderr,                                                                       \
                #prefix "_array_get: index (%zu) out of bounds (%zu)\n",                      \
                index,                                                                        \
                prefix##_array->count);                                                       \
            exit(EXIT_FAILURE);                                                               \
        }                                                                                     \
                                                                                              \
        return &prefix##_array->data[index];                                                  \
    }                                                                                         \
                                                                                              \
    static inline void prefix##_array_grow_impl(name##Array *prefix##_array)                  \
    {                                                                                         \
        if (prefix##_array->count == prefix##_array->capacity)                                \
        {                                                                                     \
            if (prefix##_array->capacity > SIZE_MAX / 2)                                      \
            {                                                                                 \
                fprintf(                                                                      \
                    stderr,                                                                   \
                    "" #prefix "_array_grow_impl: capacity (%zu) cannot be "                  \
                    "doubled without overflow. Max allowed is %zu entries.\n",                \
                    prefix##_array->capacity,                                                 \
                    SIZE_MAX / 2);                                                            \
                exit(EXIT_FAILURE);                                                           \
            }                                                                                 \
                                                                                              \
            const size_t new_capacity = prefix##_array->capacity * 2;                         \
                                                                                              \
            if (new_capacity > SIZE_MAX / sizeof(*prefix##_array->data))                      \
            {                                                                                 \
                fprintf(                                                                      \
                    stderr,                                                                   \
                    "" #prefix "_array_grow_impl: increasing capacity would "                 \
                    "overflow malloc, max capacity in bytes is %zu\n",                        \
                    SIZE_MAX / sizeof(*prefix##_array->data));                                \
                exit(EXIT_FAILURE);                                                           \
            }                                                                                 \
                                                                                              \
            type *new_pointer = realloc(                                                      \
                prefix##_array->data,                                                         \
                new_capacity * sizeof(*prefix##_array->data));                                \
                                                                                              \
            if (!new_pointer)                                                                 \
            {                                                                                 \
                perror(#prefix "_array_grow_impl: error with realloc");                       \
                exit(EXIT_FAILURE);                                                           \
            }                                                                                 \
                                                                                              \
            prefix##_array->data = new_pointer;                                               \
            prefix##_array->capacity = new_capacity;                                          \
        }                                                                                     \
    }

#endif // ARRAY_MACROS_H
