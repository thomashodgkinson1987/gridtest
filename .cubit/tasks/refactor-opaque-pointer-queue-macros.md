# Refactor: Use Opaque Pointer in `queue-macros`

-   **Goal:** To improve encapsulation and API design in the `queue-macros` library by refactoring it to use an opaque pointer (handle).
-   **Type:** `refactor`
-   **Scope:** `deps`
-   **Parent Task:** Part of a series to refactor external macro libraries.

---

## Action Plan

### Phase 1: Refactor `queue-macros` Library
*This work will be done within the `queue-macros` repository.*

1.  **Update Header:** Modify the public header file.
    -   Replace the full struct definition with a forward declaration (e.g., `struct Queue;`).
    -   Update all public API function signatures to accept/return a `Queue*` handle.
2.  **Implement Lifecycle Functions:** Create and expose `queue_create()` and `queue_free()` functions to manage memory for the `Queue` object.
3.  **Commit and Push:** Commit the changes and push them to the `queue-macros` remote repository.

### Phase 2: Integrate Changes into GridTest
*This work will be done within the GridTest repository.*

1.  **Update Submodule:** Fetch the latest changes for the submodule.
2.  **Refactor Call Sites:** Search the GridTest codebase for all usages of the `queue-macros` library (e.g., in the `CommandSystem` and `InputSystem`) and update them to use the new handle-based API.
3.  **Verification:** Build and run the project to confirm that all queue operations are functioning correctly.
