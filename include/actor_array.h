#ifndef ACTOR_ARRAY_H
#define ACTOR_ARRAY_H

#include "array_macros.h"

// Forward-declare Actor to define the array type.
typedef struct actor Actor;

// Use your macros to declare the struct and functions for an array of Actor pointers.
DECLARE_ARRAY_STRUCT(actor, Actor, Actor *)
DECLARE_ARRAY_FUNCTIONS(actor, Actor, Actor *)

#endif // ACTOR_ARRAY_H
