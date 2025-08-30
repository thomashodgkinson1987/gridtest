# Backlog

## Lesson: Implement a Hash Map in C
-   **Goal:** Learn about and discuss the implementation of hash maps in C.
-   **Type:** `lesson`
-   **Priority:** High
-   **Branch:** none
-   **Action 1 (Research):** Independently research the theory and common implementation patterns of hash maps in C (hash functions, collision resolution, etc.).
-   **Action 2 (Discussion):** Hold a discussion session to review findings, clarify concepts, and sketch out a potential C implementation for future use in the project.

## Refactor: Add `const`-correctness to `array_macros`
-   **Goal:** Refactor the `array_macros` submodule to be fully `const`-correct, allowing for safer, read-only access to array data.
-   **Type:** `refactor`
-   **Priority:** Low
-   **Branch:** `refactor/array-macros-const-correctness`
-   **Action 1:** Add `const`-correct variants for getter functions in `array_macros.h` (e.g., a version of `array_get` that accepts a `const array*`).
-   **Action 2:** Update the `gridtest` codebase to use the new `const`-correct functions where appropriate, resolving the current technical debt in `actor.c`.

## Refactor: Apply `iter_` Naming Convention
-   **Goal:** Refactor the codebase to consistently use the `iter_` prefix for loop variables where there is a name collision with a result variable.
-   **Type:** `refactor`
-   **Priority:** Medium
-   **Branch:** `refactor/apply-iter-convention`
-   **Action 1:** Search the codebase for instances of name collisions between loop variables and result variables.
-   **Action 2:** Rename the loop variables to use the `iter_` prefix (e.g., `iter_component`) to resolve ambiguity and improve clarity.

## Refactor: Standardize Enum Naming to use `_NONE`
-   **Goal:** Refactor all enums to use `_NONE` as the zero-value member instead of `_NULL` for better semantic clarity.
-   **Type:** `refactor`
-   **Priority:** Medium
-   **Branch:** `refactor/standardize-enum-naming`
-   **Action 1:** Find all enums that use a `_NULL` suffix for their default/zero member (e.g., `CommandType`, `ComponentType`).
-   **Action 2:** Rename the member to use the `_NONE` suffix.
-   **Action 3:** Update all call sites throughout the codebase that reference the old `_NULL` member name.

## Refactor: Add Error Handling to `array_macros`
-   **Goal:** Improve the `array_macros` library by adding a robust error handling strategy that avoids direct logging.
-   **Type:** `refactor`
-   **Priority:** Low
-   **Branch:** `refactor/array-macros-error-handling`
-   **Action 1:** Design an error handling strategy (e.g., returning error codes, using a global error state) that keeps the library decoupled from any specific logging implementation.
-   **Action 2:** Implement the chosen strategy, updating macros that can fail (e.g., `array_push` on a full array) to report errors.
