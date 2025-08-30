#include "actor.h"

#include <stdlib.h>

#include "colour.h"
#include "component.h"
#include "component_array.h"
#include "log.h"

// The concrete definition of the actor struct.

struct actor
{
    int x;
    int y;
    Colour colour;
    char glyph;
    char *name;
    ComponentArray components;
};

// --- Static Functions ---

static Component *find_component(
    Actor *actor,
    ComponentType type,
    size_t *out_index)
{
    for (size_t i = 0; i < component_array_get_count(&actor->components); ++i)
    {
        Component *component = component_array_get(&actor->components, i);
        if (component->type == type)
        {
            if (out_index)
                *out_index = i;
            return component;
        }
    }

    if (out_index)
        *out_index = (size_t)-1;
    return NULL;
}

// --- Actor Creation/Destruction ---

Actor *actor_create(int x, int y, char glyph, Colour colour, const char *name)
{
    if (!name || strlen(name) == 0)
    {
        log_fatal("%s: Name cannot be null or 0", __func__);
    }

    Actor *actor = malloc(sizeof(*actor));
    if (!actor)
    {
        log_perror("Actor allocation failure");
        log_fatal("%s: Fatal error due to actor allocation failure", __func__);
    }

    actor->x = x;
    actor->y = y;
    actor->glyph = glyph;
    actor->colour = colour;
    actor->name = strdup(name);

    if (!actor->name)
    {
        log_perror("Actor name allocation failure");
        log_fatal(
            "%s: Fatal error due to actor name allocation failure",
            __func__);
    }

    actor->components = component_array_create(1);

    return actor;
}

void actor_free(Actor *actor)
{
    free(actor->name);

    for (size_t i = 0; i < component_array_get_count(&actor->components); ++i)
    {
        Component *component = component_array_get(&actor->components, i);
        component_free(component);
    }

    component_array_free(&actor->components);

    free(actor);
}

// --- Actor Component Management ---

void actor_add_component(Actor *actor, Component *component)
{
    if (find_component(actor, component->type, NULL))
    {
        log_fatal(
            "%s: Actor already has [%s] component",
            __func__,
            component_get_name_from_type(component->type));
    }

    component_array_push(&actor->components, component);
}

void actor_remove_component(Actor *actor, ComponentType type)
{
    size_t index = 0;

    if (!find_component(actor, type, &index))
    {
        log_fatal(
            "%s: Actor does not have a [%s] component",
            __func__,
            component_get_name_from_type(type));
    }

    component_array_remove(&actor->components, index);
}

const Component *actor_get_component(Actor *actor, ComponentType type)
{
    return find_component(actor, type, NULL);
}

Component *actor_get_component_mut(Actor *actor, ComponentType type)
{
    return find_component(actor, type, NULL);
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
const char *actor_get_name(const Actor *actor)
{
    return actor->name;
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
void actor_set_name(Actor *actor, const char *name)
{
    char *new_pointer = realloc(actor->name, strlen(name) + 1);
    if (!new_pointer)
    {
        log_perror("Name reallocation failure");
        log_fatal(
            "%s: Fatal error due to name reallocation failure",
            __func__);
    }
    strncpy(new_pointer, name, strlen(name) + 1);
    actor->name = new_pointer;
}
