#include "actor_hash_map.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h> // for size_t
#include <stdint.h> // for uint64_t
#include <stdlib.h>

#include "actor.h"

// --- Internal Module Definitions ---
typedef struct actor_hash_map_entry
{
    Actor *actor;
    bool is_tombstone;
} ActorHashMapEntry;

struct actor_hash_map
{
    ActorHashMapEntry *data;
    size_t count;
    size_t capacity;
};

// --- Static Function Declarations ---
static void rehash(ActorHashMap *hash_map, size_t new_capacity);

// --- Public Function Definitions ---
ActorHashMap *actor_hash_map_create(size_t initial_capacity)
{
    assert(initial_capacity);

    ActorHashMap *hash_map = malloc(sizeof(*hash_map));
    assert(hash_map);

    hash_map->count = 0;
    hash_map->capacity = initial_capacity;

    hash_map->data = calloc(hash_map->capacity, sizeof(*hash_map->data));
    assert(hash_map->data);

    return hash_map;
}
void actor_hash_map_free(ActorHashMap *hash_map)
{
    assert(hash_map);
    assert(hash_map->data);

    for (size_t i = 0; i < hash_map->capacity; ++i)
    {
        ActorHashMapEntry *entry = &hash_map->data[i];
        assert(entry);
        if (entry->actor)
            actor_free(entry->actor);
    }

    free(hash_map->data);
    free(hash_map);
}

size_t actor_hash_map_get_count(const ActorHashMap *hash_map)
{
    assert(hash_map);
    return hash_map->count;
}
size_t actor_hash_map_get_capacity(const ActorHashMap *hash_map)
{
    assert(hash_map);
    return hash_map->capacity;
}

void actor_hash_map_add(ActorHashMap *hash_map, const Actor *actor)
{
    assert(hash_map);
    assert(hash_map->data);
    assert(hash_map->capacity);
    assert(actor);

    if (hash_map->count >= hash_map->capacity * 0.7)
    {
        rehash(hash_map, hash_map->capacity * 2);
    }

    size_t index = actor_get_id(actor) % hash_map->capacity;
    ActorHashMapEntry *entry = &hash_map->data[index];

    while (1)
    {
        if (!entry->actor)
        {
            entry->actor = (Actor *)actor;
            hash_map->count++;
            break;
        }
        else
        {
            index = (index + 1) % hash_map->capacity;
            entry = &hash_map->data[index];
        }
    }
}
void actor_hash_map_remove(ActorHashMap *hash_map, uint64_t id)
{
    assert(hash_map);
    assert(hash_map->data);
    assert(hash_map->capacity);
    assert(hash_map->count);
    assert(hash_map->count < hash_map->capacity * 0.7);
    assert(id);

    size_t index = id % hash_map->capacity;
    ActorHashMapEntry *entry = &hash_map->data[index];

    while (1)
    {
        if (entry->actor && actor_get_id(entry->actor) == id)
        {
            entry->actor = NULL;
            entry->is_tombstone = true;
            hash_map->count--;
            break;
        }
        else if (
            (entry->actor && !actor_get_id(entry->actor) == id) ||
            entry->is_tombstone)
        {
            index = (index + 1) % hash_map->capacity;
            entry = &hash_map->data[index];
        }
        else
        {
            break;
        }
    }
}

const Actor *actor_hash_map_get(const ActorHashMap *hash_map, uint64_t id)
{
    assert(hash_map);
    assert(hash_map->data);
    assert(hash_map->count);
    assert(hash_map->capacity >= hash_map->count);
    assert(id);

    size_t index = id % hash_map->capacity;
    ActorHashMapEntry *entry = &hash_map->data[index];

    while (1)
    {
        if (entry->actor && actor_get_id(entry->actor) == id)
        {
            return hash_map->data[index].actor;
        }
        else if (
            (entry->actor && !actor_get_id(entry->actor) == id) ||
            entry->is_tombstone)
        {
            index = (index + 1) % hash_map->capacity;
            entry = &hash_map->data[index];
        }
        else
        {
            return NULL;
        }
    }
}
Actor *actor_hash_map_get_mut(ActorHashMap *hash_map, uint64_t id)
{
    assert(hash_map);
    assert(hash_map->data);
    assert(hash_map->count);
    assert(hash_map->capacity >= hash_map->count);
    assert(id);

    size_t index = id % hash_map->capacity;
    ActorHashMapEntry *entry = &hash_map->data[index];

    while (1)
    {
        if (entry->actor && actor_get_id(entry->actor) == id)
        {
            return hash_map->data[index].actor;
        }
        else if (
            (entry->actor && !actor_get_id(entry->actor) == id) ||
            entry->is_tombstone)
        {
            index = (index + 1) % hash_map->capacity;
            entry = &hash_map->data[index];
        }
        else
        {
            return NULL;
        }
    }
}

// --- Static Function Definitions ---
static void rehash(ActorHashMap *hash_map, size_t new_capacity)
{
    assert(hash_map);
    assert(hash_map->data);
    assert(hash_map->capacity < new_capacity);

    ActorHashMapEntry *new_data = calloc(new_capacity, sizeof(*new_data));
    assert(new_data);

    ActorHashMapEntry *old_data = hash_map->data;
    size_t old_capacity = hash_map->capacity;

    hash_map->data = new_data;
    hash_map->count = 0;
    hash_map->capacity = new_capacity;

    for (size_t i = 0; i < old_capacity; ++i)
    {
        ActorHashMapEntry *entry = &old_data[i];
        if (entry->actor)
        {
            actor_hash_map_add(hash_map, entry->actor);
        }
    }

    free(old_data);
}