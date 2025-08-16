#include "game.h"

#include "raylib.h"

#include "actor.h"
#include "actor_array.h"
#include "actor_colour.h"
#include "constants.h"
#include "tile.h"
#include "tile_colour.h"
#include "tile_flags.h"
#include "tile_map.h"
#include "tile_prototype.h"
#include "tile_prototype_repository.h"
#include "world.h"

// ---------------------------------------------------------------------------
// Static Globals
// ---------------------------------------------------------------------------

static TilePrototypeRepository tile_prototype_repository;
static World *world;
static Actor *player_actor;

// ---------------------------------------------------------------------------
// Static Function Prototypes
// ---------------------------------------------------------------------------

static void game_init_tile_prototype_repository(
    TilePrototypeRepository *repository);
static void game_free_tile_prototype_repository(
    TilePrototypeRepository *repository);

static void game_tick_actors(
    World *world,
    Actor *player_actor);

static void game_draw_tile_map(
    World *world,
    size_t tile_width,
    size_t tile_height);
static void game_draw_actors(
    const World *world,
    size_t tile_width,
    size_t tile_height);

static Tile game_create_tile_from_prototype(
    TilePrototype prototype);
static Tile game_create_tile_from_id(
    const TilePrototypeRepository *repository,
    size_t id);
static Tile game_create_tile_from_name(
    const TilePrototypeRepository *repository,
    const char *name);

// ---------------------------------------------------------------------------
// Public Functions
// ---------------------------------------------------------------------------

void game_init(void)
{
    game_init_tile_prototype_repository(&tile_prototype_repository);

    world = world_create(8, 8, &tile_prototype_repository);

    const ActorColour colour = actor_colour_create(0, 0, 255, 255);
    player_actor = actor_create(0, 0, colour, "player");

    if (!player_actor)
    {
        fprintf(
            stderr,
            "%s: error creating player actor\n",
            __func__);
        exit(EXIT_FAILURE);
    }

    world_add_actor(world, player_actor);
}

void game_free(void)
{
    world_free(world);
    game_free_tile_prototype_repository(&tile_prototype_repository);
}

void game_tick(
    float delta)
{
    (void)delta;

    game_tick_actors(world, player_actor);
}

void game_draw(void)
{
    BeginDrawing();
    ClearBackground(WHITE);
    DrawFPS(8, 8);

    game_draw_tile_map(world, TILE_WIDTH, TILE_HEIGHT);
    game_draw_actors(world, TILE_WIDTH, TILE_HEIGHT);

    EndDrawing();
}

// ---------------------------------------------------------------------------
// Static Functions
// ---------------------------------------------------------------------------

static void game_init_tile_prototype_repository(
    TilePrototypeRepository *repository)
{
    *repository = tile_prototype_repository_create();

    // empty tile prototype
    {
        const TileFlags flags = TILE_FLAG_NONE;
        const TileColour colour = tile_colour_create(0, 0, 0, 255);
        const TilePrototype prototype = tile_prototype_create(flags, colour);

        tile_prototype_repository_add(repository, 0, "empty", prototype);
    }

    // floor tile prototype
    {
        const TileFlags flags = TILE_FLAG_WALKABLE;
        const TileColour colour = tile_colour_create(255, 0, 0, 255);
        const TilePrototype prototype = tile_prototype_create(flags, colour);

        tile_prototype_repository_add(repository, 1, "floor", prototype);
    }

    // wall tile prototype
    {
        const TileFlags flags = TILE_FLAG_SOLID;
        const TileColour colour = tile_colour_create(0, 255, 0, 255);
        const TilePrototype prototype = tile_prototype_create(flags, colour);

        tile_prototype_repository_add(repository, 2, "wall", prototype);
    }
}

static void game_free_tile_prototype_repository(
    TilePrototypeRepository *repository)
{
    tile_prototype_repository_free(repository);
}

static void game_tick_actors(
    World *world,
    Actor *player_actor)
{
    if (IsKeyPressed(KEY_KP_1) || IsKeyPressed(KEY_KP_2) ||
        IsKeyPressed(KEY_KP_3) || IsKeyPressed(KEY_KP_4) ||
        IsKeyPressed(KEY_KP_6) || IsKeyPressed(KEY_KP_7) ||
        IsKeyPressed(KEY_KP_8) || IsKeyPressed(KEY_KP_9))
    {
        int dx = 0;
        int dy = 0;

        if (IsKeyPressed(KEY_KP_7) ||
            IsKeyPressed(KEY_KP_4) ||
            IsKeyPressed(KEY_KP_1))
        {
            --dx;
        }

        if (IsKeyPressed(KEY_KP_9) ||
            IsKeyPressed(KEY_KP_6) ||
            IsKeyPressed(KEY_KP_3))
        {
            ++dx;
        }

        if (IsKeyPressed(KEY_KP_7) ||
            IsKeyPressed(KEY_KP_8) ||
            IsKeyPressed(KEY_KP_9))
        {
            --dy;
        }

        if (IsKeyPressed(KEY_KP_1) ||
            IsKeyPressed(KEY_KP_2) ||
            IsKeyPressed(KEY_KP_3))
        {
            ++dy;
        }

        if (dx || dy)
        {
            world_move_actor(world, player_actor, dx, dy);
        }
    }
}

static void game_draw_tile_map(
    World *world,
    size_t tile_width,
    size_t tile_height)
{
    for (int y = 0; y < world->tile_map->height; ++y)
    {
        const int pos_y = y * tile_height;
        for (int x = 0; x < world->tile_map->width; ++x)
        {
            const Tile *tile = world_get_tile(world, x, y);
            const TileColour colour = tile->colour;

            if (!tile)
                continue;

            const int pos_x = x * tile_width;
            const Color color = {colour.r, colour.g, colour.b, colour.a};

            DrawRectangle(pos_x, pos_y, tile_width, tile_height, color);
        }
    }
}

static void game_draw_actors(
    const World *world,
    size_t tile_width,
    size_t tile_height)
{
    for (size_t i = 0; i < world->actors->count; ++i)
    {
        const Actor *actor = world->actors->data[i];
        const ActorColour colour = actor_get_colour(actor);

        const int pos_x = actor_get_x(actor) * tile_width;
        const int pos_y = actor_get_y(actor) * tile_height;
        const int width = tile_width;
        const int height = tile_height;
        const Color color = {colour.r, colour.g, colour.b, colour.a};

        DrawRectangle(pos_x, pos_y, width, height, color);
    }
}

static Tile game_create_tile_from_prototype(
    TilePrototype prototype)
{
    const Tile tile = tile_create(prototype.flags, prototype.colour);
    return tile;
}

static Tile game_create_tile_from_id(
    const TilePrototypeRepository *repository,
    size_t id)
{
    const TilePrototype prototype = *tile_prototype_repository_get_by_id(
        repository,
        id);
    const Tile tile = game_create_tile_from_prototype(prototype);
    return tile;
}

static Tile game_create_tile_from_name(
    const TilePrototypeRepository *repository,
    const char *name)
{
    const TilePrototype prototype = *tile_prototype_repository_get_by_name(
        repository,
        name);
    const Tile tile = game_create_tile_from_prototype(prototype);
    return tile;
}
