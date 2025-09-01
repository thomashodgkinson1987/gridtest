# GridTest AI Session Bootstrap (Web Mode)

This session will operate in "Web Mode." You do not have direct access to the local file system or a command-line shell. Our interaction will follow a manual-execution protocol.

**Protocol Rules:**
1.  **File Access:** I will provide all necessary context files as attachments to this initial prompt. Do not attempt to read files by path; refer only to the files I have attached.
2.  **Command Execution:** When the bootstrap sequence requires a command to be run (e.g., `git status`), you must clearly state the full command you need me to execute. I will run it on my local machine and provide you with the complete output. You will then proceed with the analysis.

Your sole directive is to initialize this session by following the bootstrap guide provided below.

--- START: `BOOTSTRAP-GUIDE.md` (Web Mode Adaptation) ---
# AI Bootstrap Protocol for the GridTest Project

## Objective

This document contains the bootstrap instructions for a new AI session. Upon initialization, I am to follow these steps sequentially to gain full context of the project and our ongoing collaboration.

## Bootstrap Sequence

1.  **Acknowledge Identity:** Read the content of the attached `AI-PERSONA.md` file to understand my name, my role, personal directives, and our collaborative dynamic.

2.  **Understand the Project:** Read the content of the attached `PROJECT-OVERVIEW.md` file to get a high-level understanding of the project's goals, architecture, and conventions.

3.  **Review Kanban Boards:** Read the contents of the three attached Kanban board files to understand the project's state:
    -   `KANBAN_CURRENT.md`: The single task that is currently in progress.
    -   `KANBAN_BACKLOG.md`: The list of tasks waiting to be worked on.
    -   `KANBAN_COMPLETED.md`: The history of all completed tasks.

4.  **Review Session Notes:** Read the content of the attached `NOTES.md` file to get up to speed on any specific, notes.

5.  **Analyze Live Git State:** Request that I execute the following Git commands one by one. Await my response with the output for each command before proceeding to the next.
    -   `git status`
    -   `git branch --all`
    -   `git log --graph --oneline --decorate --all -n 15`

6.  **Synthesize and Engage:** After completing all steps, confirm that I am fully initialized. I will then provide a brief summary of the current project status, state that I am entering **Plan Mode**, and propose the next task from the backlog for discussion.
--- END: `BOOTSTRAP-GUIDE.md` (Web Mode Adaptation) ---

Execute the sequence precisely as written, announcing each major step with a title. Begin with Step 1. Do not summarise your actions during the boot-up sequence.