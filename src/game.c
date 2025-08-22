#include "game.h"

#include "raylib.h"
#include "world.h"
#include "actor.h"
#include "components.h"
#include "colour.h"
#include "renderer.h"

#include <stdlib.h>
#include <stdio.h>

// The concrete definition of the game struct.
struct game
{
    World *world;
    Actor *player;
    bool is_running;
    bool player_took_turn;
    bool is_draw_dirty;
};

// A single static instance of the game state. This is a simple way to manage
// the global state of the game without passing the Game pointer everywhere.
static struct game *game_instance = NULL;

// --- Static Function Prototypes ---

static void handle_input(void);
static void update(void);
static void render(void);
static void create_map(World *world);

// --- Public Function Implementations ---

void game_init(void)
{
    renderer_init(512, 512, "gridtest");

    game_instance = malloc(sizeof(*game_instance));
    if (!game_instance)
    {
        char error_msg[100];
        snprintf(
            error_msg,
            sizeof(error_msg),
            "%s: Failed to allocate memory for game",
            __func__);
        perror(error_msg);
        exit(EXIT_FAILURE);
    }

    game_instance->world = world_create(16, 16);
    game_instance->is_running = true;
    game_instance->player_took_turn = false;
    game_instance->is_draw_dirty = true;

    // Create a simple map layout
    create_map(game_instance->world);

    // Create the player
    Colour player_colour = {255, 255, 255, 255};
    game_instance->player = actor_create(4, 4, '@', player_colour);
    actor_add_health_component(
        game_instance->player,
        health_component_create(100));
    actor_add_combat_component(
        game_instance->player,
        combat_component_create(10));
    world_add_actor(game_instance->world, game_instance->player);

    // Create a monster
    Colour monster_colour = {0, 255, 0, 255};
    Actor *monster = actor_create(6, 4, 'g', monster_colour);
    actor_add_health_component(monster, health_component_create(20));
    actor_add_combat_component(monster, combat_component_create(5));
    actor_add_ai_component(monster, ai_component_create());
    world_add_actor(game_instance->world, monster);
}

void game_run(void)
{
    while (game_instance->is_running)
    {
        if (renderer_should_close())
        {
            game_instance->is_running = false;
            continue;
        }

        handle_input();
        update();
        render();
    }
}

void game_shutdown(void)
{
    world_free(game_instance->world);
    free(game_instance);
    renderer_shutdown();
}

// --- Static Function Implementations ---

static void handle_input(void)
{
    int dx = 0;
    int dy = 0;

    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_KP_8))
        dy = -1;
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_KP_2))
        dy = 1;
    if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_KP_4))
        dx = -1;
    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_KP_6))
        dx = 1;
    if (IsKeyPressed(KEY_KP_7))
    {
        dx = -1;
        dy = -1;
    }
    if (IsKeyPressed(KEY_KP_9))
    {
        dx = 1;
        dy = -1;
    }
    if (IsKeyPressed(KEY_KP_1))
    {
        dx = -1;
        dy = 1;
    }
    if (IsKeyPressed(KEY_KP_3))
    {
        dx = 1;
        dy = 1;
    }

    if (dx != 0 || dy != 0)
    {
        int player_x, player_y;
        actor_get_position(game_instance->player, &player_x, &player_y);

        int target_x = player_x + dx;
        int target_y = player_y + dy;

        // Check for actors at the target location
        Actor *target_actor = world_get_mutable_actor_at(
            game_instance->world,
            target_x,
            target_y);
        if (target_actor)
        {
            world_actor_attack_actor(
                game_instance->world,
                game_instance->player,
                target_actor);
        }
        else if (
            world_is_tile_walkable(game_instance->world, target_x, target_y))
        {
            actor_set_position(game_instance->player, target_x, target_y);
        }

        game_instance->player_took_turn = true;
        renderer_set_dirty();
    }
}

static void update(void)
{
    if (game_instance->player_took_turn)
    {
        world_update_actors(game_instance->world);
        game_instance->player_took_turn = false;
    }
}

static void render(void)
{
    renderer_begin_frame(game_instance->world);

    // world_render(game_instance->world);

    renderer_end_frame();
}

// A simple helper function to carve out a rectangular room.
static void create_map(World *world)
{
    int room_x = 1;
    int room_y = 1;
    int room_w = world_get_width(world) - 2;
    int room_h = world_get_height(world) - 2;

    for (int y = room_y; y < room_y + room_h; ++y)
    {
        for (int x = room_x; x < room_x + room_w; ++x)
        {
            Tile *tile = world_get_mutable_tile_at(world, x, y);
            if (tile)
            {
                tile->type = TILE_TYPE_FLOOR;
            }
        }
    }
}
