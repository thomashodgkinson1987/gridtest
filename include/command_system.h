#ifndef COMMAND_SYSTEM_H
#define COMMAND_SYSTEM_H

typedef struct command_system CommandSystem;

typedef struct command Command;
typedef struct renderer Renderer;
typedef struct world World;

CommandSystem *command_system_create(void);
void command_system_free(CommandSystem *command_system);

void command_system_add_command(
    CommandSystem *command_system,
    const Command *command);

void command_system_process_queue(
    CommandSystem *command_system,
    Renderer *renderer,
    World *world);

#endif // COMMAND_SYSTEM_H
