#ifndef COMMAND_H
#define COMMAND_H

#include "colour.h"
#include "command_result.h"

typedef struct actor Actor;

typedef enum command_type
{
    COMMAND_TYPE_NULL,
    COMMAND_TYPE_ACTOR_SET_X,
    COMMAND_TYPE_ACTOR_SET_Y,
    COMMAND_TYPE_ACTOR_SET_POSITION,
    COMMAND_TYPE_ACTOR_SET_GLYPH,
    COMMAND_TYPE_ACTOR_SET_COLOUR,
    COMMAND_TYPE_ACTOR_SET_R,
    COMMAND_TYPE_ACTOR_SET_G,
    COMMAND_TYPE_ACTOR_SET_B,
    COMMAND_TYPE_ACTOR_SET_A,
    COMMAND_TYPE_ACTOR_SET_CURRENT_HP,
    COMMAND_TYPE_ACTOR_SET_MAX_HP,
    COMMAND_TYPE_ACTOR_SET_HP,
    COMMAND_TYPE_ACTOR_SET_ATTACK_POWER,
    COMMAND_TYPE_ACTOR_SET_NAME,
    COMMAND_TYPE_ACTOR_TRANSLATE_HEALTH
} CommandType;

typedef struct command_params_actor_set_x
{
    Actor *actor;
    int old_x;
    int new_x;
} CommandParamsActorSetX;

typedef struct command_params_actor_set_y
{
    Actor *actor;
    int old_y;
    int new_y;
} CommandParamsActorSetY;

typedef struct command_params_actor_set_position
{
    Actor *actor;
    int old_x;
    int old_y;
    int new_x;
    int new_y;
} CommandParamsActorSetPosition;

typedef struct command_params_actor_set_glyph
{
    Actor *actor;
    char old_glyph;
    char new_glyph;
} CommandParamsActorSetGlyph;

typedef struct command_params_actor_set_colour
{
    Actor *actor;
    Colour old_colour;
    Colour new_colour;
} CommandParamsActorSetColour;

typedef struct command_params_actor_set_r
{
    Actor *actor;
    unsigned char old_r;
    unsigned char new_r;
} CommandParamsActorSetR;

typedef struct command_params_actor_set_g
{
    Actor *actor;
    unsigned char old_g;
    unsigned char new_g;
} CommandParamsActorSetG;

typedef struct command_params_actor_set_b
{
    Actor *actor;
    unsigned char old_b;
    unsigned char new_b;
} CommandParamsActorSetB;

typedef struct command_params_actor_set_a
{
    Actor *actor;
    unsigned char old_a;
    unsigned char new_a;
} CommandParamsActorSetA;

typedef struct command_params_actor_set_current_hp
{
    Actor *actor;
    int old_current_hp;
    int new_current_hp;
} CommandParamsActorSetCurrentHp;

typedef struct command_params_actor_set_max_hp
{
    Actor *actor;
    int old_max_hp;
    int new_max_hp;
} CommandParamsActorSetMaxHp;

typedef struct command_params_actor_set_hp
{
    Actor *actor;
    int old_current_hp;
    int old_max_hp;
    int new_current_hp;
    int new_max_hp;
} CommandParamsActorSetHp;

typedef struct command_params_actor_set_attack_power
{
    Actor *actor;
    int old_attack_power;
    int new_attack_power;
} CommandParamsActorSetAttackPower;

typedef struct command_params_actor_set_name
{
    Actor *actor;
    char *old_name;
    char *new_name;
} CommandParamsActorSetName;

typedef struct command_params_actor_translate_health
{
    Actor *actor;
    int translation;
} CommandParamsActorTranslateHealth;

typedef struct command
{
    CommandType type;
    union
    {
        CommandParamsActorSetX actor_set_x;
        CommandParamsActorSetY actor_set_y;
        CommandParamsActorSetPosition actor_set_position;
        CommandParamsActorSetGlyph actor_set_glyph;
        CommandParamsActorSetColour actor_set_colour;
        CommandParamsActorSetR actor_set_r;
        CommandParamsActorSetG actor_set_g;
        CommandParamsActorSetB actor_set_b;
        CommandParamsActorSetA actor_set_a;
        CommandParamsActorSetCurrentHp actor_set_current_hp;
        CommandParamsActorSetMaxHp actor_set_max_hp;
        CommandParamsActorSetHp actor_set_hp;
        CommandParamsActorSetAttackPower actor_set_attack_power;
        CommandParamsActorSetName actor_set_name;
        CommandParamsActorTranslateHealth actor_translate_health;
    } params;
} Command;

Command command_actor_set_x_create(Actor *actor, int x);
Command command_actor_set_y_create(Actor *actor, int y);
Command command_actor_set_position_create(Actor *actor, int x, int y);
Command command_actor_set_glyph_create(Actor *actor, char glyph);
Command command_actor_set_colour_create(Actor *actor, Colour colour);
Command command_actor_set_r_create(Actor *actor, unsigned char r);
Command command_actor_set_g_create(Actor *actor, unsigned char g);
Command command_actor_set_b_create(Actor *actor, unsigned char b);
Command command_actor_set_a_create(Actor *actor, unsigned char a);
Command command_actor_set_current_hp_create(Actor *actor, int current_hp);
Command command_actor_set_max_hp_create(Actor *actor, int max_hp);
Command command_actor_set_hp_create(Actor *actor, int current_hp, int max_hp);
Command command_actor_set_attack_power_create(Actor *actor, int attack_power);
Command command_actor_set_name_create(Actor *actor, const char *name);
Command command_actor_translate_health_create(Actor *actor, int translation);

void command_free(Command *command);
CommandResult command_execute(Command *command);
const char *command_get_name_from_type(CommandType type);

#endif // COMMAND_H
