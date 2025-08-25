#ifndef COMMAND_ARRAY_H
#define COMMAND_ARRAY_H

#include "array_macros.h"

typedef struct command Command;

DECLARE_ARRAY_STRUCT(command, Command, Command)
DECLARE_ARRAY_FUNCTIONS(command, Command, Command)

#endif // COMMAND_ARRAY_H
