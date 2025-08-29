# Development Plan

This file tracks our development progress using a Kanban-style workflow.

## 1. Current Task

*empty*

---

## 2. Backlog

### Remove Redundant Null Checks
-   **Goal:** Align the codebase with the project convention of not performing a null check before calling free.
-   **Type:** refactor
-   **Priority:** Low
-   **Branch:** refactor/remove-redundant-null-checks
-   **Action 1:** Search the project for any instances of `if (ptr) { free(ptr); }`.
-   **Action 2:** Replace all instances with a direct `free(ptr)` call.

### Reorder `#include`s In Game Module
-   **Goal:** To have `game.c/.h` include directives to be alphabetically ordererd.
-   **Type:** refactor
-   **Priority:** Low
-   **Branch:** refactor/reorder-game-module-includes
-   **Action 1:** Reorder Game module `#include`s.

### Refactor: Standardize Core Object Logging
-   **Goal:** All Command and Component logging calls will use a .
-   **Type:** `refactor`
-   **Priority:** Low
-   **Branch:** `refactor/standardized-logging`
-   **Action 1 (Lookup Table):** Create a lookup table that contains the formatted name strings of commands and components (enum-to-char*).
-   **Action 2 (Implement):** Refactor logging calls throughout the codebase (e.g., in `game.c`, `command_system.c`) to use these lookup tables.
-   **Git:** Commit, merge, and clean up.

---

## 3. Completed Tasks (Most Recent At The Top)

### Change Command API to Use Pointers
-   **Goal:** Refactor the Command struct to be passed by const pointer to improve encapsulation and reduce header coupling.
-   **Type:** refactor
-   **Priority:** Medium
-   **Branch:** refactor/command-by-pointer
-   **Action 1:** Update `command_system.h` and `command_system.c` to accept `const Command*`.
-   **Action 2:** Update all call sites in `game.c` to pass the address of the Command struct.
-   **Action 3:** Replace `#include "command.h"` with a forward declaration in headers where possible.

### Amend Commit Type
-   **Goal:** Amend 98a20a0 to use the `chore` type for better adherence to Conventional Commits.
-   **Type:** chore
-   **Priority:** High
-   **Branch:** develop
-   **Action 1:** Run `git rebase -i HEAD~3 ` and complete changes.
-   **Action 2:** Push the change using `git push --force-with-lease`.

### Refactor: Centralize Command Logic into `CommandSystem`
-   **Goal:** Create a new core subsystem for the Game module that manages the command queue.
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

### Topic: Kanban Methodology Overview
-   **Goal:** Ensure we have a shared, solid understanding of the workflow system we've adopted.
-   **Type:** `lesson`
-   **Priority:** High
-   **Action (Chat):** Discuss the core principles of the Kanban methodology.

### Create the Command Processing System
-   **Goal:** Move responsibiility of CommandResult processing into dedicated command system.
-   **Type:** `feature`
-   **Priority:** Medium
-   **Branch:** `feature/command-processing-system`
-   **Action 1 (Files Creation):** Create new `command_processing_system.h`/`.c` files.
-   **Action 2 (Separate Conserns):** Move the `CommandResult` `switch` statement from `game.c` into the new system to improve separation of concerns.
-   **Action 3 (Git)** Commit, merge, and clean up.
