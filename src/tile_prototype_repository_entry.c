#include "tile_prototype_repository_entry.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tile_prototype.h"

TilePrototypeRepositoryEntry tile_prototype_repository_entry_create(
    const size_t id,
    const char *name,
    const TilePrototype prototype)
{
    if (!name)
    {
        fprintf(
            stderr,
            "tile_prototype_repository_entry_create: name cannot be null\n");
        exit(EXIT_FAILURE);
    }

    if (strlen(name) == 0)
    {
        fprintf(
            stderr,
            "tile_prototype_repository_entry_create: name cannot have length "
            "of 0\n");
        exit(EXIT_FAILURE);
    }

    if (strlen(name) > 255)
    {
        fprintf(
            stderr,
            "tile_prototype_repository_entry_create: name length cannot be "
            "larger than 255\n");
        exit(EXIT_FAILURE);
    }

    TilePrototypeRepositoryEntry entry = {0};

    entry.id = id;
    entry.name = malloc(strlen(name) + 1);

    if (!entry.name)
    {
        perror("tile_prototype_repository_entry_create: error allocating tile "
               "repository name");
        exit(EXIT_FAILURE);
    }

    strcpy(entry.name, name);

    entry.prototype = prototype;

    return entry;
}

void tile_prototype_repository_entry_free(TilePrototypeRepositoryEntry *entry)
{
    entry->id = 0;
    free(entry->name);
    entry->name = NULL;
    entry->prototype = (TilePrototype){0};
}
