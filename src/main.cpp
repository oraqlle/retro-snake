#include <raylib.h>

#include <stdio.h>

// Global Constants
#define CELL_W 30  //< px
#define CELL_H 30  //< px
#define CELL_GAP 2 //< px

#define GRID_W 30 //< cell
#define GRID_H 30 //< cell
#define NUM_CELLS GRID_W *GRID_H

const int TARGET_FPS = 60;

const int SIDE_PANEL_W = 500;               //< px
const int SIDE_PANEL_H = (GRID_H * CELL_H); //< px

const int BOARD_W = GRID_W * CELL_W;
const int BOARD_H = SIDE_PANEL_H;

const int SCREEN_W = BOARD_W + SIDE_PANEL_W; //< px
const int SCREEN_H = SIDE_PANEL_H;           //< px

const Color BACKGROUND_COLOUR = {.r = 172, .g = 182, .b = 7, .a = 255};

const float SNAKE_CELL_W = CELL_W - CELL_GAP - CELL_GAP;
const float SNAKE_CELL_H = CELL_H - CELL_GAP - CELL_GAP;
const float SNAKE_CELL_OFFSET = CELL_W + CELL_GAP;

// Types
typedef struct {
    int x;
    int y;
} Vector2i;

typedef struct {
    unsigned x;
    unsigned y;
} Vector2u;

typedef enum { UP, DOWN, LEFT, RIGHT } Direction;

typedef struct {
    Vector2i positions[NUM_CELLS];
    unsigned length;
    Direction dir;
} Snake;

Snake snake;

Snake *init_snake(Snake *snake) {
    if (snake == NULL) {
        return NULL;
    }

    snake->dir = UP;
    snake->length = 2;

    snake->positions[0].x = 15;
    snake->positions[0].y = 15;

    snake->positions[1].x = 15;
    snake->positions[1].y = 16;

    for (unsigned idx = 2; idx < NUM_CELLS; idx++) {
        snake->positions[idx].x = -1;
        snake->positions[idx].y = -1;
    }

    return snake;
}

void draw_snake(Snake *snake) {
    for (unsigned idx = 0; idx < snake->length; idx++) {
        float screen_x = (float)(snake->positions[idx].x * CELL_W) + SNAKE_CELL_OFFSET;
        float screen_y = (float)(snake->positions[idx].y * CELL_H) + SNAKE_CELL_OFFSET;
        Rectangle rect = {
            .x = screen_x, .y = screen_y, .width = SNAKE_CELL_W, .height = SNAKE_CELL_H};
        DrawRectangleRec(rect, BLACK);
    }
}

static float time = 0.0f;
void update_snake(Snake *snake, float delta) {
    time += delta;

    if (time >= 0.5f) {

        time = 0.0f;

        for (unsigned idx = snake->length - 1; idx > 0; idx--) {
            Vector2i nxt_pos = snake->positions[idx - 1];
            snake->positions[idx].x = nxt_pos.x;
            snake->positions[idx].y = nxt_pos.y;
        }

        switch (snake->dir) {
            case UP:
                snake->positions[0].y -= 1;
                break;
            case DOWN:
                snake->positions[0].y += 1;
                break;
            case LEFT:
                snake->positions[0].x -= 1;
                break;
            case RIGHT:
                snake->positions[0].x += 1;
                break;
        }
    }
}

void draw_game_panel(void) {
    Rectangle board = {.x = 5, .y = 5, .width = BOARD_W - 10, .height = BOARD_H - 10};
    DrawRectangleLinesEx(board, 10, BLACK);
}

void draw_side_panel(void) {
    Rectangle board = {
        .x = BOARD_W, .y = 5, .width = SIDE_PANEL_W - 5, .height = SIDE_PANEL_H - 10};
    DrawRectangleLinesEx(board, 10, BLACK);
}

void input(void) {}

void update(float delta) { update_snake(&snake, delta); }

void draw(void) {
    draw_game_panel();
    draw_side_panel();
    draw_snake(&snake);
}

int main(void) {
    InitWindow(SCREEN_W, SCREEN_H, "Snake");
    SetTargetFPS(TARGET_FPS);

    init_snake(&snake);

    while (!WindowShouldClose()) {
        float delta = GetFrameTime();

        input();
        update(delta);

        BeginDrawing();
        ClearBackground(BACKGROUND_COLOUR);
        DrawFPS(0, 0);
        draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
