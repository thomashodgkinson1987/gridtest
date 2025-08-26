#include "command_result.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "actor.h"
#include "colour.h"

CommandResult command_result_actor_set_x_create(
    Actor *actor,
    int old_x,
    int new_x)
{
    CommandResult result = {0};
    result.type = COMMAND_RESULT_TYPE_ACTOR_SET_X;
    result.params.actor_set_x.actor = actor;
    result.params.actor_set_x.old_x = old_x;
    result.params.actor_set_x.new_x = new_x;

    return result;
}

CommandResult command_result_actor_set_y_create(
    Actor *actor,
    int old_y,
    int new_y)
{
    CommandResult result = {0};
    result.type = COMMAND_RESULT_TYPE_ACTOR_SET_Y;
    result.params.actor_set_y.actor = actor;
    result.params.actor_set_y.old_y = old_y;
    result.params.actor_set_y.new_y = new_y;

    return result;
}

CommandResult command_result_actor_set_position_create(
    Actor *actor,
    int old_x,
    int old_y,
    int new_x,
    int new_y)
{
    CommandResult result = {0};
    result.type = COMMAND_RESULT_TYPE_ACTOR_SET_POSITION;
    result.params.actor_set_position.actor = actor;
    result.params.actor_set_position.old_x = old_x;
    result.params.actor_set_position.old_y = old_y;
    result.params.actor_set_position.new_x = new_x;
    result.params.actor_set_position.new_y = new_y;

    return result;
}

CommandResult command_result_actor_set_glyph_create(
    Actor *actor,
    char old_glyph,
    char new_glyph)
{
    CommandResult result = {0};
    result.type = COMMAND_RESULT_TYPE_ACTOR_SET_GLYPH;
    result.params.actor_set_glyph.actor = actor;
    result.params.actor_set_glyph.old_glyph = old_glyph;
    result.params.actor_set_glyph.new_glyph = new_glyph;

    return result;
}

CommandResult command_result_actor_set_colour_create(
    Actor *actor,
    Colour old_colour,
    Colour new_colour)
{
    CommandResult result = {0};
    result.type = COMMAND_RESULT_TYPE_ACTOR_SET_COLOUR;
    result.params.actor_set_colour.actor = actor;
    result.params.actor_set_colour.old_colour = old_colour;
    result.params.actor_set_colour.new_colour = new_colour;

    return result;
}

CommandResult command_result_actor_set_r_create(
    Actor *actor,
    unsigned char old_r,
    unsigned char new_r)
{
    CommandResult result = {0};
    result.type = COMMAND_RESULT_TYPE_ACTOR_SET_R;
    result.params.actor_set_r.actor = actor;
    result.params.actor_set_r.old_r = old_r;
    result.params.actor_set_r.new_r = new_r;

    return result;
}

CommandResult command_result_actor_set_g_create(
    Actor *actor,
    unsigned char old_g,
    unsigned char new_g)
{
    CommandResult result = {0};
    result.type = COMMAND_RESULT_TYPE_ACTOR_SET_G;
    result.params.actor_set_g.actor = actor;
    result.params.actor_set_g.old_g = old_g;
    result.params.actor_set_g.new_g = new_g;

    return result;
}

CommandResult command_result_actor_set_b_create(
    Actor *actor,
    unsigned char old_b,
    unsigned char new_b)
{
    CommandResult result = {0};
    result.type = COMMAND_RESULT_TYPE_ACTOR_SET_B;
    result.params.actor_set_b.actor = actor;
    result.params.actor_set_b.old_b = old_b;
    result.params.actor_set_b.new_b = new_b;

    return result;
}

CommandResult command_result_actor_set_a_create(
    Actor *actor,
    unsigned char old_a,
    unsigned char new_a)
{
    CommandResult result = {0};
    result.type = COMMAND_RESULT_TYPE_ACTOR_SET_A;
    result.params.actor_set_a.actor = actor;
    result.params.actor_set_a.old_a = old_a;
    result.params.actor_set_a.new_a = new_a;

    return result;
}

CommandResult command_result_actor_set_current_hp_create(
    Actor *actor,
    int old_current_hp,
    int new_current_hp)
{
    CommandResult result = {0};
    result.type = COMMAND_RESULT_TYPE_ACTOR_SET_CURRENT_HP;
    result.params.actor_set_current_hp.actor = actor;
    result.params.actor_set_current_hp.old_current_hp = old_current_hp;
    result.params.actor_set_current_hp.new_current_hp = new_current_hp;

    return result;
}

CommandResult command_result_actor_set_max_hp_create(
    Actor *actor,
    int old_max_hp,
    int new_max_hp)
{
    CommandResult result = {0};
    result.type = COMMAND_RESULT_TYPE_ACTOR_SET_MAX_HP;
    result.params.actor_set_max_hp.actor = actor;
    result.params.actor_set_max_hp.old_max_hp = old_max_hp;
    result.params.actor_set_max_hp.new_max_hp = new_max_hp;

    return result;
}

CommandResult command_result_actor_set_hp_create(
    Actor *actor,
    int old_current_hp,
    int old_max_hp,
    int new_current_hp,
    int new_max_hp)
{
    CommandResult result = {0};
    result.type = COMMAND_RESULT_TYPE_ACTOR_SET_HP;
    result.params.actor_set_hp.actor = actor;
    result.params.actor_set_hp.old_current_hp = old_current_hp;
    result.params.actor_set_hp.old_max_hp = old_max_hp;
    result.params.actor_set_hp.new_current_hp = new_current_hp;
    result.params.actor_set_hp.new_max_hp = new_max_hp;

    return result;
}

CommandResult command_result_actor_set_attack_power_create(
    Actor *actor,
    int old_attack_power,
    int new_attack_power)
{
    CommandResult result = {0};
    result.type = COMMAND_RESULT_TYPE_ACTOR_SET_ATTACK_POWER;
    result.params.actor_set_attack_power.actor = actor;
    result.params.actor_set_attack_power.old_attack_power = old_attack_power;
    result.params.actor_set_attack_power.new_attack_power = new_attack_power;

    return result;
}

CommandResult command_result_actor_set_name_create(
    Actor *actor,
    const char *old_name,
    const char *new_name)
{
    CommandResult result = {0};
    result.type = COMMAND_RESULT_TYPE_ACTOR_SET_NAME;
    result.params.actor_set_name.actor = actor;
    result.params.actor_set_name.old_name = strdup(old_name);
    if (!result.params.actor_set_name.old_name)
    {
        perror("[FATAL] Old name allocation failure");
        exit(EXIT_FAILURE);
    }
    result.params.actor_set_name.new_name = strdup(new_name);
    if (!result.params.actor_set_name.new_name)
    {
        perror("[FATAL] New name allocation failure");
        exit(EXIT_FAILURE);
    }

    return result;
}

CommandResult command_result_actor_took_damage_create(
    Actor *actor,
    int amount,
    bool did_die)
{
    CommandResult result = {0};
    result.type = COMMAND_RESULT_TYPE_ACTOR_TOOK_DAMAGE;
    result.params.actor_took_damage.actor = actor;
    result.params.actor_took_damage.amount = amount;
    result.params.actor_took_damage.did_die = did_die;

    return result;
}

void command_result_free(CommandResult *result)
{
    switch (result->type)
    {

    case COMMAND_RESULT_TYPE_ACTOR_SET_X:
    {
        break;
    }

    case COMMAND_RESULT_TYPE_ACTOR_SET_Y:
    {
        break;
    }

    case COMMAND_RESULT_TYPE_ACTOR_SET_POSITION:
    {
        break;
    }

    case COMMAND_RESULT_TYPE_ACTOR_SET_GLYPH:
    {
        break;
    }

    case COMMAND_RESULT_TYPE_ACTOR_SET_COLOUR:
    {
        break;
    }

    case COMMAND_RESULT_TYPE_ACTOR_SET_R:
    {
        break;
    }

    case COMMAND_RESULT_TYPE_ACTOR_SET_G:
    {
        break;
    }

    case COMMAND_RESULT_TYPE_ACTOR_SET_B:
    {
        break;
    }

    case COMMAND_RESULT_TYPE_ACTOR_SET_A:
    {
        break;
    }

    case COMMAND_RESULT_TYPE_ACTOR_SET_CURRENT_HP:
    {
        break;
    }

    case COMMAND_RESULT_TYPE_ACTOR_SET_MAX_HP:
    {
        break;
    }

    case COMMAND_RESULT_TYPE_ACTOR_SET_HP:
    {
        break;
    }

    case COMMAND_RESULT_TYPE_ACTOR_SET_ATTACK_POWER:
    {
        break;
    }

    case COMMAND_RESULT_TYPE_ACTOR_SET_NAME:
    {
        CommandResultParamsActorSetName *params =
            &result->params.actor_set_name;
        free(params->old_name);
        free(params->new_name);
        break;
    }

    case COMMAND_RESULT_TYPE_ACTOR_TOOK_DAMAGE:
    {
        break;
    }

    default:
    {
        break;
    }
    }
}
