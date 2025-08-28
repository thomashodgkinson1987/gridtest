<plan>
# Development Plan

This file tracks our development progress using a Kanban-style workflow.

## 1. Current Task
*No active task. Ready to select from the backlog.*

---

## 2. Upcoming Tasks (Backlog)

### Refactor: Centralize Command Logic into `CommandSystem`
-   **Type:** `refactor`
-   **Priority:** Medium
-   **Branch:** `refactor/command-system`
-   **Action:** Rename `command_processing_system.h`/`.c` to `command_system.h`/`.c` and update `CMakeLists.txt`.
-   **Action:** Refactor all public function names from `cps_*` to the `cmdsys_*` prefix.
-   **Action:** Create an opaque `CommandSystem` struct and move the `CommandQueue` from the `Game` struct into it.
-   **Action:** Update the `Game` struct to hold a `CommandSystem*` handle instead of the queue.
-   **Action:** Refactor `game.c` to delegate all command operations (adding, processing) to the new `CommandSystem` module.
-   **Git:** Commit, merge, and clean up.

### Refactor: Standardize Core Object Logging
-   **Type:** `refactor`
-   **Priority:** Low
-   **Branch:** `refactor/standardized-logging`
-   **Action:** Create helper functions (e.g., `command_to_string`, `actor_to_string`) that produce consistent, formatted string representations of core game objects.
-   **Action:** Refactor logging calls throughout the codebase (e.g., in `game.c`, `cmdsys.c`) to use these new helper functions, improving consistency and reducing code duplication.
-   **Git:** Commit, merge, and clean up.

---

## 3. Completed Tasks
*Most recent at the top.*

-   **(Topic) Kanban Methodology Overview**
    -   **Type:** `docs`
    -   **Priority:** High
    -   **Action:** Discuss the core principles of the Kanban methodology.
    -   **Goal:** Ensure we have a shared, solid understanding of the workflow system we've adopted.

-   **Create the Command Processing System**
    -   **Branch:** `feature/command-processing-system`
    -   **Action:** Create new `command_processing_system.h`/`.c` files.
    -   **Action:** Move the `CommandResult` `switch` statement from `game.c` into the new system to improve separation of concerns.
    -   **Git:** Commit, merge, and clean up.
</plan>
