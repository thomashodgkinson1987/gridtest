<overview>
# Project Overview: GridTest

## High-Level Summary

-   **Project:** GridTest, a rogikuelike prototype written in C.
-   **Developer:** Thomas Hodgkinson (Tom)
-   **Email:** thomashodgkinson1987@gmail.com
-   **Core Philosophy:** "Productive Laziness" - building a clean, maintainable, and well-documented project now to save time and effort later.

## Session Workflow

Our collaboration follows a structured lifecycle for each development session, ensuring a clean start and a clear end.

### Bootstrap Sequence
At the beginning of each session, a bootstrap sequence is performed to bring me up to speed on the current state of the project. This involves reading all core metadata files and analyzing the live Git state. The full, detailed steps for this process are documented in `BOOTSTRAP-GUIDE.md`.

### Shutdown Sequence
At the end of each session, a shutdown sequence is performed to ensure the project is left in a clean, predictable state. This involves:
1.  **State Analysis:** I will check the Git status, the current branch, the active task in `PLAN.md`, and any unresolved topics in `NOTES.md`.
2.  **Shutdown Report:** I will provide a concise summary of the project's state.
3.  **Final Actions:** Based on the report, we will take any necessary actions (e.g., committing final changes) to ensure a clean handoff for the next session.

## Development Modes

Our collaboration is structured around three distinct modes of operation to ensure flexibility and efficiency. We default to **Plan Mode** at the start of every session.

### 1. Plan Mode
-   **Purpose:** Discussion, brainstorming, research, and defining tasks. This is our "thinking" space.
-   **Rules:**
    -   No code or documentation is modified, except for `NOTES.md`.
    -   We can freely read any file and check the Git state (`git status`, `git log`).
    -   No branches are created, and no commits are made.

### 2. Admin Mode
-   **Purpose:** Managing the project and our process. This mode is for "meta-work" that should be committed directly to `develop`.
-   **Rules:**
    -   Used for tasks that don't require a feature branch (e.g., updating `PLAN.md` after a discussion, refining workflow documents).
    -   Commits are made directly on the `develop` branch, typically with `docs(...)` or `chore(...)` scopes.

### 3. Work Mode
-   **Purpose:** Focused implementation of a single, defined task from `PLAN.md`. This is our "coding" space.
-   **Rules:** This mode strictly follows our established Kanban-style Git workflow for implementing tasks.
    -   **Branching:** Always starts by creating a new feature branch (`git switch -c ...`) from `develop`.
    -   **Task Lifecycle in `PLAN.md`:**
        1.  **Initiate Task:** Select the highest-priority task from the `Upcoming Tasks` backlog.
        2.  **Set as Current:** The **first commit** on the new branch must be a `docs(plan)` commit that moves the task into the `Current Task` section.
        3.  **Execute:** Work through the task's action items, making atomic commits as needed.
        4.  **Complete Task:** The **final commit** on the branch must be another `docs(plan)` commit that moves the task to the `Completed Tasks` section.
    -   **Merging:** The feature branch is then merged back into `develop` (squashing if it contains multiple commits) to keep the history clean and atomic.

## Architecture

-   **Model:** A pragmatic, layered **Actor Model**. It is not a pure Entity-Component-System (ECS).
-   **Core Objects:** `Actor` structs are concrete objects with intrinsic properties (`x`, `y`, `glyph`, `colour`, `name`) and optional `Components` for extensible data (health, combat, AI).
-   **Game Loop:** The engine is built on a **Command/Result Pattern**.
    -   Gameplay logic generates "Commands" (atomic state changes).
    -   A central queue in the `game` module holds these commands.
    -   A `command_execute` function processes commands and returns a "Result" object.
    -   The main game loop inspects the `Result` to handle consequences (e.g., actor death, dirtying the renderer). This system is slated to be encapsulated within a dedicated `CommandSystem` module to improve separation of concerns.

## Project Conventions

-   **API Design:** Prefer passing explicit context (e.g., `Game*`, `Renderer*`) over using singletons. Strive for `const`-correctness with both `const` and `_mut` variants for getters where appropriate.
-   **Memory Management:** Ownership is clear and encapsulated. `_create` functions `malloc`, and corresponding `_free` functions `free`. The calling code does not manage memory for objects it receives.
-   **Formatting:** Adhere to an 80-column limit. Use include guards and a standard include order (primary header, system headers, library headers, project headers).
-   **File Naming:**
    -   C source and header files (`.c`, `.h`) use `snake_case` (e.g., `command_result.h`).
    -   Non-code metadata files use `dash-case` (e.g., `PROJECT-OVERVIEW.md`).

## Git & Repository

-   **URLs:**
    -   Main Project: `https://github.com/thomashodgkinson1987/gridtest.git`
    -   `array_macros` Submodule: `https://github.com/thomashodgkinson1987/array_macros.git`
-   **Branching:** All work is done on feature/fix/chore branches, branched from `develop`.
-   **Commits:** All commit messages must adhere to the **Conventional Commits** specification. We practice creating **atomic commits** where it adds clarity.
-   **Merging:**
    -   Branches are merged into `develop` using a **fast-forward merge (`--ff-only`)** when the branch contains a single commit.
    -   For feature branches with multiple commits, a **squash merge** is used to maintain a clean, atomic history on `develop`.
    -   `develop` is merged into `main` for releases using a **`--no-ff` merge**.
    -   A "back-merge" from `main` to `develop` is performed after releases to keep branches synchronized.

## Build & Run Workflow

This project uses a CMake configuration that simplifies the build and run process.

-   **Build:** To compile the project, press `F7` in VS Code, or run the following command in the terminal:
    ```bash
    cmake --build build-Debug
    ```
-   **Run (Recommended):** To build and run the application with the correct working directory, use the custom `run` target. This is the preferred method for command-line execution.
    ```bash
    cmake --build build-Debug --target run
    ```
-   **Debug:** To launch a debugging session (which correctly sets the working directory), press `F5` in VS Code.

## Directory Structure

The project is organized into the following key directories:

-   `/src/`: Contains all the core C source files (.c).
-   `/include/`: Contains all the public header files (.h) that make up the modules' APIs.
-   `/lib/`: Contains pre-compiled third-party libraries (e.g., Raylib).
-   `/vendor/`: Contains third-party source code managed as Git submodules (e.g., array_macros).
-   `/res/`: Contains game assets like fonts and images.
-   `/.vscode/`: Contains project-specific settings and launch configurations for VS Code.
-   `/build-*/`: Build output directories (generated by CMake, ignored by Git).
</overview>
