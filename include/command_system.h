#ifndef COMMAND_SYSTEM_H
#define COMMAND_SYSTEM_H

// --- Opaque Pointer ---
// The user of this API does not need to know the internal details of the
// CommandSystem struct, so we forward-declare it here. The full definition
// is in the corresponding .c file.
typedef struct command_system CommandSystem;

// --- Forward Declarations for Dependencies ---
// We only need pointers to these types in the header, so we can forward-declare
// them to avoid including their full headers, which speeds up compilation.
typedef struct command Command;
typedef struct renderer Renderer;
typedef struct world World;

// --- Lifecycle Functions ---

/**
 * @brief Creates a new CommandSystem instance.
 * @return A pointer to the newly allocated CommandSystem, or NULL on failure.
 */
CommandSystem *command_system_create(void);

/**
 * @brief Frees all resources associated with a CommandSystem instance.
 * @param command_system A pointer to the CommandSystem instance to be freed.
 */
void command_system_free(CommandSystem *command_system);

// --- Command Management Functions ---

/**
 * @brief Adds a command to the command queue for later processing.
 * @param command_system A pointer to the CommandSystem instance.
 * @param command A pointer to the command to be added.
 */
void command_system_add_command(
    CommandSystem *command_system,
    const Command *command);

/**
 * @brief Processes all commands currently in the queue.
 * @param command_system A pointer to the CommandSystem instance.
 * @param renderer A pointer to the Renderer for handling related results.
 * @param world A pointer to the World for handling world-state command results
 */
void command_system_process_queue(
    CommandSystem *command_system,
    Renderer *renderer,
    World *world);

#endif // COMMAND_SYSTEM_H
