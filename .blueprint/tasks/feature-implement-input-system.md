# Task: Implement Input System

-   **Goal:** Create a dedicated `InputSystem` module to centralize input polling, abstract raw input into game-agnostic events, and decouple input handling from core game logic.
-   **Branch:** `feature/implement-input-system`

---

## Action Plan

1.  **Scaffold Module and Update Build System:**
    -   Create empty files: `input_event.h`, `input_system.h`, and `input_system.c`.
    -   Modify `CMakeLists.txt` to add `input_system.c` to the list of sources to be compiled. This ensures the VS Code environment is immediately aware of the new files.

2.  **Define Public Interface and Data Types:**
    -   In `input_event.h`, define the `InputEventType` enum (e.g., `INPUT_EVENT_MOVE_NORTH`, etc.).
    -   In `input_system.h`, declare the public API: an opaque `struct InputSystem;` and the core functions: `input_system_create`, `input_system_free`, `input_system_poll_input`, and `input_system_get_next_event`.

3.  **Implement `InputSystem` Internals:**
    -   In `input_system.c`, define the concrete `struct InputSystem`, which will contain a dynamic array to queue `InputEventType`s using `array_macros.h`.
    -   Implement `input_system_create` and `input_system_free`.

4.  **Implement Polling and Event Retrieval:**
    -   In `input_system.c`, implement `input_system_poll_input`. This function will clear the internal event queue, poll Raylib for key presses, translate them into `InputEventType`s, and push them into the queue.
    -   Implement `input_system_get_next_event` to pop and return the next event from the queue, or return `INPUT_EVENT_NONE` if the queue is empty.

5.  **Integrate `InputSystem` into `Game` Lifecycle:**
    -   In `game.h`, add an `InputSystem*` handle to the `struct game`.
    -   In `game.c`, update `game_create` and `game_free` to manage the lifecycle of the `InputSystem` instance.

6.  **Refactor `Game` Main Loop:**
    -   In `game.c`, remove the now-obsolete `static void handle_input(Game* game)`.
    -   Create a new `static void process_input(Game* game)`.
    -   In `game_run`, replace the old `handle_input` call with `input_system_poll_input(game->input_system);` followed by `process_input(game);`.
    -   Implement `process_input` to loop through all available events from `input_system_get_next_event` and generate the appropriate `Command`s (move, attack), setting `is_player_turn_complete` as needed.
    