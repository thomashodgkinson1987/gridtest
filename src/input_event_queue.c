#include "input_event_queue.h"

#include "queue_macros.h"

#include "input_event.h"

// --- Internal Module Definitions ---
DEFINE_QUEUE_STRUCT(input_event, InputEvent, InputEvent)

// --- Public Function Definitions ---
DEFINE_QUEUE_FUNCTIONS(input_event, InputEvent, InputEvent)
