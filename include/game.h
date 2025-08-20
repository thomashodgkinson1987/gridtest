#ifndef GAME_H
#define GAME_H

// Opaque pointer type for the Game.
typedef struct game Game;

// Manages the overall application state and main loop.
void game_init(void);
void game_run(void);
void game_shutdown(void);

#endif // GAME_H
