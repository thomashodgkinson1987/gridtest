#include "game.h"

#include <stdlib.h>

#include "raylib.h"

#include "actor.h"
#include "colour.h"
#include "command.h"
#include "command_system.h"
#include "command_result.h"
#include "log.h"
#include "renderer.h"
#include "world.h"

// The concrete definition of the game struct.
struct game
{
    // --- Core Subsystems ---
    Renderer *renderer;
    World *world;
    CommandSystem *command_system;

    // --- Game State ---
    bool is_running;
    bool is_player_turn_complete;

    // --- Player Reference ---
    Actor *player;
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
    game_instance = malloc(sizeof(*game_instance));
    if (!game_instance)
    {
        log_perror("Game instance allocation failure");
        log_fatal(
            "%s: Fatal error due to game instance allocation failure",
            __func__);
    }

    game_instance->renderer = renderer_create(512, 512, "gridtest");
    game_instance->world = world_create(16, 16);
    game_instance->command_system = command_system_create();
    game_instance->is_running = true;
    game_instance->is_player_turn_complete = false;

    // Create a simple map layout
    create_map(game_instance->world);

    // Create the player
    Colour player_colour = {255, 255, 255, 255};
    game_instance->player = actor_create(4, 4, '@', player_colour, "Player");
    actor_add_health_component(game_instance->player, 100);
    actor_add_combat_component(game_instance->player, 10);
    world_add_actor(game_instance->world, game_instance->player);

    // Create a monster
    Colour monster_colour = {0, 255, 0, 255};
    Actor *monster = actor_create(6, 4, 'g', monster_colour, "Goblin");
    actor_add_health_component(monster, 20);
    actor_add_combat_component(monster, 5);
    actor_add_ai_component(monster);
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
    command_system_free(game_instance->command_system);
    world_free(game_instance->world);
    renderer_free(game_instance->renderer);
    free(game_instance);
}

void game_add_command(Game *game, Command command)
{
    command_system_add_command(game->command_system, command);
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
        Actor *target_actor = world_get_actor_at_mut(
            game_instance->world,
            target_x,
            target_y);

        if (target_actor)
        {
            Command command = world_actor_attack_actor(
                game_instance->world,
                game_instance->player,
                target_actor);

            if (command.type != COMMAND_TYPE_NULL)
            {
                game_add_command(game_instance, command);
            }
        }
        else if (
            world_is_tile_walkable(game_instance->world, target_x, target_y))
        {
            Command command = command_actor_set_position_create(
                game_instance->player,
                target_x,
                target_y);
            game_add_command(game_instance, command);
        }

        game_instance->is_player_turn_complete = true;
    }
}

static void update(void)
{
    // has player took their turn?
    if (game_instance->is_player_turn_complete)
    {
        // Process all commands in the queue
        command_system_process_queue(
            game_instance->command_system,
            game_instance->renderer,
            game_instance->world);

        world_update_actors(game_instance->world);
        game_instance->is_player_turn_complete = false;
    }
}

static void render(void)
{
    renderer_begin_frame(game_instance->renderer, game_instance->world);
    renderer_end_frame(game_instance->renderer);
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
            Tile *tile = world_get_tile_at_mut(world, x, y);
            if (tile)
            {
                tile->type = TILE_TYPE_FLOOR;
            }
        }
    }
}
