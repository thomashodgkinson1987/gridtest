#include "component.h"

#include <stdlib.h>

#include "log.h"

Component *component_health_create(int current_hp, int max_hp)
{
    Component *component = malloc(sizeof(*component));
    if (!component)
    {
        log_perror("Component allocation failure");
        log_fatal("%s: Fatal error", __func__);
    }

    component->type = COMPONENT_TYPE_HEALTH;
    component->params.health.current_hp = current_hp;
    component->params.health.max_hp = max_hp;

    return component;
}

Component *component_combat_create(int attack_power)
{
    Component *component = malloc(sizeof(*component));
    if (!component)
    {
        log_perror("Component allocation failure");
        log_fatal("%s: Fatal error", __func__);
    }

    component->type = COMPONENT_TYPE_COMBAT;
    component->params.combat.attack_power = attack_power;

    return component;
}

Component *component_ai_create(void)
{
    Component *component = malloc(sizeof(*component));
    if (!component)
    {
        log_perror("Component allocation failure");
        log_fatal("%s: Fatal error", __func__);
    }

    component->type = COMPONENT_TYPE_AI;
    component->params.ai.placeholder = 0;

    return component;
}

void component_free(Component *component)
{
    free(component);
}

const char *component_get_name_from_type(ComponentType type)
{
    switch (type)
    {
    case COMPONENT_TYPE_NULL:
    {
        return "NULL";
    }

    case COMPONENT_TYPE_HEALTH:
    {
        return "HEALTH";
    }

    case COMPONENT_TYPE_COMBAT:
    {
        return "COMBAT";
    }

    case COMPONENT_TYPE_AI:
    {
        return "AI";
    }

    default:
    {
        return "UNKNOWN";
    }
    }
}
