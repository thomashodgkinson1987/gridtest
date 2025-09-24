# Refactor: Professionalise the array-macros Library

-   **Goal:** To replace the legacy `array_macros` library with a new, professional-grade `array-macros` library, built to the same high standard as `queue-macros`.
-   **Type:** `refactor`
-   **Priority:** High
-   **Branch:** `refactor/professionalise-array-macros`

---

## Action Plan
This task is divided into two distinct phases. Phase 1 involves creating the new, standalone library. Phase 2 involves integrating it into the main `gridtest` project.

### Phase 1: Create the New `array-macros` Library
*(This work takes place outside the `gridtest` repository)*

1.  **Create New Repository:** Create a new, empty repository on GitHub named `array-macros`.
2.  **Clone Locally:** Clone the new, empty repository to your local machine.
3.  **Bootstrap Project Structure:** Using `queue-macros` as a template, create a professional project structure:
    -   Set up a `CMakeLists.txt` file.
    -   Create a `README.md` with build and usage instructions.
    -   Implement a test suite using CMake.
4.  **Implement Opaque Pointer API:** Migrate the logic from the old `array_macros` library, but design the new implementation around an opaque pointer (handle) from the start. Ensure the API is robust, well-documented, and follows our established conventions.
5.  **Verify and Push:** Build the library, run the tests to ensure it is working correctly, and then push the complete, high-quality library to the `main` branch of the new `array-macros` repository.

### Phase 2: Integrate into GridTest
*(This work takes place on a feature branch within the `gridtest` repository)*

1.  **Open Task:** Create the `refactor/professionalise-array-macros` branch.
2.  **Remove Old Submodule:** Unregister and remove the old `vendor/array_macros` submodule.
    ```bash
    git rm vendor/array_macros
    ```
3.  **Add New Submodule:** Add your new, high-quality `array-macros` library as a submodule.
    ```bash
    git submodule add <URL_to_new_repo> vendor/array-macros
    ```
4.  **Update Build System:** Modify `gridtest`'s root `CMakeLists.txt` to point to the new submodule directory.
5.  **Refactor Call Sites:** Search the `gridtest` codebase for any place that used the old array library and update it to use the new, opaque-pointer-based API.
6.  **Verify Integration:** Perform a clean build of `gridtest` and run it to confirm that the new library is integrated and functioning correctly.
