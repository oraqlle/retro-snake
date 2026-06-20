#include <raylib.h>

#include <stdio.h>

const int TARGET_FPS = 60;

const int screen_width = 1000;
const int screen_height = 1000;
const Color background_colour = { .r = 245, .g = 245, .b = 245, .a = 255 };

typedef struct {
    int x;
    int y;
} Vector2i;

void input(void) {}

void update(float delta) { delta = delta * 2; }

void draw(void) {
    Rectangle rec1 = { .x = 420, .y = 290, .width = 20, .height = 20 };
    Rectangle rec2 = { .x = 420, .y = 315, .width = 20, .height = 20 };

    DrawRectangleRec(rec1, BLACK);
    DrawRectangleRec(rec2, BLACK);
}

int main(void) {
    InitWindow(screen_width, screen_height, "Snake");
    SetTargetFPS(TARGET_FPS);

    while (!WindowShouldClose()) {
        float delta = GetFrameTime();

        input();
        update(delta);

        BeginDrawing();
        ClearBackground(background_colour);
        DrawFPS(0, 0);
        draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
