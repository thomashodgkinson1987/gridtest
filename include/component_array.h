#ifndef COMPONENT_ARRAY_H
#define COMPONENT_ARRAY_H

#include "array_macros.h"

typedef struct component Component;

DECLARE_ARRAY_STRUCT(component, Component, Component *)
DECLARE_ARRAY_FUNCTIONS(component, Component, Component *)

#endif // COMPONENT_ARRAY_H
