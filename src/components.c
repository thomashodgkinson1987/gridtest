#include "components.h"

#include <stdlib.h>
#include <stdio.h>

// --- Health Component ---

HealthComponent *health_component_create(int max_hp)
{
    HealthComponent *component = malloc(sizeof(*component));
    if (!component)
    {
        // Using __func__ makes error messages more robust.
        char error_msg[100];
        snprintf(
            error_msg,
            sizeof(error_msg),
            "%s: Failed to allocate memory",
            __func__);
        perror(error_msg);
        exit(EXIT_FAILURE);
    }

    component->max_hp = max_hp;
    component->current_hp = max_hp;

    return component;
}

void health_component_free(HealthComponent *component)
{
    free(component);
}

// --- Combat Component ---

CombatComponent *combat_component_create(int attack_power)
{
    CombatComponent *component = malloc(sizeof(*component));
    if (!component)
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

    component->attack_power = attack_power;

    return component;
}

void combat_component_free(CombatComponent *component)
{
    free(component);
}

// --- AI Component ---

AIComponent *ai_component_create(void)
{
    AIComponent *component = malloc(sizeof(*component));
    if (!component)
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

    component->placeholder = 0; // Initialize any future AI data here

    return component;
}

void ai_component_free(AIComponent *component)
{
    free(component);
}
