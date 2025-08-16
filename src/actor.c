#include "actor.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "actor_colour.h"

#define MAX_NAME_LENGTH 255

typedef struct actor
{
    int x;
    int y;
    ActorColour colour;
    char name[MAX_NAME_LENGTH];
} Actor;

Actor *actor_create(
    const int x,
    const int y,
    const ActorColour colour,
    const char *name)
{
    if (!name)
    {
        fprintf(stderr, "%s: name cannot be NULL\n", __func__);
        return false;
    }

    if (strlen(name) == 0)
    {
        fprintf(stderr, "%s: name cannot have a length of 0\n", __func__);
        return NULL;
    }

    if (strlen(name) >= MAX_NAME_LENGTH)
    {
        fprintf(
            stderr,
            "%s: name cannot be greater than %zu characters\n",
            __func__,
            MAX_NAME_LENGTH);
        return NULL;
    }

    Actor *actor = malloc(sizeof(Actor));

    if (!actor)
    {
        char err_msg[256];
        snprintf(
            err_msg,
            sizeof(err_msg),
            "%s: error allocating memory",
            __func__);
        perror(err_msg);
        return NULL;
    }

    actor->x = x;
    actor->y = y;
    actor->colour = colour;
    strncpy(actor->name, name, MAX_NAME_LENGTH - 1);
    actor->name[MAX_NAME_LENGTH - 1] = '\0';

    return actor;
}

void actor_free(Actor *actor)
{
    free(actor);
}

int actor_get_x(const Actor *actor)
{
    return actor->x;
}

int actor_get_y(const Actor *actor)
{
    return actor->y;
}

ActorColour actor_get_colour(const Actor *actor)
{
    return actor->colour;
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
    actor_set_x(actor, x);
    actor_set_y(actor, y);
}

void actor_set_colour(Actor *actor, ActorColour colour)
{
    actor->colour = colour;
}

bool actor_set_name(Actor *actor, const char *name)
{
    if (!name)
    {
        fprintf(stderr, "%s: name cannot be NULL\n", __func__);
        return false;
    }

    if (strlen(name) == 0)
    {
        fprintf(stderr, "%s: name cannot have a length of 0\n", __func__);
        return false;
    }

    if (strlen(name) >= MAX_NAME_LENGTH)
    {
        fprintf(
            stderr,
            "%s: name cannot be greater than %zu characters\n",
            __func__,
            MAX_NAME_LENGTH);
        return false;
    }

    strncpy(actor->name, name, MAX_NAME_LENGTH - 1);
    actor->name[MAX_NAME_LENGTH - 1] = '\0';

    return true;
}

void actor_translate_x(Actor *actor, int translation_x)
{
    actor_set_x(actor, actor_get_x(actor) + translation_x);
}

void actor_translate_y(Actor *actor, int translation_y)
{
    actor_set_y(actor, actor_get_y(actor) + translation_y);
}

void actor_translate_position(
    Actor *actor,
    int translation_x,
    int translation_y)
{
    actor_translate_x(actor, translation_x);
    actor_translate_y(actor, translation_y);
}
