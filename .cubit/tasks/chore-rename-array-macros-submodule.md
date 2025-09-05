# Chore: Rename `array_macros` Submodule

-   **Goal:** To standardize repository naming conventions by renaming the `array_macros` library and submodule to `array-macros`.
-   **Type:** `chore`
-   **Scope:** `deps`
-   **Parent Task:** Part of a series to refactor external macro libraries.

---

## Action Plan

### Phase 1: Create New Remote Repository
1.  **Create GitHub Repo:** Tom will create a new, empty GitHub repository named `array-macros`.
2.  **Push Existing Code:** Tom will push the current `array_macros` source code to the new `array-macros` remote.

### Phase 2: Update GridTest Project
1.  **Remove Old Submodule:** In the GridTest project, run `git rm vendor/array_macros` to unregister the old submodule. This will remove the directory and the relevant lines from `.gitmodules`.
2.  **Add New Submodule:** Run `git submodule add <URL_to_new_repo> vendor/array-macros` to add the newly named repository as a submodule.
3.  **Update Build System:** Modify `CMakeLists.txt` to reflect the new directory name (`vendor/array-macros` instead of `vendor/array_macros`).
4.  **Verification:** Perform a clean build of the project (`cmake --build build-Debug`) to ensure the library is still found and compiled correctly.
