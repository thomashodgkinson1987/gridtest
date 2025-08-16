#ifndef TILE_PROTOTYPE_REPOSITORY_ENTRY_H
#define TILE_PROTOTYPE_REPOSITORY_ENTRY_H

#include <stddef.h>

#include "tile_prototype.h"

typedef struct tile_prototype_repository_entry
{
    size_t id;
    char *name;
    TilePrototype prototype;
} TilePrototypeRepositoryEntry;

TilePrototypeRepositoryEntry tile_prototype_repository_entry_create(
    size_t id,
    const char *name,
    TilePrototype prototype);
void tile_prototype_repository_entry_free(TilePrototypeRepositoryEntry *entry);

#endif // TILE_PROTOTYPE_REPOSITORY_ENTRY_H
