#include "game.h"

#include "command_system.h"
#include "input_system.h"
#include "renderer.h"
#include "world.h"

int main(void)
{
    Renderer *renderer = renderer_create(512, 512, "gridtest");
    World *world = world_create(16, 16);
    CommandSystem *command_system = command_system_create();
    InputSystem *input_system = input_system_create();

    Game *game = game_create(renderer, world, command_system, input_system);
    game_init(game);
    game_run(game);
    game_free(game);

    return 0;
}
