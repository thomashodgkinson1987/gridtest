#ifndef ACTOR_ARRAY_H
#define ACTOR_ARRAY_H

#include <array_macros.h>

// --- Forward Declarations ---
typedef struct actor Actor;

// --- Type Definitions ---
DECLARE_ARRAY_STRUCT(actor, Actor, Actor *)

// --- Public Function Prototypes ---
DECLARE_ARRAY_FUNCTIONS(actor, Actor, Actor *)

#endif // ACTOR_ARRAY_H
