#include "actor.h"
#include "colour.h"
#include "components.h"

#include <stdio.h>
#include <stdlib.h>

// The concrete definition of the actor struct.
// This is hidden from other modules, which only see the opaque pointer.
struct actor
{
    int x;
    int y;
    Colour colour;
    char glyph;

    // Components (can be NULL)
    HealthComponent *health_component;
    CombatComponent *combat_component;
    AIComponent *ai_component;
    NameComponent *name_component;
};

// --- Actor Creation/Destruction ---

Actor *actor_create(int x, int y, char glyph, Colour colour)
{
    Actor *actor = malloc(sizeof(*actor));
    if (!actor)
    {
        char error_msg[100];
        snprintf(
            error_msg,
            sizeof(error_msg),
            "%s: Failed to allocate memory",
            __func__);
        perror(error_msg);
        exit(EXIT_FAILURE);
    }

    actor->x = x;
    actor->y = y;
    actor->glyph = glyph;
    actor->colour = colour;

    // Initialize all component pointers to NULL.
    // Components must be created and added separately.
    actor->health_component = NULL;
    actor->combat_component = NULL;
    actor->ai_component = NULL;
    actor->name_component = NULL;

    return actor;
}

void actor_free(Actor *actor)
{
    if (!actor)
    {
        return;
    }

    // Free each component if it exists.
    if (actor->health_component)
    {
        health_component_free(actor->health_component);
    }
    if (actor->combat_component)
    {
        combat_component_free(actor->combat_component);
    }
    if (actor->ai_component)
    {
        ai_component_free(actor->ai_component);
    }
    if (actor->name_component)
    {
        name_component_free(actor->name_component);
    }

    // Finally, free the actor struct itself.
    free(actor);
}

// --- Actor Component Management ---

void actor_add_health_component(Actor *actor, int max_hp)
{
    if (actor->health_component)
    {
        fprintf(stderr, "%s: component already exists\n", __func__);
    }
    else
    {
        actor->health_component = health_component_create(max_hp);
    }
}
void actor_add_combat_component(Actor *actor, int attack_power)
{
    if (actor->combat_component)
    {
        fprintf(stderr, "%s: component already exists\n", __func__);
    }
    else
    {
        actor->combat_component = combat_component_create(attack_power);
    }
}
void actor_add_ai_component(Actor *actor)
{
    if (actor->ai_component)
    {
        fprintf(stderr, "%s: component already exists\n", __func__);
    }
    else
    {
        actor->ai_component = ai_component_create();
    }
}
void actor_add_name_component(Actor *actor, const char *name)
{
    if (actor->name_component)
    {
        fprintf(stderr, "%s: component already exists\n", __func__);
    }
    else
    {
        actor->name_component = name_component_create(name);
    }
}

void actor_remove_health_component(Actor *actor)
{
    if (!actor->health_component)
    {
        fprintf(stderr, "%s: component does not exists\n", __func__);
    }
    else
    {
        health_component_free(actor->health_component);
        actor->health_component = NULL;
    }
}
void actor_remove_combat_component(Actor *actor)
{
    if (!actor->combat_component)
    {
        fprintf(stderr, "%s: component does not exists\n", __func__);
    }
    else
    {
        combat_component_free(actor->combat_component);
        actor->combat_component = NULL;
    }
}
void actor_remove_ai_component(Actor *actor)
{
    if (!actor->ai_component)
    {
        fprintf(stderr, "%s: component does not exists\n", __func__);
    }
    else
    {
        ai_component_free(actor->ai_component);
        actor->ai_component = NULL;
    }
}
void actor_remove_name_component(Actor *actor)
{
    if (!actor->name_component)
    {
        fprintf(stderr, "%s: component does not exists\n", __func__);
    }
    else
    {
        name_component_free(actor->name_component);
        actor->name_component = NULL;
    }
}

const HealthComponent *actor_get_health_component(const Actor *actor)
{
    return actor->health_component;
}
const CombatComponent *actor_get_combat_component(const Actor *actor)
{
    return actor->combat_component;
}
const AIComponent *actor_get_ai_component(const Actor *actor)
{
    return actor->ai_component;
}
const NameComponent *actor_get_name_component(const Actor *actor)
{
    return actor->name_component;
}

HealthComponent *actor_get_health_component_mut(Actor *actor)
{
    return actor->health_component;
}
CombatComponent *actor_get_combat_component_mut(Actor *actor)
{
    return actor->combat_component;
}
AIComponent *actor_get_ai_component_mut(Actor *actor)
{
    return actor->ai_component;
}
NameComponent *actor_get_name_component_mut(Actor *actor)
{
    return actor->name_component;
}

// --- Actor Getters/Setters ---

int actor_get_x(const Actor *actor)
{
    return actor->x;
}
int actor_get_y(const Actor *actor)
{
    return actor->y;
}
void actor_get_position(const Actor *actor, int *x, int *y)
{
    *x = actor->x;
    *y = actor->y;
}
char actor_get_glyph(const Actor *actor)
{
    return actor->glyph;
}
Colour actor_get_colour(const Actor *actor)
{
    return actor->colour;
}
unsigned char actor_get_r(const Actor *actor)
{
    return actor->colour.r;
}
unsigned char actor_get_g(const Actor *actor)
{
    return actor->colour.g;
}
unsigned char actor_get_b(const Actor *actor)
{
    return actor->colour.b;
}
unsigned char actor_get_a(const Actor *actor)
{
    return actor->colour.a;
}

void actor_set_x(Actor *actor, int x)
{
    actor->x = x;
}
void actor_set_y(Actor *actor, int y)
{
    actor->y = y;
}
void actor_set_position(Actor *actor, int x, int y)
{
    actor->x = x;
    actor->y = y;
}
void actor_set_glyph(Actor *actor, char glyph)
{
    actor->glyph = glyph;
}
void actor_set_colour(Actor *actor, Colour colour)
{
    actor->colour = colour;
}
void actor_set_r(Actor *actor, unsigned char r)
{
    actor->colour.r = r;
}
void actor_set_g(Actor *actor, unsigned char g)
{
    actor->colour.g = g;
}
void actor_set_b(Actor *actor, unsigned char b)
{
    actor->colour.b = b;
}
void actor_set_a(Actor *actor, unsigned char a)
{
    actor->colour.a = a;
}
