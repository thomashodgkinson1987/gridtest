#ifndef COMMAND_QUEUE_H
#define COMMAND_QUEUE_H

#include "queue_macros.h"

// --- Forward Declarations ---
typedef struct command Command;

// --- Type Definitions ---
DECLARE_QUEUE_STRUCT(command, Command, Command)

// --- Public Function Prototypes ---
DECLARE_QUEUE_FUNCTIONS(command, Command, Command)

#endif // COMMAND_QUEUE_H
