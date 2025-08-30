#ifndef COMPONENT_H
#define COMPONENT_H

typedef enum component_type
{
    COMPONENT_TYPE_NULL,
    COMPONENT_TYPE_HEALTH,
    COMPONENT_TYPE_COMBAT,
    COMPONENT_TYPE_AI,
    COMPONENT_TYPE_COUNT
} ComponentType;

typedef struct component_params_health
{
    int current_hp;
    int max_hp;
} ComponentParamsHealth;

typedef struct component_params_combat
{
    int attack_power;
} ComponentParamsCombat;

typedef struct component_params_ai
{
    int placeholder;
} ComponentParamsAi;

typedef struct component
{
    ComponentType type;
    union
    {
        ComponentParamsHealth health;
        ComponentParamsCombat combat;
        ComponentParamsAi ai;
    } params;
} Component;

Component *component_health_create(int current_hp, int max_hp);
Component *component_combat_create(int attack_power);
Component *component_ai_create(void);

void component_free(Component *component);

const char *component_get_name_from_type(ComponentType type);

#endif // COMPONENT_H
