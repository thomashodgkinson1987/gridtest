#include "components.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Health Component ---

HealthComponent *health_component_create(int max_hp)
{
    HealthComponent *component = malloc(sizeof(*component));
    if (!component)
    {
        perror("[FATAL] Health component allocation failure");
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
        perror("[FATAL] Combat component allocation failure");
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
        perror("[FATAL] AI component allocation failure");
        exit(EXIT_FAILURE);
    }

    component->placeholder = 0; // Initialize any future AI data here

    return component;
}

void ai_component_free(AIComponent *component)
{
    free(component);
}

// --- Name Component ---

NameComponent *name_component_create(const char *name)
{
    NameComponent *component = malloc(sizeof(*component));
    if (!component)
    {
        perror("[FATAL] Name component allocation failure");
        exit(EXIT_FAILURE);
    }

    component->name = malloc(strlen(name) + 1);
    if (!component->name)
    {
        perror("[FATAL] Name component name allocation failure");
        exit(EXIT_FAILURE);
    }

    strncpy(component->name, name, strlen(name) + 1);

    return component;
}

void name_component_free(NameComponent *component)
{
    free(component->name);
    free(component);
}
