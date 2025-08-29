#include "command_system.h"

#include <stdlib.h>

#include "actor.h"
#include "command.h"
#include "command_array.h"
#include "command_result.h"
#include "log.h"
#include "renderer.h"
#include "world.h"

// --- Private Struct Definition ---

struct command_system
{
    CommandArray command_queue;
};

// --- Static Function Prototypes ---

static void
process_result(Renderer *renderer, World *world, CommandResult result);

// --- Public Function Implementations ---

CommandSystem *command_system_create(void)
{
    CommandSystem *command_system = malloc(sizeof(*command_system));
    if (!command_system)
    {
        log_perror("CommandSystem allocation failure");
        return NULL;
    }

    command_system->command_queue = command_array_create(1);
    return command_system;
}

void command_system_free(CommandSystem *command_system)
{
    for (
        size_t i = 0;
        i < command_array_get_count(&command_system->command_queue);
        ++i)
    {
        Command command = command_array_get(&command_system->command_queue, i);
        command_free(&command);
    }
    command_array_free(&command_system->command_queue);
    free(command_system);
}

void command_system_add_command(
    CommandSystem *command_system,
    const Command *command)
{
    command_array_push(&command_system->command_queue, *command);
}

void command_system_process_queue(
    CommandSystem *command_system,
    Renderer *renderer,
    World *world)
{
    for (
        size_t i = 0;
        i < command_array_get_count(&command_system->command_queue);
        ++i)
    {
        Command command = command_array_get(&command_system->command_queue, i);
        CommandResult result = command_execute(&command);
        process_result(renderer, world, result);
        command_result_free(&result);
        command_free(&command);
    }
    command_array_clear(&command_system->command_queue);
}

// --- Static Function Implementations ---

static void process_result(
    Renderer *renderer,
    World *world,
    CommandResult result)
{
    bool is_set_renderer_dirty = false;

    switch (result.type)
    {
    case COMMAND_RESULT_TYPE_ACTOR_SET_X:
    {
        if (result.params.actor_set_x.old_x != result.params.actor_set_x.new_x)
        {
            is_set_renderer_dirty = true;
        }
        break;
    }
    case COMMAND_RESULT_TYPE_ACTOR_SET_Y:
    {
        if (result.params.actor_set_y.old_y != result.params.actor_set_y.new_y)
        {
            is_set_renderer_dirty = true;
        }
        break;
    }
    case COMMAND_RESULT_TYPE_ACTOR_SET_POSITION:
    {
        const int old_x = result.params.actor_set_position.old_x;
        const int old_y = result.params.actor_set_position.old_y;
        const int new_x = result.params.actor_set_position.new_x;
        const int new_y = result.params.actor_set_position.new_y;
        if (old_x != new_x || old_y != new_y)
        {
            is_set_renderer_dirty = true;
        }
        break;
    }
    case COMMAND_RESULT_TYPE_ACTOR_SET_GLYPH:
    {
        const char old_glyph = result.params.actor_set_glyph.old_glyph;
        const char new_glyph = result.params.actor_set_glyph.new_glyph;
        if (old_glyph != new_glyph)
        {
            is_set_renderer_dirty = true;
        }
        break;
    }
    case COMMAND_RESULT_TYPE_ACTOR_SET_COLOUR:
    {
        const Colour old_colour = result.params.actor_set_colour.old_colour;
        const Colour new_colour = result.params.actor_set_colour.new_colour;
        if (old_colour.r != new_colour.r || old_colour.g != new_colour.g ||
            old_colour.b != new_colour.b || old_colour.a != new_colour.a)
        {
            is_set_renderer_dirty = true;
        }
        break;
    }
    case COMMAND_RESULT_TYPE_ACTOR_SET_R:
    {
        if (result.params.actor_set_r.old_r != result.params.actor_set_r.new_r)
        {
            is_set_renderer_dirty = true;
        }
        break;
    }
    case COMMAND_RESULT_TYPE_ACTOR_SET_G:
    {
        if (result.params.actor_set_g.old_g != result.params.actor_set_g.new_g)
        {
            is_set_renderer_dirty = true;
        }
        break;
    }
    case COMMAND_RESULT_TYPE_ACTOR_SET_B:
    {
        if (result.params.actor_set_b.old_b != result.params.actor_set_b.new_b)
        {
            is_set_renderer_dirty = true;
        }
        break;
    }
    case COMMAND_RESULT_TYPE_ACTOR_SET_A:
    {
        if (result.params.actor_set_a.old_a != result.params.actor_set_a.new_a)
        {
            is_set_renderer_dirty = true;
        }
        break;
    }
    case COMMAND_RESULT_TYPE_ACTOR_TOOK_DAMAGE:
    {
        Actor *actor = result.params.actor_took_damage.actor;
        const int amount = result.params.actor_took_damage.amount;
        const bool did_die = result.params.actor_took_damage.did_die;
        log_message(
            LOG_LEVEL_INFO,
            "%s took %i damage",
            actor_get_name(actor),
            amount);
        if (did_die)
        {
            log_message(LOG_LEVEL_INFO, "%s died", actor_get_name(actor));
            world_remove_actor(world, actor);
            is_set_renderer_dirty = true;
        }
        break;
    }
    default:
    {
        break;
    }
    }

    if (is_set_renderer_dirty)
    {
        renderer_set_dirty(renderer);
    }
}
