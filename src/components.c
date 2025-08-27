#include "components.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"

// --- Health Component ---

HealthComponent *health_component_create(int max_hp)
{
    HealthComponent *component = malloc(sizeof(*component));
    if (!component)
    {
        log_perror("Health component allocation failure");
        log_fatal(
            "%s: Fatal error due to health component allocation failure",
            __func__);
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
        log_perror("Combat component allocation failure");
        log_fatal(
            "%s: Fatal error due to combat component allocation failure",
            __func__);
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
        log_perror("AI component allocation failure");
        log_fatal(
            "%s: Fatal error due to AI component allocation failure",
            __func__);
    }

    component->placeholder = 0; // Initialize any future AI data here

    return component;
}

void ai_component_free(AIComponent *component)
{
    free(component);
}


