#ifndef COMMAND_ARRAY_H
#define COMMAND_ARRAY_H

#include "array_macros.h"

// --- Forward Declarations ---
typedef struct command Command;

// --- Type Definitions ---
DECLARE_ARRAY_STRUCT(command, Command, Command)

// --- Public Function Prototypes ---
DECLARE_ARRAY_FUNCTIONS(command, Command, Command)

#endif // COMMAND_ARRAY_H
