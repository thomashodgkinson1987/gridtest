#include "command.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "actor.h"
#include "colour.h"
#include "command_result.h"

Command command_actor_set_x_create(Actor *actor, int x)
{
    Command command = {0};
    command.type = COMMAND_TYPE_ACTOR_SET_X;
    command.params.actor_set_x.actor = actor;
    command.params.actor_set_x.old_x = actor_get_x(actor);
    command.params.actor_set_x.new_x = x;

    return command;
}

Command command_actor_set_y_create(Actor *actor, int y)
{
    Command command = {0};
    command.type = COMMAND_TYPE_ACTOR_SET_Y;
    command.params.actor_set_y.actor = actor;
    command.params.actor_set_y.old_y = actor_get_y(actor);
    command.params.actor_set_y.new_y = y;

    return command;
}

Command command_actor_set_position_create(Actor *actor, int x, int y)
{
    Command command = {0};
    command.type = COMMAND_TYPE_ACTOR_SET_POSITION;
    command.params.actor_set_position.actor = actor;
    command.params.actor_set_position.old_x = actor_get_x(actor);
    command.params.actor_set_position.old_y = actor_get_y(actor);
    command.params.actor_set_position.new_x = x;
    command.params.actor_set_position.new_y = y;

    return command;
}

Command command_actor_set_glyph_create(Actor *actor, char glyph)
{
    Command command = {0};
    command.type = COMMAND_TYPE_ACTOR_SET_GLYPH;
    command.params.actor_set_glyph.actor = actor;
    command.params.actor_set_glyph.old_glyph = actor_get_glyph(actor);
    command.params.actor_set_glyph.new_glyph = glyph;

    return command;
}

Command command_actor_set_colour_create(Actor *actor, Colour colour)
{
    Command command = {0};
    command.type = COMMAND_TYPE_ACTOR_SET_COLOUR;
    command.params.actor_set_colour.actor = actor;
    command.params.actor_set_colour.old_colour = actor_get_colour(actor);
    command.params.actor_set_colour.new_colour = colour;

    return command;
}

Command command_actor_set_r_create(Actor *actor, unsigned char r)
{
    Command command = {0};
    command.type = COMMAND_TYPE_ACTOR_SET_R;
    command.params.actor_set_r.actor = actor;
    command.params.actor_set_r.old_r = actor_get_r(actor);
    command.params.actor_set_r.new_r = r;

    return command;
}

Command command_actor_set_g_create(Actor *actor, unsigned char g)
{
    Command command = {0};
    command.type = COMMAND_TYPE_ACTOR_SET_G;
    command.params.actor_set_g.actor = actor;
    command.params.actor_set_g.old_g = actor_get_g(actor);
    command.params.actor_set_g.new_g = g;

    return command;
}

Command command_actor_set_b_create(Actor *actor, unsigned char b)
{
    Command command = {0};
    command.type = COMMAND_TYPE_ACTOR_SET_B;
    command.params.actor_set_b.actor = actor;
    command.params.actor_set_b.old_b = actor_get_b(actor);
    command.params.actor_set_b.new_b = b;

    return command;
}

Command command_actor_set_a_create(Actor *actor, unsigned char a)
{
    Command command = {0};
    command.type = COMMAND_TYPE_ACTOR_SET_A;
    command.params.actor_set_a.actor = actor;
    command.params.actor_set_a.old_a = actor_get_a(actor);
    command.params.actor_set_a.new_a = a;

    return command;
}

Command command_actor_set_current_hp_create(Actor *actor, int current_hp)
{
    Command command = {0};
    command.type = COMMAND_TYPE_ACTOR_SET_CURRENT_HP;
    command.params.actor_set_current_hp.actor = actor;

    const HealthComponent *health_component =
        actor_get_health_component(actor);

    if (!health_component)
    {
        fprintf(stderr, "%s: health component is null\n", __func__);
        // TODO: better error handling
        exit(EXIT_FAILURE);
    }

    command.params.actor_set_current_hp.old_current_hp =
        health_component->current_hp;
    command.params.actor_set_current_hp.new_current_hp = current_hp;

    return command;
}

Command command_actor_set_max_hp_create(Actor *actor, int max_hp)
{
    Command command = {0};
    command.type = COMMAND_TYPE_ACTOR_SET_MAX_HP;
    command.params.actor_set_max_hp.actor = actor;

    const HealthComponent *health_component =
        actor_get_health_component(actor);

    if (!health_component)
    {
        fprintf(stderr, "%s: health component is null\n", __func__);
        // TODO: better error handling
        exit(EXIT_FAILURE);
    }

    command.params.actor_set_max_hp.old_max_hp = health_component->max_hp;
    command.params.actor_set_max_hp.new_max_hp = max_hp;

    return command;
}

Command command_actor_set_hp_create(Actor *actor, int current_hp, int max_hp)
{
    Command command = {0};
    command.type = COMMAND_TYPE_ACTOR_SET_HP;
    command.params.actor_set_hp.actor = actor;

    const HealthComponent *health_component =
        actor_get_health_component(actor);

    if (!health_component)
    {
        fprintf(stderr, "%s: health component is null\n", __func__);
        // TODO: better error handling
        exit(EXIT_FAILURE);
    }

    command.params.actor_set_hp.old_current_hp = health_component->current_hp;
    command.params.actor_set_hp.old_max_hp = health_component->max_hp;
    command.params.actor_set_hp.new_current_hp = current_hp;
    command.params.actor_set_hp.new_max_hp = max_hp;

    return command;
}

Command command_actor_set_attack_power_create(Actor *actor, int attack_power)
{
    Command command = {0};
    command.type = COMMAND_TYPE_ACTOR_SET_ATTACK_POWER;
    command.params.actor_set_attack_power.actor = actor;

    const CombatComponent *combat_component =
        actor_get_combat_component(actor);

    if (!combat_component)
    {
        fprintf(stderr, "%s: combat component is null\n", __func__);
        // TODO: better error handling
        exit(EXIT_FAILURE);
    }

    command.params.actor_set_attack_power.old_attack_power =
        combat_component->attack_power;
    command.params.actor_set_attack_power.new_attack_power = attack_power;

    return command;
}

Command command_actor_set_name_create(Actor *actor, const char *name)
{
    Command command = {0};
    command.type = COMMAND_TYPE_ACTOR_SET_NAME;
    command.params.actor_set_name.actor = actor;

    command.params.actor_set_name.old_name = strdup(actor_get_name(actor));
    if (!command.params.actor_set_name.old_name)
    {
        perror("[FATAL] Old name allocation failure");
        exit(EXIT_FAILURE);
    }

    command.params.actor_set_name.new_name = strdup(name);
    if (!command.params.actor_set_name.new_name)
    {
        perror("[FATAL] New name allocation error");
        exit(EXIT_FAILURE);
    }

    return command;
}

Command command_actor_translate_health_create(Actor *actor, int translation)
{
    Command command = {0};
    command.type = COMMAND_TYPE_ACTOR_TRANSLATE_HEALTH;
    command.params.actor_translate_health.actor = actor;
    command.params.actor_translate_health.translation = translation;

    return command;
}

void command_free(Command *command)
{
    switch (command->type)
    {

    case COMMAND_TYPE_NULL:
    {
        break;
    }

    case COMMAND_TYPE_ACTOR_SET_X:
    {
        break;
    }

    case COMMAND_TYPE_ACTOR_SET_Y:
    {
        break;
    }

    case COMMAND_TYPE_ACTOR_SET_POSITION:
    {
        break;
    }

    case COMMAND_TYPE_ACTOR_SET_GLYPH:
    {
        break;
    }

    case COMMAND_TYPE_ACTOR_SET_COLOUR:
    {
        break;
    }

    case COMMAND_TYPE_ACTOR_SET_R:
    {
        break;
    }

    case COMMAND_TYPE_ACTOR_SET_G:
    {
        break;
    }

    case COMMAND_TYPE_ACTOR_SET_B:
    {
        break;
    }

    case COMMAND_TYPE_ACTOR_SET_A:
    {
        break;
    }

    case COMMAND_TYPE_ACTOR_SET_CURRENT_HP:
    {
        break;
    }

    case COMMAND_TYPE_ACTOR_SET_MAX_HP:
    {
        break;
    }

    case COMMAND_TYPE_ACTOR_SET_HP:
    {
        break;
    }

    case COMMAND_TYPE_ACTOR_SET_ATTACK_POWER:
    {
        break;
    }

    case COMMAND_TYPE_ACTOR_SET_NAME:
    {
        free(command->params.actor_set_name.old_name);
        free(command->params.actor_set_name.new_name);
        break;
    }

    case COMMAND_TYPE_ACTOR_TRANSLATE_HEALTH:
    {
        break;
    }

    default:
    {
        // Good practice to have a default case
        fprintf(stderr, "Warning: Unknown command type %d\n", command->type);
        break;
    }
    }
}

CommandResult command_execute(Command *command)
{
    switch (command->type)
    {

    case COMMAND_TYPE_NULL:
    {
        break;
    }

    case COMMAND_TYPE_ACTOR_SET_X:
    {
        CommandParamsActorSetX *params = &command->params.actor_set_x;
        Actor *actor = params->actor;
        const int old_x = params->old_x;
        const int new_x = params->new_x;
        actor_set_x(actor, new_x);
        printf(
            "%s [actor_set_x]: old_x=%i new_x=%i\n",
            __func__,
            old_x,
            new_x);
        CommandResult result = command_result_actor_set_x_create(
            actor,
            old_x,
            new_x);
        return result;
    }

    case COMMAND_TYPE_ACTOR_SET_Y:
    {
        CommandParamsActorSetY *params = &command->params.actor_set_y;
        Actor *actor = params->actor;
        const int old_y = params->old_y;
        const int new_y = params->new_y;
        actor_set_y(actor, new_y);
        printf(
            "%s [actor_set_y]: old_y=%i new_y=%i\n",
            __func__,
            old_y,
            new_y);
        CommandResult result = command_result_actor_set_y_create(
            actor,
            old_y,
            new_y);
        return result;
    }

    case COMMAND_TYPE_ACTOR_SET_POSITION:
    {
        CommandParamsActorSetPosition *params =
            &command->params.actor_set_position;
        Actor *actor = params->actor;
        const int old_x = params->old_x;
        const int old_y = params->old_y;
        const int new_x = params->new_x;
        const int new_y = params->new_y;
        actor_set_position(actor, new_x, new_y);
        printf(
            "%s [actor_set_position]: old_x=%i old_y=%i new_x=%i new_y=%i\n",
            __func__,
            old_x,
            old_y,
            new_x,
            new_y);
        CommandResult result = command_result_actor_set_position_create(
            actor,
            old_x,
            old_y,
            new_x,
            new_y);
        return result;
    }

    case COMMAND_TYPE_ACTOR_SET_GLYPH:
    {
        CommandParamsActorSetGlyph *params = &command->params.actor_set_glyph;
        Actor *actor = params->actor;
        const char old_glyph = params->old_glyph;
        const char new_glyph = params->new_glyph;
        actor_set_glyph(actor, new_glyph);
        printf(
            "%s [actor_set_glyph]: old_glyph=%c new_glyph=%c\n",
            __func__,
            old_glyph,
            new_glyph);
        CommandResult result = command_result_actor_set_glyph_create(
            actor,
            old_glyph,
            new_glyph);
        return result;
    }

    case COMMAND_TYPE_ACTOR_SET_COLOUR:
    {
        CommandParamsActorSetColour *params =
            &command->params.actor_set_colour;
        Actor *actor = params->actor;
        const Colour old_colour = params->old_colour;
        const Colour new_colour = params->new_colour;
        actor_set_colour(actor, new_colour);
        printf(
            "%s [actor_set_colour]: old_colour={%hhu. %hhu, %hhu, %hhu} "
            "new_colour={%hhu. %hhu, %hhu, %hhu}\n",
            __func__,
            old_colour.r,
            old_colour.g,
            old_colour.b,
            old_colour.a,
            new_colour.r,
            new_colour.g,
            new_colour.b,
            new_colour.a);
        CommandResult result = command_result_actor_set_colour_create(
            actor,
            old_colour,
            new_colour);
        return result;
    }

    case COMMAND_TYPE_ACTOR_SET_R:
    {
        CommandParamsActorSetR *params = &command->params.actor_set_r;
        Actor *actor = params->actor;
        const unsigned char old_r = params->old_r;
        const unsigned char new_r = params->new_r;
        actor_set_r(actor, new_r);
        printf(
            "%s [actor_set_r]: old_r=%hhu new_r=%hhu\n",
            __func__,
            old_r,
            new_r);
        CommandResult result = command_result_actor_set_r_create(
            actor,
            old_r,
            new_r);
        return result;
    }

    case COMMAND_TYPE_ACTOR_SET_G:
    {
        CommandParamsActorSetG *params = &command->params.actor_set_g;
        Actor *actor = params->actor;
        const unsigned char old_g = params->old_g;
        const unsigned char new_g = params->new_g;
        actor_set_g(actor, new_g);
        printf(
            "%s [actor_set_g]: old_g=%hhu new_g=%hhu\n",
            __func__,
            old_g,
            new_g);
        CommandResult result = command_result_actor_set_g_create(
            actor,
            old_g,
            new_g);
        return result;
    }

    case COMMAND_TYPE_ACTOR_SET_B:
    {
        CommandParamsActorSetB *params = &command->params.actor_set_b;
        Actor *actor = params->actor;
        const unsigned char old_b = params->old_b;
        const unsigned char new_b = params->new_b;
        actor_set_b(actor, new_b);
        printf(
            "%s [actor_set_b]: old_b=%hhu new_b=%hhu\n",
            __func__,
            old_b,
            new_b);
        CommandResult result = command_result_actor_set_b_create(
            actor,
            old_b,
            new_b);
        return result;
    }

    case COMMAND_TYPE_ACTOR_SET_A:
    {
        CommandParamsActorSetA *params = &command->params.actor_set_a;
        Actor *actor = params->actor;
        const unsigned char old_a = params->old_a;
        const unsigned char new_a = params->new_a;
        actor_set_a(actor, new_a);
        printf(
            "%s [actor_set_a]: old_a=%hhu new_a=%hhu\n",
            __func__,
            old_a,
            new_a);
        CommandResult result = command_result_actor_set_a_create(
            actor,
            old_a,
            new_a);
        return result;
    }

    case COMMAND_TYPE_ACTOR_SET_CURRENT_HP:
    {
        CommandParamsActorSetCurrentHp *params =
            &command->params.actor_set_current_hp;
        Actor *actor = params->actor;
        const int old_current_hp = params->old_current_hp;
        const int new_current_hp = params->new_current_hp;
        HealthComponent *health_component =
            actor_get_health_component_mut(actor);
        if (!health_component)
        {
            fprintf(
                stderr,
                "%s: COMMAND_TYPE_ACTOR_SET_CURRENT_HP health component is "
                "null\n",
                __func__);
            exit(EXIT_FAILURE);
        }
        health_component->current_hp = new_current_hp;
        if (health_component->current_hp < 0)
            health_component->current_hp = 0;
        else if (health_component->current_hp > health_component->max_hp)
            health_component->current_hp = health_component->max_hp;
        printf(
            "%s [actor_set_current_hp]: old_current_hp=%i new_current_hp=%i\n",
            __func__,
            old_current_hp,
            health_component->current_hp);
        CommandResult result = command_result_actor_set_current_hp_create(
            actor,
            old_current_hp,
            health_component->current_hp);
        break;
    }

    case COMMAND_TYPE_ACTOR_SET_MAX_HP:
    {
        CommandParamsActorSetMaxHp *params = &command->params.actor_set_max_hp;
        Actor *actor = params->actor;
        const int old_max_hp = params->old_max_hp;
        const int new_max_hp = params->new_max_hp;
        HealthComponent *health_component =
            actor_get_health_component_mut(actor);
        if (!health_component)
        {
            fprintf(
                stderr,
                "%s: COMMAND_TYPE_ACTOR_SET_MAX_HP health component is "
                "null\n",
                __func__);
            exit(EXIT_FAILURE);
        }
        health_component->max_hp = new_max_hp;
        if (health_component->max_hp < 0)
            health_component->max_hp = 0;
        if (health_component->current_hp > health_component->max_hp)
            health_component->current_hp = health_component->max_hp;
        // TODO: Add old/new current_hp it could be changed
        printf(
            "%s [actor_set_max_hp]: old_max_hp=%i new_max_hp=%i\n",
            __func__,
            old_max_hp,
            health_component->max_hp);
        CommandResult result = command_result_actor_set_max_hp_create(
            actor,
            old_max_hp,
            health_component->max_hp);
        return result;
    }

    case COMMAND_TYPE_ACTOR_SET_HP:
    {
        CommandParamsActorSetHp *params = &command->params.actor_set_hp;
        Actor *actor = params->actor;
        const int old_current_hp = params->old_current_hp;
        const int old_max_hp = params->old_max_hp;
        const int new_current_hp = params->new_current_hp;
        const int new_max_hp = params->new_max_hp;
        HealthComponent *health_component =
            actor_get_health_component_mut(actor);
        if (!health_component)
        {
            fprintf(
                stderr,
                "%s: COMMAND_TYPE_ACTOR_SET_HP health component is "
                "null\n",
                __func__);
        }
        health_component->current_hp = new_current_hp;
        health_component->max_hp = new_max_hp;
        if (health_component->current_hp < 0)
            health_component->current_hp = 0;
        if (health_component->max_hp < 0)
            health_component->max_hp = 0;
        if (health_component->current_hp > health_component->max_hp)
            health_component->current_hp = health_component->max_hp;
        printf(
            "%s [actor_set_hp]: old_current_hp=%i old_max_hp=%i "
            "new_current_hp=%i new_max_hp=%i\n",
            __func__,
            old_current_hp,
            old_max_hp,
            health_component->current_hp,
            health_component->max_hp);
        CommandResult result = command_result_actor_set_hp_create(
            actor,
            old_current_hp,
            old_max_hp,
            health_component->current_hp,
            health_component->max_hp);
        return result;
    }

    case COMMAND_TYPE_ACTOR_SET_ATTACK_POWER:
    {
        CommandParamsActorSetAttackPower *params =
            &command->params.actor_set_attack_power;
        Actor *actor = params->actor;
        const int old_attack_power = params->old_attack_power;
        const int new_attack_power = params->new_attack_power;
        CombatComponent *combat_component =
            actor_get_combat_component_mut(actor);
        if (!combat_component)
        {
            fprintf(
                stderr,
                "%s: COMMAND_TYPE_ACTOR_SET_ATTACK_POWER combat component is "
                "null\n",
                __func__);
            exit(EXIT_FAILURE);
        }
        combat_component->attack_power = new_attack_power;
        if (combat_component->attack_power < 0)
            combat_component->attack_power = 0;
        printf(
            "%s [actor_set_attack_power]: old_attack_power=%i "
            "new_attack_power=%i\n",
            __func__,
            old_attack_power,
            combat_component->attack_power);
        CommandResult result = command_result_actor_set_attack_power_create(
            actor,
            old_attack_power,
            combat_component->attack_power);
        return result;
    }

    case COMMAND_TYPE_ACTOR_SET_NAME:
    {
        CommandParamsActorSetName *params = &command->params.actor_set_name;
        Actor *actor = params->actor;
        const char *old_name = params->old_name;
        const char *new_name = params->new_name;
        actor_set_name(actor, new_name);
        printf(
            "%s [actor_set_name]: old_name=%s new_name=%s\n",
            __func__,
            old_name,
            new_name);
        CommandResult result = command_result_actor_set_name_create(
            actor,
            old_name,
            new_name);
        return result;
    }

    case COMMAND_TYPE_ACTOR_TRANSLATE_HEALTH:
    {
        CommandParamsActorTranslateHealth *params =
            &command->params.actor_translate_health;
        Actor *actor = params->actor;
        const int translation = params->translation;
        HealthComponent *health_component =
            actor_get_health_component_mut(actor);
        if (!health_component)
        {
            // TODO: better error handling
            fprintf(
                stderr,
                "%s [actor_translate_health]: health component is null\n",
                __func__);
            exit(EXIT_FAILURE);
        }
        const int old_current_hp = health_component->current_hp;
        health_component->current_hp += translation;
        if (health_component->current_hp < 0)
            health_component->current_hp = 0;
        else if (health_component->current_hp > health_component->max_hp)
            health_component->current_hp = health_component->max_hp;
        bool did_die = health_component->current_hp == 0 && old_current_hp > 0;
        CommandResult result = command_result_actor_took_damage_create(
            actor,
            -translation,
            did_die);
        return result;
    }

    default:
    {
        // Good practice to have a default case
        fprintf(stderr, "Warning: Unknown command type %d\n", command->type);
        break;
    }
    }
}
