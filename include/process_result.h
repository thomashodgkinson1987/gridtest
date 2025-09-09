#ifndef PROCESS_RESULT_H
#define PROCESS_RESULT_H

#include <stdbool.h>

// --- Type Definitions ---
typedef struct process_result
{
    bool did_quit;
    bool is_redraw;
} ProcessResult;

#endif // PROCESS_RESULT_H
