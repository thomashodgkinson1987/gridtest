#include "game.h"

#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"

#include "actor.h"
#include "colour.h"
#include "command.h"
#include "command_array.h"
#include "command_result.h"
#include "components.h"
#include "renderer.h"
#include "world.h"

// The concrete definition of the game struct.
struct game
{
    World *world;
    Actor *player;
    Renderer *renderer;
    bool is_running;
    bool player_took_turn;
    CommandArray command_array;
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
        char error_msg[100];
        snprintf(
            error_msg,
            sizeof(error_msg),
            "%s: Failed to allocate memory for game",
            __func__);
        perror(error_msg);
        exit(EXIT_FAILURE);
    }

    game_instance->renderer = renderer_create(512, 512, "gridtest");
    game_instance->world = world_create(16, 16);
    game_instance->is_running = true;
    game_instance->player_took_turn = false;

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

    // Init command array
    game_instance->command_array = command_array_create(1);
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
    for (
        size_t i = 0;
        i < command_array_get_count(&game_instance->command_array);
        ++i)
    {
        Command command = command_array_get(&game_instance->command_array, i);
        command_free(&command);
    }
    command_array_free(&game_instance->command_array);
    world_free(game_instance->world);
    free(game_instance);
    renderer_free(game_instance->renderer);
}

void game_add_command(Game *game, Command command)
{
    command_array_push(&game->command_array, command);
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

        game_instance->player_took_turn = true;
    }
}

static void update(void)
{
    if (game_instance->player_took_turn)
    {
        bool is_set_renderer_dirty = false;

        for (
            size_t i = 0;
            i < command_array_get_count(&game_instance->command_array);
            ++i)
        {
            Command command =
                command_array_get(&game_instance->command_array, i);
            CommandResult result = command_execute(&command);

            switch (result.type)
            {

            case COMMAND_RESULT_TYPE_ACTOR_SET_X:
            {
                CommandResultParamsActorSetX *params =
                    &result.params.actor_set_x;
                const int old_x = params->old_x;
                const int new_x = params->new_x;
                if (old_x != new_x)
                {
                    is_set_renderer_dirty = true;
                }
                break;
            }

            case COMMAND_RESULT_TYPE_ACTOR_SET_Y:
            {
                CommandResultParamsActorSetY *params =
                    &result.params.actor_set_y;
                const int old_y = params->old_y;
                const int new_y = params->new_y;
                if (old_y != new_y)
                {
                    is_set_renderer_dirty = true;
                }
                break;
            }

            case COMMAND_RESULT_TYPE_ACTOR_SET_POSITION:
            {
                CommandResultParamsActorSetPosition *params =
                    &result.params.actor_set_position;
                const int old_x = params->old_x;
                const int old_y = params->old_y;
                const int new_x = params->new_x;
                const int new_y = params->new_y;
                if (old_x != new_x || old_y != new_y)
                {
                    is_set_renderer_dirty = true;
                }
                break;
            }

            case COMMAND_RESULT_TYPE_ACTOR_SET_GLYPH:
            {
                CommandResultParamsActorSetGlyph *params =
                    &result.params.actor_set_glyph;
                const char old_glyph = params->old_glyph;
                const char new_glyph = params->new_glyph;
                if (old_glyph != new_glyph)
                {
                    is_set_renderer_dirty = true;
                }
                break;
            }

            case COMMAND_RESULT_TYPE_ACTOR_SET_COLOUR:
            {
                CommandResultParamsActorSetColour *params =
                    &result.params.actor_set_colour;
                const Colour old_colour = params->old_colour;
                const Colour new_colour = params->new_colour;
                if (old_colour.r != new_colour.r ||
                    old_colour.g != new_colour.g ||
                    old_colour.b != new_colour.b ||
                    old_colour.a != new_colour.a)
                {
                    is_set_renderer_dirty = true;
                }
                break;
            }

            case COMMAND_RESULT_TYPE_ACTOR_SET_R:
            {
                CommandResultParamsActorSetR *params =
                    &result.params.actor_set_r;
                const unsigned char old_r = params->old_r;
                const unsigned char new_r = params->new_r;
                if (old_r != new_r)
                {
                    is_set_renderer_dirty = true;
                }
                break;
            }

            case COMMAND_RESULT_TYPE_ACTOR_SET_G:
            {
                CommandResultParamsActorSetG *params =
                    &result.params.actor_set_g;
                const unsigned char old_g = params->old_g;
                const unsigned char new_g = params->new_g;
                if (old_g != new_g)
                {
                    is_set_renderer_dirty = true;
                }
                break;
            }

            case COMMAND_RESULT_TYPE_ACTOR_SET_B:
            {
                CommandResultParamsActorSetB *params =
                    &result.params.actor_set_b;
                const unsigned char old_b = params->old_b;
                const unsigned char new_b = params->new_b;
                if (old_b != new_b)
                {
                    is_set_renderer_dirty = true;
                }
                break;
            }

            case COMMAND_RESULT_TYPE_ACTOR_SET_A:
            {
                CommandResultParamsActorSetA *params =
                    &result.params.actor_set_a;
                const unsigned char old_a = params->old_a;
                const unsigned char new_a = params->new_a;
                if (old_a != new_a)
                {
                    is_set_renderer_dirty = true;
                }
                break;
            }

            case COMMAND_RESULT_TYPE_ACTOR_TOOK_DAMAGE:
            {
                CommandResultParamsActorTookDamage *params =
                    &result.params.actor_took_damage;
                Actor *actor = params->actor;
                const int amount = params->amount;
                const bool did_die = params->did_die;
                printf("%s took %i damage\n", actor_get_name(actor), amount);
                if (did_die)
                {
                    printf("%s died\n", actor_get_name(actor));
                    world_remove_actor(game_instance->world, actor);
                    is_set_renderer_dirty = true;
                }
                break;
            }

            default:
            {
                break;
            }
            }

            command_result_free(&result);
            command_free(&command);
        }

        command_array_clear(&game_instance->command_array);

        world_update_actors(game_instance->world);
        game_instance->player_took_turn = false;

        if (is_set_renderer_dirty)
        {
            renderer_set_dirty(game_instance->renderer);
        }
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
