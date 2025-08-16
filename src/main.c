#include "raylib.h"

#include "constants.h"
#include "game.h"

int main(void)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(TARGET_FPS);

    game_init();

    float delta = 0.0f;

    while (!WindowShouldClose())
    {
        delta = GetFrameTime();

        if (IsKeyPressed(KEY_R))
        {
            game_free();
            game_init();

            delta = 0.0f;
        }

        game_tick(delta);

        game_draw();
    }

    game_free();

    CloseWindow();

    return 0;
}
