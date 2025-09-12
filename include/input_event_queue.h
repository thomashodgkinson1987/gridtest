#ifndef INPUT_EVENT_QUEUE_H
#define INPUT_EVENT_QUEUE_H

#include <queue_macros.h>

// --- Forward Declarations ---
typedef struct input_event InputEvent;
DECLARE_QUEUE_STRUCT(input_event, InputEvent)

// --- Public Function Prototypes ---
DECLARE_QUEUE_FUNCTIONS(input_event, InputEvent, InputEvent)

#endif // INPUT_EVENT_QUEUE_H
