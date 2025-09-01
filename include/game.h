#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

// --- Forward Declarations ---
typedef struct command Command;

typedef struct renderer Renderer;
typedef struct world World;
typedef struct command_system CommandSystem;

typedef struct game Game;

// --- Public Function Prototypes ---
Game *game_create(
    Renderer *renderer,
    World *world,
    CommandSystem *command_system);
void game_init(Game *game);
void game_run(Game *game);
void game_free(Game *game);

bool game_add_command(Game *game, const Command *command);

#endif // GAME_H
