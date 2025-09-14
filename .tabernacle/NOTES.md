# Session Notes
*This file is for transient notes created **during** a single session. Important points that need to persist to the next session will be captured in the handoff document during the shutdown sequence.*

-   **Technical Debt Identified (Input System):** The `InputSystem` currently directly couples to Raylib's input functions (`IsKeyPressed`, `WindowShouldClose`).
-   **Action Item:** For a future refactor, a dedicated abstraction layer should be introduced (e.g., a `RaylibInputAdapter`) to fully decouple the `InputSystem` from Raylib, allowing for easier switching to other input libraries.
