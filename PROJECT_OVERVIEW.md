# Project Overview: GridTest

## 1. High-Level Summary

-   **Project:** GridTest, a rogikuelike prototype written in C.
-   **Developer:** Thomas Hodgkinson (Tom)
-   **Email:** thomashodgkinson1987@gmail.com
-   **Core Philosophy:** "Productive Laziness" - building a clean, maintainable, and well-documented project now to save time and effort later.

## 2. Architecture

-   **Model:** A pragmatic, layered **Actor Model**. It is not a pure Entity-Component-System (ECS).
-   **Core Objects:** `Actor` structs are concrete objects with intrinsic properties (`x`, `y`, `glyph`, `colour`, `name`) and optional `Components` for extensible data (health, combat, AI).
-   **Game Loop:** The engine is built on a **Command/Result Pattern**.
    -   Gameplay logic generates "Commands" (atomic state changes).
    -   A central queue in the `game` module holds these commands.
    -   A `command_execute` function processes commands and returns a "Result" object.
    -   The main game loop inspects the `Result` to handle consequences (e.g., actor death, dirtying the renderer).

## 3. Project Conventions

-   **API Design:** Prefer passing explicit context (e.g., `Game*`, `Renderer*`) over using singletons. Strive for `const`-correctness with both `const` and `_mut` variants for getters where appropriate.
-   **Memory Management:** Ownership is clear and encapsulated. `_create` functions `malloc`, and corresponding `_free` functions `free`. The calling code does not manage memory for objects it receives.
-   **Formatting:** Adhere to an 80-column limit. Use include guards and a standard include order (primary header, system headers, library headers, project headers).
-   **Git Workflow:** See section below.

## 4. Git & Repository

-   **URLs:**
    -   Main Project: `https://github.com/thomashodgkinson1987/gridtest.git`
    -   `array_macros` Submodule: `https://github.com/thomashodgkinson1987/array_macros.git`
-   **Branching:** All work is done on feature/fix/chore branches, branched from `develop`.
-   **Commits:** All commit messages must adhere to the **Conventional Commits** specification. We practice creating **atomic commits** where it adds clarity.
-   **Merging:**
    -   Features are merged into `develop` using a **squash merge**.
    -   `develop` is merged into `main` for releases using a **`--no-ff` merge**.
    -   A "back-merge" from `main` to `develop` is performed after releases to keep branches synchronized.
