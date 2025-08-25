#ifndef COMMAND_RESULT_H
#define COMMAND_RESULT_H

#include <stdbool.h>

#include "colour.h"

typedef struct actor Actor;

typedef enum command_result_type
{
    COMMAND_RESULT_TYPE_NULL,
    COMMAND_RESULT_TYPE_ACTOR_SET_X,
    COMMAND_RESULT_TYPE_ACTOR_SET_Y,
    COMMAND_RESULT_TYPE_ACTOR_SET_POSITION,
    COMMAND_RESULT_TYPE_ACTOR_SET_GLYPH,
    COMMAND_RESULT_TYPE_ACTOR_SET_COLOUR,
    COMMAND_RESULT_TYPE_ACTOR_SET_R,
    COMMAND_RESULT_TYPE_ACTOR_SET_G,
    COMMAND_RESULT_TYPE_ACTOR_SET_B,
    COMMAND_RESULT_TYPE_ACTOR_SET_A,
    COMMAND_RESULT_TYPE_ACTOR_SET_CURRENT_HP,
    COMMAND_RESULT_TYPE_ACTOR_SET_MAX_HP,
    COMMAND_RESULT_TYPE_ACTOR_SET_HP,
    COMMAND_RESULT_TYPE_ACTOR_SET_ATTACK_POWER,
    COMMAND_RESULT_TYPE_ACTOR_SET_NAME,
    COMMAND_RESULT_TYPE_ACTOR_TOOK_DAMAGE
} CommandResultType;

typedef struct command_result_params_actor_set_x
{
    Actor *actor;
    int old_x;
    int new_x;
} CommandResultParamsActorSetX;

typedef struct command_result_params_actor_set_y
{
    Actor *actor;
    int old_y;
    int new_y;
} CommandResultParamsActorSetY;

typedef struct command_result_params_actor_set_position
{
    Actor *actor;
    int old_x;
    int old_y;
    int new_x;
    int new_y;
} CommandResultParamsActorSetPosition;

typedef struct command_result_params_actor_set_glyph
{
    Actor *actor;
    char old_glyph;
    char new_glyph;
} CommandResultParamsActorSetGlyph;

typedef struct command_result_params_actor_set_colour
{
    Actor *actor;
    Colour old_colour;
    Colour new_colour;
} CommandResultParamsActorSetColour;

typedef struct command_result_params_actor_set_r
{
    Actor *actor;
    unsigned char old_r;
    unsigned char new_r;
} CommandResultParamsActorSetR;

typedef struct command_result_params_actor_set_g
{
    Actor *actor;
    unsigned char old_g;
    unsigned char new_g;
} CommandResultParamsActorSetG;

typedef struct command_result_params_actor_set_b
{
    Actor *actor;
    unsigned char old_b;
    unsigned char new_b;
} CommandResultParamsActorSetB;

typedef struct command_result_params_actor_set_a
{
    Actor *actor;
    unsigned char old_a;
    unsigned char new_a;
} CommandResultParamsActorSetA;

typedef struct command_result_params_actor_set_current_hp
{
    Actor *actor;
    int old_current_hp;
    int new_current_hp;
} CommandResultParamsActorSetCurrentHp;

typedef struct command_result_params_actor_set_max_hp
{
    Actor *actor;
    int old_max_hp;
    int new_max_hp;
} CommandResultParamsActorSetMaxHp;

typedef struct command_result_params_actor_set_hp
{
    Actor *actor;
    int old_current_hp;
    int new_current_hp;
    int old_max_hp;
    int new_max_hp;
} CommandResultParamsActorSetHp;

typedef struct command_result_params_actor_set_attack_power
{
    Actor *actor;
    int old_attack_power;
    int new_attack_power;
} CommandResultParamsActorSetAttackPower;

typedef struct command_result_params_actor_set_name
{
    Actor *actor;
    char *old_name;
    char *new_name;
} CommandResultParamsActorSetName;

typedef struct command_result_params_actor_took_damage
{
    Actor *actor;
    int amount;
    bool did_die;
} CommandResultParamsActorTookDamage;

typedef struct command_result
{
    CommandResultType type;
    union
    {
        CommandResultParamsActorSetX actor_set_x;
        CommandResultParamsActorSetY actor_set_y;
        CommandResultParamsActorSetPosition actor_set_position;
        CommandResultParamsActorSetGlyph actor_set_glyph;
        CommandResultParamsActorSetColour actor_set_colour;
        CommandResultParamsActorSetR actor_set_r;
        CommandResultParamsActorSetG actor_set_g;
        CommandResultParamsActorSetB actor_set_b;
        CommandResultParamsActorSetA actor_set_a;
        CommandResultParamsActorSetCurrentHp actor_set_current_hp;
        CommandResultParamsActorSetMaxHp actor_set_max_hp;
        CommandResultParamsActorSetHp actor_set_hp;
        CommandResultParamsActorSetAttackPower actor_set_attack_power;
        CommandResultParamsActorSetName actor_set_name;
        CommandResultParamsActorTookDamage actor_took_damage;
    } params;
} CommandResult;

CommandResult command_result_actor_set_x_create(
    Actor *actor,
    int old_x,
    int new_x);

CommandResult command_result_actor_set_y_create(
    Actor *actor,
    int old_y,
    int new_y);

CommandResult command_result_actor_set_position_create(
    Actor *actor,
    int old_x,
    int old_y,
    int new_x,
    int new_y);

CommandResult command_result_actor_set_glyph_create(
    Actor *actor,
    char old_glyph,
    char new_glyph);

CommandResult command_result_actor_set_colour_create(
    Actor *actor,
    Colour old_colour,
    Colour new_colour);

CommandResult command_result_actor_set_r_create(
    Actor *actor,
    unsigned char old_r,
    unsigned char new_r);

CommandResult command_result_actor_set_g_create(
    Actor *actor,
    unsigned char old_g,
    unsigned char new_g);

CommandResult command_result_actor_set_b_create(
    Actor *actor,
    unsigned char old_b,
    unsigned char new_b);

CommandResult command_result_actor_set_a_create(
    Actor *actor,
    unsigned char old_a,
    unsigned char new_a);

CommandResult command_result_actor_set_current_hp_create(
    Actor *actor,
    int old_current_hp,
    int new_current_hp);

CommandResult command_result_actor_set_max_hp_create(
    Actor *actor,
    int old_max_hp,
    int new_max_hp);

CommandResult command_result_actor_set_hp_create(
    Actor *actor,
    int old_current_hp,
    int old_max_hp,
    int new_current_hp,
    int new_max_hp);

CommandResult command_result_actor_set_attack_power_create(
    Actor *actor,
    int old_attack_power,
    int new_attack_power);

CommandResult command_result_actor_set_name_create(
    Actor *actor,
    const char *old_name,
    const char *new_name);

CommandResult command_result_actor_took_damage_create(
    Actor *actor,
    int amount,
    bool did_die);

void command_result_free(CommandResult *command_result);

#endif // COMMAND_RESULT_H
