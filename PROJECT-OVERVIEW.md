# Project Overview: GridTest

## High-Level Summary

-   **Project:** GridTest, a rogikuelike prototype written in C using Raylib.
-   **Language:** C11
-   **Libraries:** Raylib (included)
-   **Developer:** Thomas Hodgkinson (Tom)
-   **Email:** thomashodgkinson1987@gmail.com

## Session Workflow

Our collaboration follows a structured lifecycle for each development session, ensuring a clean start and a clear end.

### Bootstrap Sequence
At the beginning of each session, a bootstrap sequence is performed to bring me up to speed on the current state of the project. This involves reading all core context files and analyzing the live Git state. The full, detailed steps for this process are documented in `BOOTSTRAP-GUIDE.md`.

### Shutdown Sequence
At the end of each session, a shutdown sequence is performed to ensure the project is left in a clean, predictable state. This involves:
1.  **Health Check:** I will check the Git status, the current branch, the active task in `PLAN.md`, and any unresolved topics in `NOTES.md`.
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
    -   Modifying context guides, core workflows or anything that needs to `pause execution` or `stop-the-line`.
    -   Used for tasks that don't require a feature branch (e.g., updating `PLAN.md` after a discussion, refining workflow documents).
    -   Commits are made directly on the `develop` branch, typically with `docs(...)` or `chore(...)` scopes.

### 3. Work Mode
-   **Purpose:** Focused implementation of a single, defined task from `PLAN.md`. This is our "coding" space.
-   **Rules:** This mode strictly follows our established Kanban-style Git workflow for implementing tasks.
    -   **Branching:** Always starts by creating a new feature branch (`git switch -c ... develop`).
    -   **Task Lifecycle in `PLAN.md`:**
        1.  **Prioritise:** Locate the highest-priority task from the backlog.
        2.  **Set as Current:** Move the task from the backlog to the `Current Task` section in `PLAN.md`. The **first commit** on the new branch must be a `docs(plan): Open task` commit.
        3.  **Execute:** Work through the task's action items, making atomic commits as needed.
        4.  **Complete Task:** The **final commit** on the branch must be a `docs(plan): Close task` commit that moves the task to the `Completed Tasks` section in `PLAN.md`.
    -   5.  **Merging:** The feature branch is then squash merged back into `develop` to keep the history clean and atomic.

## Architecture

-   **Model:** A pragmatic, layered **Actor Model**. It is not a pure Entity-Component-System (ECS).
-   **Core Objects:** `Actor` structs are concrete objects with intrinsic properties (`x`, `y`, `glyph`, `colour`, `name`) and optional `Components` for extensible data (health, combat, AI).
-   **Game Loop:** The engine is built on a **Command/Result Pattern**.
    -   Gameplay logic generates "Commands" (atomic state changes).
    -   A central queue in the `command_system` module holds these commands.
    -   A `command_execute` function processes commands and returns a `Result` object.
    -   The main game loop inspects the `Result` to handle consequences (e.g., actor death, dirtying the renderer).

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
-   **Commits:** All commit messages must adhere to the **Conventional Commits** specification. We are practice creating **atomic commits** where it adds clarity.
-   **Merging:**
    -   Feature branches are always **squash merged** into `develop` to build a clean, atomic history.
    -   `develop` is merged into `main` for releases using **`--no-ff`** to preserve the history of the `develop` branch.
    -   A "back-merge" from `main` to `develop` is performed after releases to keep branches synchronized.

## Build & Run Workflow

This project uses a CMake configuration that simplifies the build and run process.

-   **Build:** To compile the project, press `F7` in VS Code, or run the following command in the terminal from the project root:
    ```bash
    cmake --build build-Debug
    ```
-   **Build & Run:** To build and run the application, use the custom `run` target.
    ```bash
    cmake --build build-Debug --target run
    ```
-   **Debug:** To launch a debugging session, press `F5` in VS Code.

## Directory Structure

The project is organized into the following key directories:

-   `/src/`: Contains all the core C source files (.c).
-   `/include/`: Contains all the public header files (.h) (including Raylib header files).
-   `/lib/`: Contains our local copy of the Raylib library.
-   `/vendor/`: Git submodules.
-   `/res/`: Contains game assets like fonts and images.
-   `/.vscode/`: Contains project-specific settings and launch configurations for VS Code.
-   `/build-*/`: Build output directories (generated by CMake, ignored by Git).
