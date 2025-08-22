#include "actor.h"

#include <stdio.h>
#include <stdlib.h>

// The concrete definition of the actor struct.
// This is hidden from other modules, which only see the opaque pointer.
struct actor
{
    int x;
    int y;
    char glyph;
    Colour colour;

    // Components (can be NULL)
    HealthComponent *health;
    CombatComponent *combat;
    AIComponent *ai;
    NameComponent *name;
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
    actor->health = NULL;
    actor->combat = NULL;
    actor->ai = NULL;
    actor->name = NULL;

    return actor;
}

void actor_free(Actor *actor)
{
    if (!actor)
    {
        return;
    }

    // Free each component if it exists.
    if (actor->health)
    {
        health_component_free(actor->health);
    }
    if (actor->combat)
    {
        combat_component_free(actor->combat);
    }
    if (actor->ai)
    {
        ai_component_free(actor->ai);
    }
    if (actor->name)
    {
        name_component_free(actor->name);
    }

    // Finally, free the actor struct itself.
    free(actor);
}

// --- Actor Component Management ---

void actor_add_health_component(Actor *actor, HealthComponent *component)
{
    actor->health = component;
}

void actor_add_combat_component(Actor *actor, CombatComponent *component)
{
    actor->combat = component;
}

void actor_add_ai_component(Actor *actor, AIComponent *component)
{
    actor->ai = component;
}

void actor_add_name_component(Actor *actor, NameComponent *component)
{
    actor->name = component;
}

HealthComponent *actor_get_health_component(const Actor *actor)
{
    return actor->health;
}

CombatComponent *actor_get_combat_component(const Actor *actor)
{
    return actor->combat;
}

AIComponent *actor_get_ai_component(const Actor *actor)
{
    return actor->ai;
}

NameComponent *actor_get_name_component(const Actor *actor)
{
    return actor->name;
}

// --- Actor Getters/Setters ---

void actor_get_position(const Actor *actor, int *x, int *y)
{
    *x = actor->x;
    *y = actor->y;
}

void actor_set_position(Actor *actor, int x, int y)
{
    actor->x = x;
    actor->y = y;
}

char actor_get_glyph(const Actor *actor)
{
    return actor->glyph;
}

Colour actor_get_colour(const Actor *actor)
{
    return actor->colour;
}
