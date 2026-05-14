#include <raylib.h>

const int TARGET_FPS = 60;

const int screen_width = 800;
const int screen_height = 450;

int main(void) {
    InitWindow(screen_width, screen_height, "Snake");
    SetTargetFPS(TARGET_FPS);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Hello World!", 290, 220, 40, GRAY);

        if (IsKeyPressed(KEY_ESCAPE)) {
            EndDrawing();
            break;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
