#include "input_system.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include <raylib.h>

#include "input_event.h"
#include "input_event_queue.h"
#include "log.h"

// --- Internal Module Definitions ---
struct input_system
{
    InputEventQueue *event_queue;
};

// --- Public Function Definitions ---
InputSystem *input_system_create(void)
{
    InputSystem *input_system = malloc(sizeof(*input_system));
    assert(input_system);

    input_system->event_queue = input_event_queue_create(2);

    return input_system;
}
void input_system_free(InputSystem *input_system)
{
    input_event_queue_free(input_system->event_queue);
    free(input_system);
}

void input_system_poll_input(InputSystem *input_system)
{
    const bool is_q = IsKeyPressed(KEY_Q);
    const bool is_4 = IsKeyPressed(KEY_KP_4);
    const bool is_6 = IsKeyPressed(KEY_KP_6);
    const bool is_8 = IsKeyPressed(KEY_KP_8);
    const bool is_2 = IsKeyPressed(KEY_KP_2);
    const bool is_5 = IsKeyPressed(KEY_KP_5);

    InputEvent event = {INPUT_EVENT_TYPE_NONE};

    if (is_q)
    {
        event = (InputEvent){INPUT_EVENT_TYPE_QUIT};
    }
    else if (is_4 && !is_6 && !is_8 && !is_2 && !is_5)
    {
        event = (InputEvent){INPUT_EVENT_TYPE_ACTOR_MOVE_WEST};
    }
    else if (!is_4 && is_6 && !is_8 && !is_2 && !is_5)
    {
        event = (InputEvent){INPUT_EVENT_TYPE_ACTOR_MOVE_EAST};
    }
    else if (!is_4 && !is_6 && is_8 && !is_2 && !is_5)
    {
        event = (InputEvent){INPUT_EVENT_TYPE_ACTOR_MOVE_NORTH};
    }
    else if (!is_4 && !is_6 && !is_8 && is_2 && !is_5)
    {
        event = (InputEvent){INPUT_EVENT_TYPE_ACTOR_MOVE_SOUTH};
    }
    else if (!is_4 && !is_6 && !is_8 && !is_2 && is_5)
    {
        event = (InputEvent){INPUT_EVENT_TYPE_ACTOR_WAIT};
    }

    if (WindowShouldClose())
    {
        event = (InputEvent){INPUT_EVENT_TYPE_QUIT};
    }

    if (event.type != INPUT_EVENT_TYPE_NONE)
    {
        input_event_queue_push(input_system->event_queue, event);
    }
}

bool input_system_has_event(const InputSystem *input_system)
{
    return !input_event_queue_is_empty(input_system->event_queue);
}
InputEvent input_system_next_event(InputSystem *input_system)
{
    InputEvent event;

    if (input_system_has_event(input_system))
    {
        input_event_queue_pop(input_system->event_queue, &event);
    }
    else
    {
        event = (InputEvent){INPUT_EVENT_TYPE_NONE};
    }

    return event;
}
