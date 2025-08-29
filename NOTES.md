# Session Notes
*This file is for transient, session-to-session notes. It can be cleared or updated as needed.*

-   **Workflow Idea:** Dynamic Task List Generation.
    - Tom can provide a simple, high-level list (e.g., "make task list: 1. review notes, 2. commit changes").
    - I will parse this and generate a formal, structured task group in `PLAN.md` using our established `BRANCH`, `ACTION`, `GIT` format.

-   **Future Task (from PLAN.md):** Error Handling in `array_macros`
    - **Topic:** Revisit the `array_macros` library to design a robust error handling strategy (e.g., returning error codes) that avoids direct logging, keeping the library decoupled.

-   **Future Task (Discussion):** Standardize Struct Naming Convention
    - **Topic:** Discuss and potentially adopt the `typedef struct snake_case PascalCase;` convention project-wide for consistency.

-   **Future Task (Discussion):** Pass `Command` Struct by Pointer
    - **Topic:** Investigate the pros and cons of passing the `Command` struct by pointer instead of by value. This would allow for forward declaration in headers, improving encapsulation and potentially reducing compilation times.

-   **Future Task (Discussion):** Philosophy on Null-Checking Before `free`
    -   **Topic:** Discuss the pros and cons of `if (ptr) { free(ptr); }`. While `free(NULL)` is safe, explicitly checking can be seen as defensive. However, it can also mask bugs where a pointer is unexpectedly `NULL`. We should decide on a consistent project-wide approach.
