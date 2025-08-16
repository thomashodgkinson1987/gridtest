#include "tile_prototype_repository.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "tile_prototype_repository_entry.h"
#include "tile_prototype_repository_entry_array.h"

TilePrototypeRepository tile_prototype_repository_create(void)
{
    TilePrototypeRepository repository = {0};

    repository.entries = tile_prototype_repository_entry_array_create(1);

    return repository;
}

void tile_prototype_repository_free(TilePrototypeRepository *repository)
{
    for (size_t i = 0; i < repository->entries.count; ++i)
    {
        TilePrototypeRepositoryEntry *entry = &repository->entries.data[i];
        tile_prototype_repository_entry_free(entry);
    }

    tile_prototype_repository_entry_array_free(&repository->entries);
}

void tile_prototype_repository_add(
    TilePrototypeRepository *repository,
    size_t id,
    const char *name,
    TilePrototype prototype)
{
    for (size_t i = 0; i < repository->entries.count; ++i)
    {
        const TilePrototypeRepositoryEntry *_entry =
            tile_prototype_repository_entry_array_get(&repository->entries, i);

        if (_entry->id == id || strcmp(_entry->name, name) == 0)
        {
            fprintf(
                stderr,
                "tile_prototype_repository_add: either id (%zu) or name (%s) "
                "already exists (index %zu)\n",
                id,
                name,
                i);

            exit(EXIT_FAILURE);
        }
    }

    const TilePrototypeRepositoryEntry entry =
        tile_prototype_repository_entry_create(id, name, prototype);

    tile_prototype_repository_entry_array_push(&repository->entries, entry);
}

const TilePrototype *tile_prototype_repository_get_by_id(
    const TilePrototypeRepository *repository,
    size_t id)
{
    if (id >= repository->entries.count)
    {
        fprintf(
            stderr,
            "tile_prototype_repository_get_by_id: id (%zu) out of bounds (%zu)"
            "\n",
            id,
            repository->entries.count);

        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < repository->entries.count; ++i)
    {
        const TilePrototypeRepositoryEntry *entry =
            tile_prototype_repository_entry_array_get(&repository->entries, i);
        if (entry->id == id)
        {
            return &entry->prototype;
        }
    }

    fprintf(
        stderr,
        "tile_prototype_repository_get_by_id: tile entry with id %zu not found"
        "\n",
        id);

    exit(EXIT_FAILURE);
}

const TilePrototype *tile_prototype_repository_get_by_name(
    const TilePrototypeRepository *repository,
    const char *name)
{
    if (strlen(name) == 0 || strlen(name) > 255)
    {
        fprintf(
            stderr,
            "tile_prototype_repository_get_by_name: name cannot be 0 or "
            "greater than 255 (%zu)",
            strlen(name));

        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < repository->entries.count; ++i)
    {
        const TilePrototypeRepositoryEntry *entry =
            tile_prototype_repository_entry_array_get(&repository->entries, i);
        if (strcmp(entry->name, name) == 0)
        {
            return &entry->prototype;
        }
    }

    fprintf(
        stderr,
        "tile_prototype_repository_get_by_name: tile entry with name %s not "
        "found\n",
        name);

    exit(EXIT_FAILURE);
}
