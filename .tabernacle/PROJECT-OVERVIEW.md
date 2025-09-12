# Project Overview: GridTest

## High-Level Summary

-   **Project:** GridTest, a roguelike prototype written in C using Raylib.
-   **Language:** C11
-   **Libraries:** Raylib (via source submodule)
-   **Developer:** Thomas Hodgkinson (Tom)
-   **Email:** thomashodgkinson1987@gmail.com

## Session Workflow

Our collaboration follows a structured lifecycle for each development session, ensuring a clean start and a clear end.

### Bootstrap Sequence
At the beginning of each session, a bootstrap sequence is performed to bring me up to speed on the current state of the project. This involves reading all core context files and analyzing the live Git state. The full, detailed steps for this process are documented in `/.tabernacle/BOOTSTRAP-GUIDE.md`.

### Shutdown Sequence
At the end of each session, a shutdown sequence is performed to create a clear and structured handoff for the next session.
1.  **Health Check:** I will perform a final check of the Git status, the current branch, and the Kanban boards.
2.  **Handoff Generation:** I will create a new `handoff-DD-MM-YYYY.md` file. Using the official template, I will summarize the session's accomplishments, document the final project state, and outline a proposed plan for our next session. I will carry over any important unresolved notes.
3.  **Final Actions:** We will take any necessary final actions, such as making a last commit, to ensure the project is in a clean state.

## Development Modes

Our collaboration is structured around three distinct modes of operation to ensure flexibility and efficiency. We default to **Plan Mode** at the start of every session.

### 1. Plan Mode
-   **Purpose:** Discussion, brainstorming, research, and defining tasks. This is our "thinking" space.
-   **Rules:**
    -   No code or documentation is modified, except for `/.tabernacle/NOTES.md`.
    -   We can freely read any file and check the Git state (`git status`, `git log`).
    -   No branches are created, and no commits are made.

### 2. Admin Mode
-   **Purpose:** Managing the project and our process. This mode is for "meta-work" that should be committed directly to `develop`.
-   **Rules:**
    -   Modifying context guides, core workflows or anything that needs to `pause execution` or `stop-the-line`.
    -   Used for tasks that don't require a feature branch (e.g., updating `/.cubit/KANBAN_BACKLOG.md` after a discussion, refining workflow documents).
    -   Commits are made directly on the `develop` branch, typically with `docs(...)` or `chore(...)` scopes.

### 3. Work Mode
-   **Purpose:** Focused implementation of a single, defined task. This is our "coding" space.
-   **Rules:** This mode strictly follows our established Kanban-style Git workflow for implementing tasks.
    -   **Branching:** Always starts by creating a new feature branch (`git switch -c ... develop`).
    -   **Task Lifecycle on the Kanban Boards:**
        1.  **Prioritise:** Locate the highest-priority task in `/.cubit/KANBAN_BACKLOG.md`. Each task links to a detailed action plan in the `/.cubit/tasks/` directory.
        2.  **Set as Current:** Move the task from `/.cubit/KANBAN_BACKLOG.md` to `/.cubit/KANBAN_CURRENT.md`. The **first commit** on the new branch must be a `docs(plan): Open task` commit that records this change.
        3.  **Execute:** Work through the task's action items as defined in its detail file, making atomic commits as needed.
        4.  **Complete Task:** The **final commit** on the branch must be a `docs(plan): Close task` commit that moves the task from `/.cubit/KANBAN_CURRENT.md` to `/.cubit/KANBAN_COMPLETED.md`.

## Architecture

-   **Model:** A pragmatic, layered **Actor Model**. It is not a pure Entity-Component-System (ECS).
-   **Core Objects:** `Actor` structs are concrete objects with intrinsic properties (`x`, `y`, `glyph`, `colour`, `name`) and optional `Components` for extensible data (health, combat, AI).
-   **Game Loop:** The engine is built on a **Command/Result Pattern**.
    -   Gameplay logic generates "Commands" (atomic state changes).
    -   A central queue in the `command_system` module holds these commands.
    -   A `command_execute` function processes commands and returns a `Result` object.
    -   The main game loop inspects the `Result` to handle consequences (e.g., actor death, dirtying the renderer).

## Project Conventions & Workflow

All conventions for C code, documentation, Git, and our overall workflow are formally documented in the project's official style guide.

**Please refer to the [STYLE-GUIDE.md](./STYLE-GUIDE.md) for a complete reference.**

## Git Repositories

-   **Main Project:** `https://github.com/thomashodgkinson1987/gridtest.git`
-   **`array_macros` Submodule:** `https://github.com/thomashodgkinson1987/array_macros.git`
-   **`queue_macros` Submodule:** `https://github.com/thomashodgkinson1987/queue-macros.git`
-   **`raylib` Submodule:** `https://github.com/raysan5/raylib.git`

## Build & Run Workflow

This project uses a portable, multi-platform CMake configuration.

### Building for Linux (Native)

1.  **Configure (if needed):**
    ```bash
    cmake -S . -B build-Debug -DCMAKE_BUILD_TYPE=Debug
    ```
2.  **Build:**
    ```bash
    cmake --build build-Debug
    ```
3.  **Build & Run:**
    ```bash
    cmake --build build-Debug --target run
    ```
4.  **Debug:** To launch a debugging session, press `F5` in VS Code.

### Building for Windows (Cross-Compilation)

This requires the `mingw64-gcc` and `mingw64-gcc-c++` packages.

1.  **Configure (if needed):**
    ```bash
    cmake -S . -B build-Windows -DCMAKE_TOOLCHAIN_FILE=toolchain-windows.cmake -DCMAKE_BUILD_TYPE=Debug
    ```
2.  **Build:**
    ```bash
    cmake --build build-Windows
    ```
    The final executable will be located at `build-Windows/gridtest.exe`.

## Directory Structure

The project is organized into the following key directories:

-   `/.isaiah/`: Contains the high-level project vision and guiding principles.
-   `/.tabernacle/`: Contains the foundational context for our AI collaboration (persona, project overview, bootstrap guide).
-   `/.cubit/`: Contains the concrete project plans, including Kanban boards and detailed task files.
-   `/src/`: Contains all the core C source files (.c).
-   `/include/`: Contains all the public header files (.h).
-   `/lib/`: Contains the Raylib source submodule.
-   `/vendor/`: Contains other third-party source submodules.
-   `/res/`: Contains game assets like fonts and images.
-   `/.vscode/`: Contains project-specific settings and launch configurations for VS Code.
-   `/build-*/`: Build output directories (generated by CMake, ignored by Git).
