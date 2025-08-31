#include "game.h"

#include <stdlib.h>

#include "raylib.h"

#include "actor.h"
#include "colour.h"
#include "command.h"
#include "command_system.h"
#include "log.h"
#include "renderer.h"
#include "world.h"

struct game
{
    Renderer *renderer;
    World *world;
    CommandSystem *command_system;

    bool is_running;
    bool is_player_turn_complete;

    Actor *player;
};

// --- Static Function Prototypes ---

static void handle_input(Game *game);
static void update(Game *game);
static void render(Game *game);
static void create_map(World *world);

// --- Public Function Implementations ---

Game *game_create(
    Renderer *renderer,
    World *world,
    CommandSystem *command_system)
{
    Game *game = malloc(sizeof(*game));
    if (!game)
    {
        log_perror("Game instance allocation failure");
        log_fatal("%s: Fatal error", __func__);
    }

    game->renderer = renderer;
    game->world = world;
    game->command_system = command_system;
    game->is_running = true;
    game->is_player_turn_complete = false;

    return game;
}

void game_init(Game *game)
{
    create_map(game->world);

    Colour player_colour = {255, 255, 255, 255};
    game->player = actor_create(4, 4, '@', player_colour, "Player");
    actor_add_component(game->player, component_health_create(100, 100));
    actor_add_component(game->player, component_combat_create(10));
    world_add_actor(game->world, game->player);

    Colour monster_colour = {0, 255, 0, 255};
    Actor *monster = actor_create(6, 4, 'g', monster_colour, "Goblin");
    actor_add_component(monster, component_health_create(10, 10));
    actor_add_component(monster, component_combat_create(5));
    actor_add_component(monster, component_ai_create());
    world_add_actor(game->world, monster);
}

void game_run(Game *game)
{
    while (game->is_running)
    {
        if (renderer_should_close())
        {
            game->is_running = false;
            continue;
        }

        handle_input(game);
        update(game);
        render(game);
    }
}

void game_free(Game *game)
{
    command_system_free(game->command_system);
    world_free(game->world);
    renderer_free(game->renderer);
    free(game);
}

bool game_add_command(Game *game, const Command *command)
{
    if (
        command->type != COMMAND_TYPE_NONE &&
        command->type != COMMAND_TYPE_COUNT)
    {
        command_system_add_command(game->command_system, command);
        return true;
    }

    return false;
}

// --- Static Function Implementations ---

static void handle_input(Game *game)
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
        const int player_x = actor_get_x(game->player);
        const int player_y = actor_get_y(game->player);

        const int target_x = player_x + dx;
        const int target_y = player_y + dy;

        Actor *target = world_get_actor_at_mut(game->world, target_x, target_y);

        if (target)
        {
            Command command = world_actor_attack_actor(
                game->world,
                game->player,
                target);
            game_add_command(game, &command);
        }
        else if (world_is_tile_walkable(game->world, target_x, target_y))
        {
            Command command = command_actor_set_position_create(
                game->player,
                target_x,
                target_y);
            game_add_command(game, &command);
        }

        game->is_player_turn_complete = true;
    }
}

static void update(Game *game)
{
    if (game->is_player_turn_complete)
    {
        command_system_process_queue(
            game->command_system,
            game->renderer,
            game->world);

        world_update_actors(game->world);
        game->is_player_turn_complete = false;
    }
}

static void render(Game *game)
{
    renderer_begin_frame(game->renderer, game->world);
    renderer_end_frame(game->renderer);
}

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
