#include "actor_array.h"

// This file just needs to define the implementations for the array functions.
// The DEFINE_ARRAY_FUNCTIONS macro from array_macros.h does all the work.

// Note: We are defining an array of Actor pointers (Actor*), not Actor structs.
DEFINE_ARRAY_FUNCTIONS(actor, Actor, Actor*)
