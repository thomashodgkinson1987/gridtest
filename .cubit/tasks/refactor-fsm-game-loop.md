# Task: Refactor to a State-Driven Game Loop

-   **Goal:** Replace the current boolean-flag-based game loop with a more robust Finite State Machine (FSM) to manage the core game states.
-   **Type:** `refactor`
-   **Branch:** `refactor/fsm-game-loop`

---

### Guiding Principle

We will execute this refactor using a methodical, "outside-in" approach. Each phase is designed to be self-contained, allowing us to focus on one specific "hat" or role at a time without needing to hold the entire system state in memory.

---

### Phase 1: Laying the Foundation (The Data Modeler Hat)
*Your only focus is defining new data types in new files.*

- [ ] **Create `game_state.h`:** In `/include/`, create a new header file defining the `GameState` enum (`GAME_STATE_WAITING_FOR_INPUT`, `GAME_STATE_PLAYER_TURN`, `GAME_STATE_ENEMY_TURN`, `GAME_STATE_QUIT`).
- [ ] **Create `process_result.h`:** In `/include/`, create a new header file defining the `ProcessResult` struct, which will contain a single `bool did_quit;`.

---

### Phase 2: Upgrading a Subsystem (The API Designer Hat)
*Your only focus is updating the public contract of the `CommandSystem` module.*

- [ ] **Update `command_system.h`:** Add `#include "process_result.h"` and change the return type of `command_system_process_queue` from `void` to `ProcessResult`.
- [ ] **Update `command_system.c`:**
    - [ ] Update the function definition to match the new signature.
    - [ ] At the start of the function, declare and initialize a `ProcessResult` variable (`result.did_quit = false`).
    - [ ] At the end of the function, return the `result` variable.

---

### Phase 3: Rebuilding the Engine (The Game Loop Architect Hat)
*Your only focus is the high-level logic inside `game.c` and `game.h`.*

- [ ] **Refactor the `Game` Struct:**
    - [ ] In `game.h`, add `#include "game_state.h"`.
    - [ ] In the `struct game` definition, remove `bool is_running;` and `bool is_player_turn_complete;`.
    - [ ] Add `GameState current_state;` to the `struct game`.
    - [ ] In `game.c`, update `game_create()` to initialize `game->current_state = GAME_STATE_WAITING_FOR_INPUT;`.
- [ ] **Implement the FSM in `game_run()`:**
    - [ ] Change the main loop condition to `while (game->current_state != GAME_STATE_QUIT)`.
    - [ ] Implement a `switch (game->current_state)` with cases for `WAITING_FOR_INPUT`, `PLAYER_TURN`, and `ENEMY_TURN`.
    - [ ] Move the call to `handle_input(game);` into the `WAITING_FOR_INPUT` case.
    - [ ] Move the call to `command_system_process_queue(...)` into the `PLAYER_TURN` case. Capture the `ProcessResult` and check `result.did_quit` to transition to `GAME_STATE_QUIT` if needed.
    - [ ] Move the call to `world_update_actors(game->world);` into the `ENEMY_TURN` case.
    - [ ] Add the state transition logic (e.g., `PLAYER_TURN` -> `ENEMY_TURN`, `ENEMY_TURN` -> `WAITING_FOR_INPUT`).
- [ ] **Cleanup `game.c`:** Delete the now-redundant static `update()` function.

---

### Phase 4: Connecting the Wires (The Integration Hat)
*Your only focus is making the newly refactored parts communicate with each other.*

- [ ] **Implement the `GAME_QUIT` Command:**
    - [ ] In `command.h`: Add `COMMAND_TYPE_GAME_QUIT` to the `CommandType` enum.
    - [ ] In `command_result.h`: Add `COMMAND_RESULT_GAME_QUIT` to the `CommandResultType` enum.
    - [ ] In `command.c`:
        - [ ] Create the `command_game_quit_create()` factory function.
        - [ ] In `command_execute()`, add a case for `COMMAND_TYPE_GAME_QUIT` that returns a `CommandResult` of type `COMMAND_RESULT_GAME_QUIT`.
- [ ] **Connect `CommandSystem` to `ProcessResult`:**
    - [ ] In `command_system.c`, within the `command_system_process_queue` function, if the `CommandResult` from `command_execute` is `COMMAND_RESULT_GAME_QUIT`, set `result.did_quit = true;`.
- [ ] **Connect `handle_input` to the FSM:**
    - [ ] In `game.c`, inside `handle_input()`, after creating a player action command (move, attack, or quit), set `game->current_state = GAME_STATE_PLAYER_TURN;`.
    