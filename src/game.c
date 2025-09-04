#include "game.h"

#include <stdlib.h>

#include "raylib.h"

#include "actor.h"
#include "colour.h"
#include "command.h"
#include "command_system.h"
#include "game_state.h"
#include "input_system.h"
#include "log.h"
#include "process_result.h"
#include "renderer.h"
#include "world.h"

// --- Internal Module Definition ---
struct game
{
    Renderer *renderer;
    World *world;
    CommandSystem *command_system;
    InputSystem *input_system;
    GameState current_state;
    Actor *player;
};

// --- Static Function Prototypes ---
static void handle_input(Game *game);
static void update(Game *game);
static void render(Game *game);
static void create_map(World *world);

// --- Public Function Definitions ---
Game *game_create(
    Renderer *renderer,
    World *world,
    CommandSystem *command_system,
    InputSystem *input_system)
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
    game->input_system = input_system;
    game->current_state = GAME_STATE_WAITING_FOR_INPUT;
    game->player = NULL;

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
    while (game->current_state != GAME_STATE_QUIT)
    {
        switch (game->current_state)
        {
        case GAME_STATE_WAITING_FOR_INPUT:
        {
            handle_input(game);
            break;
        }
        case GAME_STATE_PLAYER_TURN:
        {
            ProcessResult result = command_system_process_queue(
                game->command_system,
                game->renderer,
                game->world);
            game->current_state = GAME_STATE_ENEMY_TURN;
            if (result.did_quit)
                game->current_state = GAME_STATE_QUIT;
            break;
        }
        case GAME_STATE_ENEMY_TURN:
        {
            world_update_actors(game->world);
            game->current_state = GAME_STATE_WAITING_FOR_INPUT;
            break;
        }
        default:
        {
            log_message(LOG_LEVEL_FATAL, "%s: Unknown game state", __func__);
            break;
        }
        }

        render(game);
    }
}
void game_free(Game *game)
{
    input_system_free(game->input_system);
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

// --- Static Function Definitions ---
static void handle_input(Game *game)
{
    input_system_poll_input(game->input_system);

    while (input_system_has_event(game->input_system))
    {
        InputEvent event = input_system_next_event(game->input_system);

        switch (event.type)
        {
        case INPUT_EVENT_TYPE_QUIT:
        {
            log_message(LOG_LEVEL_INFO, "Input Event: QUIT");
            const Command command = command_game_quit_create();
            game_add_command(game, &command);
            game->current_state = GAME_STATE_PLAYER_TURN;
            break;
        }
        case INPUT_EVENT_TYPE_ACTOR_MOVE_NORTH:
            log_message(LOG_LEVEL_INFO, "Input Event: MOVE NORTH");
            break;
        case INPUT_EVENT_TYPE_ACTOR_MOVE_SOUTH:
            log_message(LOG_LEVEL_INFO, "Input Event: MOVE SOUTH");
            break;
        case INPUT_EVENT_TYPE_ACTOR_MOVE_EAST:
            log_message(LOG_LEVEL_INFO, "Input Event: MOVE EAST");
            break;
        case INPUT_EVENT_TYPE_ACTOR_MOVE_WEST:
            log_message(LOG_LEVEL_INFO, "Input Event: MOVE WEST");
            break;
        case INPUT_EVENT_TYPE_ACTOR_WAIT:
            log_message(LOG_LEVEL_INFO, "Input Event: WAIT");
            game->current_state = GAME_STATE_PLAYER_TURN;
            break;
        default:
            log_message(
                LOG_LEVEL_FATAL,
                "%s: Invalid input event type [%i]",
                __func__,
                event.type);
            break;
        }

        bool is_direction =
            event.type == INPUT_EVENT_TYPE_ACTOR_MOVE_NORTH ||
            event.type == INPUT_EVENT_TYPE_ACTOR_MOVE_SOUTH ||
            event.type == INPUT_EVENT_TYPE_ACTOR_MOVE_EAST ||
            event.type == INPUT_EVENT_TYPE_ACTOR_MOVE_WEST;

        if (is_direction)
        {
            int dx = 0;
            int dy = 0;

            if (event.type == INPUT_EVENT_TYPE_ACTOR_MOVE_NORTH)
                dy = -1;
            else if (event.type == INPUT_EVENT_TYPE_ACTOR_MOVE_SOUTH)
                dy = +1;
            else if (event.type == INPUT_EVENT_TYPE_ACTOR_MOVE_EAST)
                dx = 1;
            else if (event.type == INPUT_EVENT_TYPE_ACTOR_MOVE_WEST)
                dx = -1;

            const int target_x = actor_get_x(game->player) + dx;
            const int target_y = actor_get_y(game->player) + dy;

            Actor *target = world_get_actor_at_mut(
                game->world,
                target_x,
                target_y);

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

            game->current_state = GAME_STATE_PLAYER_TURN;
        }
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
