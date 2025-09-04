#ifndef GAME_STATE_H
#define GAME_STATE_H

// --- Type Definitions ---
typedef enum game_state
{
    GAME_STATE_WAITING_FOR_INPUT,
    GAME_STATE_PLAYER_TURN,
    GAME_STATE_ENEMY_TURN,
    GAME_STATE_QUIT
} GameState;

#endif // GAME_STATE_H
