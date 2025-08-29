#ifndef GAME_H
#define GAME_H

// Forward declarations
typedef struct command Command;

// Opaque pointer type for the Game.
typedef struct game Game;

// Manages the overall application state and main loop.
void game_init(void);
void game_run(void);
void game_shutdown(void);

// Functions to manage command queue
void game_add_command(Game *game, const Command *command);

#endif // GAME_H
