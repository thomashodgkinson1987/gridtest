#include "command_queue.h"

#include "queue_macros.h"

#include "command.h"

// --- Internal Module Definitions ---
DEFINE_QUEUE_STRUCT(command, Command, Command)

// --- Public Function Definitions ---
DEFINE_QUEUE_FUNCTIONS(command, Command, Command)
