# Backlog

## Feature: Implement Input System
-   **Goal:** Decouple input handling from the game loop by creating a dedicated `InputSystem` that abstracts raw input into a queue of game-agnostic events.
-   **Type:** `feature`
-   **Priority:** High
-   **Branch:** `feature/implement-input-system`
-   **Details:** [Task Details](./tasks/feature-implement-input-system.md)

## Refactor: Apply `iter_` Naming Convention
-   **Goal:** Refactor the codebase to consistently use the `iter_` prefix for loop variables where there is a name collision with a result variable.
-   **Type:** `refactor`
-   **Priority:** Medium
-   **Branch:** `refactor/apply-iter-convention`

## Refactor: Add Error Handling to `array_macros`
-   **Goal:** Improve the `array_macros` library by adding a robust error handling strategy that avoids direct logging.
-   **Type:** `refactor`
-   **Priority:** Low
-   -**Branch:** `refactor/array-macros-error-handling`

## Refactor: Add `const`-correctness to `array_macros`
-   **Goal:** Refactor the `array_macros` submodule to be fully `const`-correct, allowing for safer, read-only access to array data.
-   **Type:** `refactor`
-   **Priority:** Low
-   **Branch:** `refactor/array-macros-const-correctness`
