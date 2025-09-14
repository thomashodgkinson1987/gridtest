# Copilot Instructions

This document provides guidance for AI coding agents to effectively contribute to the `gridtest` project. It outlines the project's vision, architecture, and the specific workflows you are expected to follow.

## Project Vision: Project Chimera

The long-term vision for this codebase is **Project Chimera**, a procedurally generated, science-fantasy roguelike focused on systemic simulation and emergent narrative. Key principles include:

-   **Systemic World:** A world that operates on persistent, interconnected systems (factions, ecosystems) independent of the player.
-   **Procedural Generation:** All elements are generated algorithmically to create a universe with discoverable rules.
-   **Emergent Narrative:** The story emerges from the interplay of world systems and player choices, not from a pre-authored plot.

*Source: `/.isaiah/PROPHESY.md`*

## AI Collaboration Workflow

This project uses a structured workflow for collaboration between the developer (Tom) and the AI (Rubix). You must adhere to these protocols.

### Session Lifecycle

-   **Bootstrap:** At the start of every session, you must follow the steps in `/.tabernacle/BOOTSTRAP-GUIDE.md` to gain full project context. This involves reading persona files, project overviews, Kanban boards, and analyzing the Git state.
-   **Shutdown:** At the end of a session, a handoff document is generated to summarize progress and plan the next session.

### Development Modes

-   **Plan Mode:** The default mode for discussion, brainstorming, and research. No code is modified.
-   **Admin Mode:** For meta-work like updating documentation or plans. Commits are made directly to the `develop` branch.
-   **Work Mode:** For focused task implementation on a feature branch, following the Kanban workflow.

### Kanban-Style Git Workflow

The project uses a Kanban system managed through markdown files in the `/.cubit/` directory.

1.  **Branch:** Always create a new feature branch from `develop` (`git switch -c ...`).
2.  **Open Task:** Move a task from `/.cubit/KANBAN_BACKLOG.md` to `/.cubit/KANBAN_CURRENT.md`. The **first commit** on the branch must be a `docs(plan): Open task` commit recording this change.
3.  **Implement:** Work on the task, making atomic commits.
4.  **Close Task:** When finished, move the task from `/.cubit/KANBAN_CURRENT.md` to `/.cubit/KANBAN_COMPLETED.md`. The **final commit** must be a `docs(plan): Close task` commit.

*Source: `/.tabernacle/PROJECT-OVERVIEW.md`*

## Architecture

The project is a roguelike game written in C, using the Raylib library for rendering. The architecture is a pragmatic, layered **Actor Model**, not a pure Entity-Component-System (ECS).

-   **Core Objects:** `Actor` structs are concrete objects with intrinsic properties and optional `Component`s for extensible data (e.g., health, AI).
-   **Game Loop & Command Pattern:** The game loop is driven by a state machine (`GameState` in `game.c`). Gameplay logic generates `Command`s (e.g., move, attack), which are processed by the `CommandSystem`. This decouples intent from execution.
-   **Key Modules:**
    -   **`main.c`**: Entry point, initializes all systems.
    -   **`game.c`**: Orchestrates the main game loop, state, and systems.
    -   **`world.c`**: Manages the map (`Tile`s) and the list of `Actor`s.
    -   **`actor.c`**: Defines the core game entities.
    -   **`component.c`**: Defines data-only components attachable to actors.
    -   **`input_system.c`**: Translates raw input into `InputEvent`s.
    -   **`command_system.c`**: Processes the queue of `Command`s.
    -   **`renderer.c`**: Handles all rendering with Raylib.

## Developer Workflow

The project uses a containerized development environment.

### Dev Container (Podman)

-   The environment is defined in `devcontainer.json` and uses a Podman container.
-   To build the container image, run `./dev-build.sh`.
-   To get an interactive shell inside the container, run `./dev-shell.sh`.
-   To execute a command inside the container, use `./dev-exec.sh <command>`.
-   **Recommended VS Code Extensions:** `ms-vscode.cpptools-extension-pack`, `ms-vscode.cmake-tools`, `GitHub.github-vscode-theme`.

### Building (CMake)

-   The project uses CMake. The build process is defined in `CMakeLists.txt`.
-   A `run` target is defined to build and run the application: `make run` (inside the container) or `cmake --build <build-dir> --target run`.
-   **Build Configurations:**
    -   **Linux (Container):** `cmake -S . -B build-container-Debug`
    -   **Windows (Cross-Compile):** `cmake -S . -B build-Windows -DCMAKE_TOOLCHAIN_FILE=toolchain-windows.cmake`

## Conventions

-   **Official Style Guide:** All conventions for C code, documentation, Git, and workflow are formally documented in **`STYLE-GUIDE.md`**. This is the single source of truth.
-   **Memory Management**: Manual memory management is required. Creator functions (e.g., `game_create`) return heap-allocated pointers, which must be freed with a corresponding `_free` function (e.g., `game_free`).
-   **Headers/Sources**: Each module has a `.h` file in `include/` (public interface) and a `.c` file in `src/` (implementation).
-   **Data Structures**: The project uses custom data structures from `vendor/array_macros` and `vendor/queue-macros`.
