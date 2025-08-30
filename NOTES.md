# Session Notes
*This file is for transient, session-to-session notes. It can be cleared or updated as needed.*

-   **Technical Debt:** Improve `const`-correctness in `array_macros`.
    -   **Issue:** The `array_macros` library lacks `const`-correct getters (e.g., a version of `array_get` that takes a `const array*`).
    -   **Impact:** This forces functions like `actor_get_component` to take a non-const `Actor*` even when they don't modify it, weakening the compiler's safety checks.
    -   **Action:** Deferring this until a dedicated refactor of the `array_macros` submodule.

-   **Future Task:** Apply `iter_` naming convention.
    -   **Goal:** Refactor the codebase to use the `iter_` prefix for loop variables where there is a name collision with a result variable.
    -   **Reason:** To improve code clarity and consistency.

-   **Future Topic:** Learning session on hash maps.
    -   **Goal:** Discuss and understand how to implement a hash map in C.
    -   **Reason:** Could be a more efficient alternative to array iteration for lookups.

-   **Future Task:** Revisit `_NULL` vs `_NONE` enum naming convention.
    -   **Topic:** We should standardize on `_NONE` for enums like `CommandType` and `ComponentType` for better semantic clarity, as `_NULL` is typically for pointers.

-   **Workflow Idea:** Dynamic Task List Generation.
    -   Tom can provide a simple, high-level list (e.g., "make task list: 1. review notes, 2. commit changes").
    -   I will parse this and generate a formal, structured task group in `PLAN.md` using our established `BRANCH`, `ACTION`, `GIT` format.

-   **Future Task (from PLAN.md):** Error Handling in `array_macros`
    -   **Topic:** Revisit the `array_macros` library to design a robust error handling strategy (e.g., returning error codes) that avoids direct logging, keeping the library decoupled.

-   **Workflow Improvement:** Split `PLAN.md` into three files (`KANBAN_CURRENT.md`, `KANBAN_BACKLOG.md`, `KANBAN_COMPLETED.md`) to improve token efficiency and scalability.
