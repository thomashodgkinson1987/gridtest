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
    HealthComponent* health;
    CombatComponent* combat;
    AIComponent* ai;
};


// --- Actor Creation/Destruction ---

Actor* actor_create(int x, int y, char glyph, Colour colour)
{
    Actor* actor = malloc(sizeof(*actor));
    if (!actor)
    {
        char error_msg[100];
        snprintf(error_msg, sizeof(error_msg), "%s: Failed to allocate memory", __func__);
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

    return actor;
}

void actor_free(Actor* actor)
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

    // Finally, free the actor struct itself.
    free(actor);
}


// --- Actor Component Management ---

void actor_add_health_component(Actor* actor, HealthComponent* component)
{
    actor->health = component;
}

void actor_add_combat_component(Actor* actor, CombatComponent* component)
{
    actor->combat = component;
}

void actor_add_ai_component(Actor* actor, AIComponent* component)
{
    actor->ai = component;
}

HealthComponent* actor_get_health_component(const Actor* actor)
{
    return actor->health;
}

CombatComponent* actor_get_combat_component(const Actor* actor)
{
    return actor->combat;
}

AIComponent* actor_get_ai_component(const Actor* actor)
{
    return actor->ai;
}


// --- Actor Getters/Setters ---

void actor_get_position(const Actor* actor, int* x, int* y)
{
    *x = actor->x;
    *y = actor->y;
}

void actor_set_position(Actor* actor, int x, int y)
{
    actor->x = x;
    actor->y = y;
}

char actor_get_glyph(const Actor* actor)
{
    return actor->glyph;
}

Colour actor_get_colour(const Actor* actor)
{
    return actor->colour;
}


// --- Actor Actions (Commands) ---

void actor_attack(Actor* attacker, Actor* target)
{
    // An attack requires the attacker to have a combat component
    // and the target to have a health component.
    CombatComponent* combat = attacker->combat;
    HealthComponent* health = target->health;

    if (!combat || !health)
    {
        // This attack is impossible, so do nothing.
        return;
    }

    int damage = combat->attack_power;

    // For now, we'll just print to the console.
    // Later, this will go into a message log.
    printf("Attacker hits for %d damage!\n", damage);

    actor_take_damage(target, damage);
}

void actor_take_damage(Actor* actor, int amount)
{
    HealthComponent* health = actor->health;
    if (!health)
    {
        // Cannot take damage if it doesn't have health.
        return;
    }

    health->current_hp -= amount;

    // Check for death
    if (health->current_hp <= 0)
    {
        printf("Actor has died!\n");
        // In the future, we would add logic here to handle death:
        // - Change glyph to a corpse '%'
        // - Make non-blocking
        // - Remove AI and Combat components
        // - Drop loot, etc.
    }
}
