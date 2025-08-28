<overview>
# Project Overview: GridTest

### High-Level Summary

-   **Project:** GridTest, a rogikuelike prototype written in C.
-   **Developer:** Thomas Hodgkinson (Tom)
-   **Email:** thomashodgkinson1987@gmail.com
-   **Core Philosophy:** "Productive Laziness" - building a clean, maintainable, and well-documented project now to save time and effort later.

### Architecture

-   **Model:** A pragmatic, layered **Actor Model**. It is not a pure Entity-Component-System (ECS).
-   **Core Objects:** `Actor` structs are concrete objects with intrinsic properties (`x`, `y`, `glyph`, `colour`, `name`) and optional `Components` for extensible data (health, combat, AI).
-   **Game Loop:** The engine is built on a **Command/Result Pattern**.
    -   Gameplay logic generates "Commands" (atomic state changes).
    -   A central queue in the `game` module holds these commands.
    -   A `command_execute` function processes commands and returns a "Result" object.
    -   The main game loop inspects the `Result` to handle consequences (e.g., actor death, dirtying the renderer).

### Project Conventions

-   **API Design:** Prefer passing explicit context (e.g., `Game*`, `Renderer*`) over using singletons. Strive for `const`-correctness with both `const` and `_mut` variants for getters where appropriate.
-   **Memory Management:** Ownership is clear and encapsulated. `_create` functions `malloc`, and corresponding `_free` functions `free`. The calling code does not manage memory for objects it receives.
-   **Formatting:** Adhere to an 80-column limit. Use include guards and a standard include order (primary header, system headers, library headers, project headers).
-   **Git Workflow:** See section below.

### Kanban-Style Task Workflow

Our collaboration follows a structured, Kanban-style workflow managed via `PLAN.md`. The plan is divided into three sections: `Current Task`, `Upcoming Tasks (Backlog)`, and `Completed Tasks`.

1.  **Initiate Task:** We select the highest-priority task from the `Upcoming Tasks` backlog.
2.  **Set as Current:** The task is moved from the backlog into the `Current Task` section. This change is the very first commit on a new feature branch.
3.  **Execute:** We work through the task's action items.
4.  **Complete Task:** Once all work is done, the task is moved from `Current Task` to the top of the `Completed Tasks` list. This is typically done in the final commit before merging the feature branch.

### Git & Repository

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

### Build & Run Workflow

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

### Managing Metadata (`PLAN.md`, `NOTES.md`)

To keep the `develop` branch history clean and contextually relevant, changes to metadata files are committed as part of the feature lifecycle.

1.  **Start of Task:** On a new feature branch, the **first commit** must be a `docs(plan)` commit that moves a task from the `Upcoming Tasks` section to the `Current Task` section in `PLAN.md`.
2.  **End of Task:** Before merging, the **final commit** on the feature branch should be another `docs(plan)` commit. This commit's sole purpose is to move the task from `Current Task` to the `Completed Tasks` section.
3.  **Squash and Merge:** When the feature branch is squashed and merged, all changes—including the initial and final plan updates—are bundled into a single, clean commit on `develop`. This ensures the plan always reflects the state of the codebase at the time of the merge.

### Directory Structure

The project is organized into the following key directories:

-   `/src/`: Contains all the core C source files (.c).
-   `/include/`: Contains all the public header files (.h) that make up the modules' APIs.
-   `/lib/`: Contains pre-compiled third-party libraries (e.g., Raylib).
-   `/vendor/`: Contains third-party source code managed as Git submodules (e.g., array_macros).
-   `/res/`: Contains game assets like fonts and images.
-   `/.vscode/`: Contains project-specific settings and launch configurations for VS Code.
-   `/build-*/`: Build output directories (generated by CMake, ignored by Git).
</overview>
