# Development Plan

This file outlines the next steps for the project, focusing on refactoring core utilities, professionalizing the project structure, and preparing for advanced gameplay logic.

## Checklist

1.  **Learning Objective: Understand Variadic Arguments (`va_args`)**
    -   **Topic:** Start with a focused discussion on `va_list`, `va_start`, `va_arg`, and `va_end` to understand how to create functions that accept a variable number of arguments.

2.  **Create the Logging System**
    -   **Branch:** `feature/logging-system`
    -   **Action:** Create `log.h` and `log.c`.
    -   **Action:** Implement a variadic `log_message(LogLevel level, const char *format, ...)` function.
    -   **Action:** Create a `log_perror(const char *msg)` helper for system errors.
    -   **Action:** Refactor the entire codebase to use these new, clean logging functions.
    -   **Git:** Commit, merge to `develop`, and clean up the branch.

3.  **Remove Obsolete `NameComponent`**
    -   **Branch:** `chore/remove-name-component`
    -   **Action:** Delete the unused `NameComponent` struct and its associated functions from `components.h`/`.c`.
    -   **Git:** Commit, merge, and clean up.

4.  **Refactor `game` and `renderer` Structs**
    -   **Branch:** `refactor/struct-organization`
    -   **Action:** Review and reorder the fields in the main `game` and `renderer` structs for clarity and consistency.
    -   **Git:** Commit, merge, and clean up.

5.  **Create the Command Processing System**
    -   **Branch:** `feature/command-processing-system`
    -   **Action:** Create new `command_processing_system.h`/`.c` files.
    -   **Action:** Move the `CommandResult` `switch` statement from `game.c` into the new system to improve separation of concerns.
    -   **Git:** Commit, merge, and clean up.

6.  **Future Task: Error Handling in `array_macros`**
    -   **Topic:** Revisit the `array_macros` library to design a robust error handling strategy (e.g., returning error codes) that avoids direct logging, keeping the library decoupled.
