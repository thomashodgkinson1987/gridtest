#ifndef TILE_PROTOTYPE_REPOSITORY_H
#define TILE_PROTOTYPE_REPOSITORY_H

#include <stddef.h>

#include "tile_prototype.h"
#include "tile_prototype_repository_entry.h"
#include "tile_prototype_repository_entry_array.h"

typedef struct tile_prototype_repository
{
    TilePrototypeRepositoryEntryArray entries;
} TilePrototypeRepository;

TilePrototypeRepository tile_prototype_repository_create(void);
void tile_prototype_repository_free(TilePrototypeRepository *repository);

void tile_prototype_repository_add(
    TilePrototypeRepository *repository,
    size_t id,
    const char *name,
    TilePrototype prototype);

const TilePrototype *tile_prototype_repository_get_by_id(
    const TilePrototypeRepository *repository,
    size_t id);
const TilePrototype *tile_prototype_repository_get_by_name(
    const TilePrototypeRepository *repository,
    const char *name);

#endif // TILE_PROTOTYPE_REPOSITORY_H
