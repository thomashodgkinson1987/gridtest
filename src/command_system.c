#include "command_system.h"

#include <stdlib.h>

#include "actor.h"
#include "command.h"
#include "command_queue.h"
#include "command_result.h"
#include "log.h"
#include "process_result.h"
#include "world.h"

// --- Internal Module Definitions ---
struct command_system
{
    CommandQueue command_queue;
};

// --- Static Function Prototypes ---
static void handle_command_result(
    ProcessResult *process_result,
    World *world,
    CommandResult command_result);

// --- Public Function Definitions ---
CommandSystem *command_system_create(void)
{
    CommandSystem *command_system = malloc(sizeof(*command_system));
    if (!command_system)
    {
        log_perror("CommandSystem allocation failure");
        return NULL;
    }

    command_system->command_queue = command_queue_create(2);
    return command_system;
}
void command_system_free(CommandSystem *command_system)
{
    while (!command_queue_is_empty(&command_system->command_queue))
    {
        Command command = command_queue_pop(&command_system->command_queue);
        command_free(&command);
    }
    command_queue_free(&command_system->command_queue);
    free(command_system);
}

void command_system_add_command(
    CommandSystem *command_system,
    const Command *command)
{
    command_queue_push(&command_system->command_queue, *command);
}

ProcessResult command_system_process_queue(
    CommandSystem *command_system,
    World *world)
{
    ProcessResult result = {.did_quit = false, .is_redraw = false};

    while (!command_queue_is_empty(&command_system->command_queue))
    {
        Command command = command_queue_pop(&command_system->command_queue);
        CommandResult command_result = command_execute(&command);
        handle_command_result(&result, world, command_result);
        command_result_free(&command_result);
        command_free(&command);
    }

    return result;
}

// --- Static Function Definitions ---
static void handle_command_result(
    ProcessResult *process_result,
    World *world,
    CommandResult command_result)
{
    switch (command_result.type)
    {
    case COMMAND_RESULT_TYPE_ACTOR_SET_X:
    case COMMAND_RESULT_TYPE_ACTOR_SET_Y:
    case COMMAND_RESULT_TYPE_ACTOR_SET_POSITION:
    case COMMAND_RESULT_TYPE_ACTOR_SET_COLOUR:
    case COMMAND_RESULT_TYPE_ACTOR_SET_R:
    case COMMAND_RESULT_TYPE_ACTOR_SET_G:
    case COMMAND_RESULT_TYPE_ACTOR_SET_B:
    case COMMAND_RESULT_TYPE_ACTOR_SET_A:
    case COMMAND_RESULT_TYPE_ACTOR_SET_GLYPH:
    {
        process_result->is_redraw = true;
        break;
    }
    case COMMAND_RESULT_TYPE_GAME_QUIT:
    {
        process_result->did_quit = true;
        process_result->is_redraw = true;
        break;
    }
    case COMMAND_RESULT_TYPE_ACTOR_TOOK_DAMAGE:
    {
        process_result->is_redraw = true;
        Actor *actor = command_result.params.actor_took_damage.actor;
        const int amount = command_result.params.actor_took_damage.amount;
        const bool did_die = command_result.params.actor_took_damage.did_die;
        log_message(
            LOG_LEVEL_INFO,
            "%s took %i damage",
            actor_get_name(actor),
            amount);
        if (did_die)
        {
            log_message(LOG_LEVEL_INFO, "%s died", actor_get_name(actor));
            world_remove_actor(world, actor);
        }
        break;
    }
    default:
    {
        break;
    }
    }
}
