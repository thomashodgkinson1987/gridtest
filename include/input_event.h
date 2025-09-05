#ifndef INPUT_EVENT_H
#define INPUT_EVENT_H

// --- Type Definitions ---
typedef enum input_event_type
{
    INPUT_EVENT_TYPE_NONE,

    INPUT_EVENT_TYPE_ACTOR_MOVE_NORTH,
    INPUT_EVENT_TYPE_ACTOR_MOVE_SOUTH,
    INPUT_EVENT_TYPE_ACTOR_MOVE_EAST,
    INPUT_EVENT_TYPE_ACTOR_MOVE_WEST,

    INPUT_EVENT_TYPE_ACTOR_WAIT,

    INPUT_EVENT_TYPE_QUIT,

    INPUT_EVENT_TYPE_COUNT
} InputEventType;

typedef struct input_event
{
    InputEventType type;
} InputEvent;

#endif // INPUT_EVENT_H
