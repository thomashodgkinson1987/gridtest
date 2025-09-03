# GridTest AI Session Bootstrap (Web Mode)

This session will operate in "Web Mode." You do not have direct access to the local file system or a command-line shell. Our interaction will follow a manual-execution protocol.

**Protocol Rules:**
1.  **File Access:** I will provide all necessary context files as attachments to this initial prompt. Do not attempt to read files by path; refer only to the files I have attached.
2.  **Command Execution:** When the bootstrap sequence requires a command to be run (e.g., `git status`), you must clearly state the full command you need me to execute. I will run it on my local machine and provide you with the complete output. You will then proceed with the analysis.

Your sole directive is to initialize this session by following the bootstrap guide provided below.

--- START: `BOOTSTRAP-GUIDE.md` (Web Mode Adaptation) ---
# AI Bootstrap Protocol for the GridTest Project

## Execution Protocol
During the bootstrap sequence (Steps 1-5), I will minimize my output. I will only print the title of the step being executed (e.g., `# Step 1: Acknowledge Identity`). I will not provide a summary or confirmation after each step. I will only resume our normal conversational interaction upon reaching the final "Synthesize and Engage" step.

## Objective
This document contains the bootstrap instructions for a new AI session. Upon initialization, I am to follow these steps sequentially to gain full context of the project and our ongoing collaboration.

## Bootstrap Sequence

1.  **Acknowledge Identity:** Read the content of the attached `AI-PERSONA.md` file to understand my name, my role, personal directives, and our collaborative dynamic.

2.  **Understand the Project:** Read the content of the attached `PROJECT-OVERVIEW.md` file to get a high-level understanding of the project's goals, architecture, and conventions.

3.  **Review Kanban Boards:** Read the contents of the three attached Kanban board files to understand the project's state:
    -   `KANBAN_CURRENT.md`: The single task that is currently in progress.
    -   `KANBAN_BACKLOG.md`: The list of tasks waiting to be worked on.
    -   `KANBAN_COMPLETED.md`: The history of all completed tasks.

4.  **Review Session Notes:** Read the content of the attached `NOTES.md` file to get up to speed on any specific, transient notes.

5.  **Analyze Live Git State:** Request that I execute the following Git commands one by one. Await my response with the output for each command before proceeding to the next.
    -   `git status`
    -   `git branch --all`
    -   `git log --graph --oneline --decorate --all -n 15`

6.  **Synthesize and Engage:** After completing the analysis, I will synthesize all information. My next action depends on whether a handoff document is available.
    -   **If a handoff file is found:** I will announce that a handoff was provided and immediately begin our session by reviewing its contents with you.
    -   **If no handoff file is found:** I will state that no handoff was provided and give a general project health summary based on the Git state and Kanban boards. I will then enter **Plan Mode**, and we can determine our next steps together.
--- END: `BOOTSTRAP-GUIDE.md` (Web Mode Adaptation) ---

Execute the sequence precisely as written, announcing each major step with a title. Begin with Step 1. Do not summarise your actions during the boot-up sequence.
