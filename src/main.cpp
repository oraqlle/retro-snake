#include "timer.h"

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

const int BOARD_MARGIN = 20; //< px gap between the border and the play grid

const int SIDE_PANEL_W = 500; //< px

const int BOARD_W = GRID_W * CELL_W + 2 * BOARD_MARGIN;
const int BOARD_H = GRID_H * CELL_H + 2 * BOARD_MARGIN;

const int SIDE_PANEL_H = BOARD_H; //< px

const int SCREEN_W = BOARD_W + SIDE_PANEL_W; //< px
const int SCREEN_H = BOARD_H;                //< px

const Color BACKGROUND_COLOUR = {.r = 172, .g = 182, .b = 7, .a = 255};

const float SNAKE_CELL_W = CELL_W - CELL_GAP - CELL_GAP;
const float SNAKE_CELL_H = CELL_H - CELL_GAP - CELL_GAP;
const float SNAKE_CELL_OFFSET = BOARD_MARGIN;

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
Vector2i food;

bool is_on_snake(Snake *snake, int x, int y) {
    for (unsigned idx = 0; idx < snake->length; idx++) {
        if (snake->positions[idx].x == x && snake->positions[idx].y ==y) {
            return true;
        }
    }
    return false;
}

void spawn_food(void) {
    do {
        food.x = GetRandomValue(0, GRID_W - 1);
        food.y = GetRandomValue(0, GRID_H - 1);
    } while (
        is_on_snake(&snake, food.x, food.y)
    );
}

void draw_food(void) {
    float screen_x = food.x * CELL_W + SNAKE_CELL_OFFSET;
    float screen_y = food.y * CELL_H + SNAKE_CELL_OFFSET;
 Rectangle rect = {
            .x = screen_x, .y = screen_y, .width = SNAKE_CELL_W, .height = SNAKE_CELL_H};
    DrawRectangleRec(rect, RED);
    
}

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

static float time_since_move = 0.0f;
void update_snake(Snake *snake, float delta) {
    time_since_move += delta;

    if (time_since_move >= 0.15f) {

        Vector2i old_tail = snake->positions[snake->length - 1];
        time_since_move = 0.0f;

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

        if (snake->positions[0].x == food.x && snake->positions[0].y == food.y) {
            snake->positions[snake->length] = old_tail;
            snake->length += 1;
            spawn_food();
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

void input(void) {
    //UP
    if ((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) && snake.dir != DOWN) {
        snake.dir = UP;
    }
    //DOWN
    else if((IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) && snake.dir != UP) {
        snake.dir = DOWN;
    }
    //LEFT
    else if((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && snake.dir != RIGHT) {
        snake.dir = LEFT;
    }
    //RIGHT
    else if((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) && snake.dir != LEFT) {
        snake.dir = RIGHT;
    }
}

void update(float delta) { update_snake(&snake, delta); }

void draw(void) {
    draw_game_panel();
    draw_side_panel();
    draw_snake(&snake);
    draw_food();
}

int main(void) {
    InitWindow(SCREEN_W, SCREEN_H, "Snake");
    SetTargetFPS(TARGET_FPS);

    init_snake(&snake);
    spawn_food();

    while (!WindowShouldClose()) {
        float delta = GetFrameTime();

        input();

        Timer t;
        update(delta);
        double update_ms = t.elapsed_ms();

        BeginDrawing();
        ClearBackground(BACKGROUND_COLOUR);
        DrawText(TextFormat("update: %.3f ms", update_ms), BOARD_W + 20, 40, 20, BLACK);
        DrawFPS(0, 0);
        draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
