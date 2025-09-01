#ifndef COMPONENT_ARRAY_H
#define COMPONENT_ARRAY_H

#include "array_macros.h"

// --- Forward Declarations ---
typedef struct component Component;

// --- Type Definitions ---
DECLARE_ARRAY_STRUCT(component, Component, Component *)

// --- Public Function Prototypes ---
DECLARE_ARRAY_FUNCTIONS(component, Component, Component *)

#endif // COMPONENT_ARRAY_H
