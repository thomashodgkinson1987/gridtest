#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include <stdbool.h>

#include "input_event.h"

// --- Forward Declarations ---
typedef struct input_system InputSystem;

// --- Public Function Prototypes ---
InputSystem *input_system_create(void);
void input_system_free(InputSystem *input_system);

void input_system_poll_input(InputSystem *input_system);

bool input_system_has_event(const InputSystem *input_system);
InputEvent input_system_next_event(InputSystem *input_system);

#endif // INPUT_SYSTEM_H
