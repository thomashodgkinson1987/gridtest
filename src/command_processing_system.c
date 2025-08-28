#include "command_processing_system.h"

#include "actor.h"
#include "log.h"
#include "renderer.h"
#include "world.h"

void command_processing_system_process_command_result(
    Renderer *renderer,
    World *world,
    CommandResult result)
{
    bool is_set_renderer_dirty = false;

    switch (result.type)
    {

    case COMMAND_RESULT_TYPE_ACTOR_SET_X:
    {
        CommandResultParamsActorSetX *params =
            &result.params.actor_set_x;
        const int old_x = params->old_x;
        const int new_x = params->new_x;
        if (old_x != new_x)
        {
            is_set_renderer_dirty = true;
        }
        break;
    }

    case COMMAND_RESULT_TYPE_ACTOR_SET_Y:
    {
        CommandResultParamsActorSetY *params =
            &result.params.actor_set_y;
        const int old_y = params->old_y;
        const int new_y = params->new_y;
        if (old_y != new_y)
        {
            is_set_renderer_dirty = true;
        }
        break;
    }

    case COMMAND_RESULT_TYPE_ACTOR_SET_POSITION:
    {
        CommandResultParamsActorSetPosition *params =
            &result.params.actor_set_position;
        const int old_x = params->old_x;
        const int old_y = params->old_y;
        const int new_x = params->new_x;
        const int new_y = params->new_y;
        if (old_x != new_x || old_y != new_y)
        {
            is_set_renderer_dirty = true;
        }
        break;
    }

    case COMMAND_RESULT_TYPE_ACTOR_SET_GLYPH:
    {
        CommandResultParamsActorSetGlyph *params =
            &result.params.actor_set_glyph;
        const char old_glyph = params->old_glyph;
        const char new_glyph = params->new_glyph;
        if (old_glyph != new_glyph)
        {
            is_set_renderer_dirty = true;
        }
        break;
    }

    case COMMAND_RESULT_TYPE_ACTOR_SET_COLOUR:
    {
        CommandResultParamsActorSetColour *params =
            &result.params.actor_set_colour;
        const Colour old_colour = params->old_colour;
        const Colour new_colour = params->new_colour;
        if (old_colour.r != new_colour.r ||
            old_colour.g != new_colour.g ||
            old_colour.b != new_colour.b ||
            old_colour.a != new_colour.a)
        {
            is_set_renderer_dirty = true;
        }
        break;
    }

    case COMMAND_RESULT_TYPE_ACTOR_SET_R:
    {
        CommandResultParamsActorSetR *params =
            &result.params.actor_set_r;
        const unsigned char old_r = params->old_r;
        const unsigned char new_r = params->new_r;
        if (old_r != new_r)
        {
            is_set_renderer_dirty = true;
        }
        break;
    }

    case COMMAND_RESULT_TYPE_ACTOR_SET_G:
    {
        CommandResultParamsActorSetG *params =
            &result.params.actor_set_g;
        const unsigned char old_g = params->old_g;
        const unsigned char new_g = params->new_g;
        if (old_g != new_g)
        {
            is_set_renderer_dirty = true;
        }
        break;
    }

    case COMMAND_RESULT_TYPE_ACTOR_SET_B:
    {
        CommandResultParamsActorSetB *params =
            &result.params.actor_set_b;
        const unsigned char old_b = params->old_b;
        const unsigned char new_b = params->new_b;
        if (old_b != new_b)
        {
            is_set_renderer_dirty = true;
        }
        break;
    }

    case COMMAND_RESULT_TYPE_ACTOR_SET_A:
    {
        CommandResultParamsActorSetA *params =
            &result.params.actor_set_a;
        const unsigned char old_a = params->old_a;
        const unsigned char new_a = params->new_a;
        if (old_a != new_a)
        {
            is_set_renderer_dirty = true;
        }
        break;
    }

    case COMMAND_RESULT_TYPE_ACTOR_TOOK_DAMAGE:
    {
        CommandResultParamsActorTookDamage *params =
            &result.params.actor_took_damage;
        Actor *actor = params->actor;
        const int amount = params->amount;
        const bool did_die = params->did_die;
        log_message(
            LOG_LEVEL_INFO,
            "%s took %i damage",
            actor_get_name(actor),
            amount);
        if (did_die)
        {
            log_message(
                LOG_LEVEL_INFO,
                "%s died",
                actor_get_name(actor));
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
