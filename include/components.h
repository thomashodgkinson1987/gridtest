#ifndef COMPONENTS_H
#define COMPONENTS_H

// --- Health Component ---
// Component that confers health and the ability to take damage.
typedef struct health_component
{
    int max_hp;
    int current_hp;
} HealthComponent;

HealthComponent *health_component_create(int max_hp);
void health_component_free(HealthComponent *component);

// --- Combat Component ---
// Component that allows an actor to perform melee attacks.
typedef struct combat_component
{
    int attack_power;
} CombatComponent;

CombatComponent *combat_component_create(int attack_power);
void combat_component_free(CombatComponent *component);

// --- AI Component ---
// Component that allows an actor to be controlled by AI.
typedef struct ai_component
{
    int placeholder;
} AIComponent;

AIComponent *ai_component_create(void);
void ai_component_free(AIComponent *component);



#endif // COMPONENTS_H
