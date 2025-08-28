#ifndef COMMAND_PROCESSING_SYSTEM_H
#define COMMAND_PROCESSING_SYSTEM_H

#include "command_result.h"

// Forward declarations
typedef struct renderer Renderer;
typedef struct world World;

void command_processing_system_process_command_result(
    Renderer *renderer,
    World *world,
    CommandResult result);

#endif // COMMAND_PROCESSING_SYSTEM_H
