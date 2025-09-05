# Refactor: Use Opaque Pointer in `array-macros`

-   **Goal:** To improve encapsulation and API design in the `array-macros` library by refactoring it to use an opaque pointer (handle).
-   **Type:** `refactor`
-   **Scope:** `deps`
-   **Parent Task:** Part of a series to refactor external macro libraries.

---

## Action Plan

### Phase 1: Refactor `array-macros` Library
*This work will be done within the `array-macros` repository.*

1.  **Update Header:** Modify the public header file.
    -   Replace the full struct definition with a forward declaration (e.g., `struct Array;`).
    -   Update all public API function signatures to accept/return an `Array*` handle.
2.  **Implement Lifecycle Functions:** Create and expose `array_create()` and `array_free()` functions to manage memory for the `Array` object.
3.  **Commit and Push:** Commit the changes and push them to the `array-macros` remote repository.

### Phase 2: Integrate Changes into GridTest
*This work will be done within the GridTest repository.*

1.  **Update Submodule:** Fetch the latest changes for the submodule.
2.  **Refactor Call Sites:** Search the GridTest codebase for all usages of the `array-macros` library and update them to use the new handle-based API (including creation and destruction).
3.  **Verification:** Build and run the project to confirm that all interactions with the `array-macros` library are functioning correctly.
