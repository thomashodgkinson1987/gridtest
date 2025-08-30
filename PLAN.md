# Development Plan

This file tracks our development progress using a Kanban-style workflow.

# Development Plan

This file tracks our development progress using a Kanban-style workflow.

## 1. Current Task

*empty*

---

## 2. Backlog

### Chore: Split `PLAN.md` into Multiple Files
-   **Goal:** Split the main `PLAN.md` file into separate files for each Kanban section (`Current`, `Backlog`, `Completed`) to improve token efficiency.
-   **Type:** `chore`
-   **Priority:** High
-   **Branch:** `chore/split-kanban-board`
-   **Action 1:** Create `KANBAN_CURRENT.md`, `KANBAN_BACKLOG.md`, and `KANBAN_COMPLETED.md`.
-   **Action 2:** Migrate the content from the corresponding sections of `PLAN.md` into the new files.
-   **Action 3:** Update `PLAN.md` to act as a master file that explains the new structure.
-   **Action 4:** Update workflow documents (`PROJECT-OVERVIEW.md`, `BOOTSTRAP-GUIDE.md`) to reflect the new multi-file Kanban system.

### Lesson: Implement a Hash Map in C
-   **Goal:** Learn about and discuss the implementation of hash maps in C.
-   **Type:** `lesson`
-   **Priority:** High
-   **Branch:** none
-   **Action 1 (Research):** Independently research the theory and common implementation patterns of hash maps in C (hash functions, collision resolution, etc.).
-   **Action 2 (Discussion):** Hold a discussion session to review findings, clarify concepts, and sketch out a potential C implementation for future use in the project.

### Refactor: Add `const`-correctness to `array_macros`
-   **Goal:** Refactor the `array_macros` submodule to be fully `const`-correct, allowing for safer, read-only access to array data.
-   **Type:** `refactor`
-   **Priority:** Low
-   **Branch:** `refactor/array-macros-const-correctness`
-   **Action 1:** Add `const`-correct variants for getter functions in `array_macros.h` (e.g., a version of `array_get` that accepts a `const array*`).
-   **Action 2:** Update the `gridtest` codebase to use the new `const`-correct functions where appropriate, resolving the current technical debt in `actor.c`.

### Refactor: Apply `iter_` Naming Convention
-   **Goal:** Refactor the codebase to consistently use the `iter_` prefix for loop variables where there is a name collision with a result variable.
-   **Type:** `refactor`
-   **Priority:** Medium
-   **Branch:** `refactor/apply-iter-convention`
-   **Action 1:** Search the codebase for instances of name collisions between loop variables and result variables.
-   **Action 2:** Rename the loop variables to use the `iter_` prefix (e.g., `iter_component`) to resolve ambiguity and improve clarity.

### Refactor: Standardize Enum Naming to use `_NONE`
-   **Goal:** Refactor all enums to use `_NONE` as the zero-value member instead of `_NULL` for better semantic clarity.
-   **Type:** `refactor`
-   **Priority:** Medium
-   **Branch:** `refactor/standardize-enum-naming`
-   **Action 1:** Find all enums that use a `_NULL` suffix for their default/zero member (e.g., `CommandType`, `ComponentType`).
-   **Action 2:** Rename the member to use the `_NONE` suffix.
-   **Action 3:** Update all call sites throughout the codebase that reference the old `_NULL` member name.

### Refactor: Add Error Handling to `array_macros`
-   **Goal:** Improve the `array_macros` library by adding a robust error handling strategy that avoids direct logging.
-   **Type:** `refactor`
-   **Priority:** Low
-   **Branch:** `refactor/array-macros-error-handling`
-   **Action 1:** Design an error handling strategy (e.g., returning error codes, using a global error state) that keeps the library decoupled from any specific logging implementation.
-   **Action 2:** Implement the chosen strategy, updating macros that can fail (e.g., `array_push` on a full array) to report errors.

---

## 3. Completed Tasks (Most Recent At The Top)

### Refactor: Overhaul Component System
-   **Goal:** Refactor the component system to be a generic, type-safe, and extensible system, mirroring the design of the Command system.
-   **Type:** `refactor`
-   **Priority:** High
-   **Branch:** `refactor/overhaul-component-system`
-   **Action 1 (File Renaming):** Rename `components.h/.c` to `component.h/.c` and update `CMakeLists.txt`.
-   **Action 2 (Define Generic Component):** In `component.h`, define `ComponentType` enum, `ComponentParams*` structs, and a main `Component` struct with a `union`.
-   **Action 3 (Implement New API):** In `component.c`, implement `component_*_create`, a unified `component_free`, and `component_get_name_from_type`.
-   **Action 4 (Overhaul Actor Internals):** In `actor.c`, replace named component pointers with a dynamic array of `Component*`. Update `actor_create` and `actor_free` to manage this array.
-   **Action 5 (Overhaul Actor API):** In `actor.h/.c`, replace all old component functions with new generic ones: `actor_add_component`, `actor_get_component`, `actor_get_component_mut`, and `actor_remove_component`.
-   **Action 6 (Update Codebase):** Sweep the project to replace all calls to the old component API with the new one.

### Refactor: Standardize Command Object Logging
-   **Goal:** All Command logging calls will use a lookup table to retrieve the object's name.
-   **Type:** `refactor`
-   **Priority:** Low
-   **Branch:** `refactor/standardized-command-logging`
-   **Action 1 (Implement Naming Function):** In `command.h/.c`, create `const char* command_get_name_from_type(CommandType type);`. The function will be implemented with a private, static lookup table and will return a safe default string on error.
-   **Action 2 (Refactor Logging Calls):** Search the codebase and replace any manual logging of command names with calls to the new helper function.

---

## 3. Completed Tasks (Most Recent At The Top)

### Reorder `#include`s In Game Module
-   **Goal:** To have `game.c/.h` include directives to be alphabetically ordererd.
-   **Type:** refactor
-   **Priority:** Low
-   **Branch:** refactor/reorder-game-module-includes
-   **Action 1:** Reorder Game module `#include`s.

### Remove Redundant Null Checks
-   **Goal:** Align the codebase with the project convention of not performing a null check before calling free.
-   **Type:** refactor
-   **Priority:** Low
-   **Branch:** refactor/remove-redundant-null-checks
-   **Action 1:** Search the project for any instances of `if (ptr) { free(ptr); }`.
-   **Action 2:** Replace all instances with a direct `free(ptr)` call.

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
