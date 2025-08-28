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
-   **Action 1 (File Renaming):** Rename `command_processing_system.h` to `command_system.h` and `command_processing_system.c` to `command_system.c`.
-   **Action 2 (Build System):** Update `CMakeLists.txt` to reflect the file renames.
-   **Action 3 (API Refactoring):** Refactor all public function prefixes from `cps_*` to `command_system_*`.
-   **Action 4 (Opaque Struct):**
    -   In `command_system.h`, replace the existing content with a forward declaration for `struct CommandSystem;` and the new public function signatures that operate on a `CommandSystem*` handle.
    -   In `command_system.c`, define the `struct CommandSystem`, which will now encapsulate the `CommandQueue`.
-   **Action 5 (Game Integration):**
    -   Update the `Game` struct to hold a `CommandSystem*` handle.
    -   Remove the `CommandQueue` from the `Game` struct.
    -   Update `game_create` and `game_free` to manage the lifecycle of the `CommandSystem` instance.
-   **Action 6 (Delegation):** Refactor `game.c` to delegate all command operations (e.g., adding commands, processing the queue) to the new `command_system_*` functions.
-   **Action 7 (Git):** Commit, merge, and clean up.

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
