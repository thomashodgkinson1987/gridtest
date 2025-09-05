# Session Notes
*This file is for transient notes created **during** a single session. Important points that need to persist to the next session will be captured in the handoff document during the shutdown sequence.*

-   **Technical Debt Identified:** The `array-macros` and `queue-macros` submodules are not `const`-correct. Their APIs currently force the caller to pass non-`const` pointers even for read-only operations. This necessitates temporary `const` casts in `actor.c`.
-   **Action Item:** The submodules should be updated to provide `const` variants of their getter functions (e.g., `array_get` should have a corresponding `const` version) to eliminate the need for casting. This can be addressed after the current batch of micro-refactors is complete.
-   **Technical Debt Identified (Input System):** The `InputSystem` currently directly couples to Raylib's input functions (`IsKeyPressed`, `WindowShouldClose`).
-   **Action Item:** For a future refactor, a dedicated abstraction layer should be introduced (e.g., a `RaylibInputAdapter`) to fully decouple the `InputSystem` from Raylib, allowing for easier switching to other input libraries.
-   **Technical Debt Identified (Command System):** The `CommandSystem` is unnecessarily coupled to the `Renderer`, as it calls the renderer directly to set a "dirty" flag.
-   **Action Item:** Refactor this interaction by adding a `needs_redraw` flag to the `ProcessResult` struct. The `CommandSystem` will set this flag, and the `Game` module will read it and orchestrate the call to the `Renderer`, breaking the direct dependency.
-   **Workflow Improvement Identified:** The AI persona should be updated to prompt Tom to write the commit message first, providing him with an opportunity to practice. The AI will then offer feedback or write the message if requested.
-   **Action Item:** Modify the "Critical Safety Protocol (Commits)" section in `/.tabernacle/AI-PERSONA.md` to reflect this new interactive step, while preserving the rule that the AI never executes `git commit`.
