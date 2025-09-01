#ifndef ACTOR_HASH_MAP_H
#define ACTOR_HASH_MAP_H

#include <stddef.h>
#include <stdint.h>

// --- Forward Declarations ---
typedef struct actor Actor;
typedef struct actor_hash_map ActorHashMap;

// --- Public Function Prototypes ---
ActorHashMap *actor_hash_map_create(size_t initial_capacity);
void actor_hash_map_free(ActorHashMap *hash_map);

size_t actor_hash_map_get_count(const ActorHashMap *hash_map);
size_t actor_hash_map_get_capacity(const ActorHashMap *hash_map);

void actor_hash_map_add(ActorHashMap *hash_map, const Actor *actor);
void actor_hash_map_remove(ActorHashMap *hash_map, uint64_t id);

const Actor *actor_hash_map_get(const ActorHashMap *hash_map, uint64_t id);
Actor *actor_hash_map_get_mut(const ActorHashMap *hash_map, uint64_t id);

#endif // ACTOR_HASH_MAP_H
