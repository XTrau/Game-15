#include "Game.h"

#include <ctime>
#include <cstdlib>
#include <string>

void Game::move(char direction) {
    int ni = current_i, nj = current_j;
    switch (direction) {
        case 'u':
            ni++;
            break;
        case 'd':
            ni--;
            break;
        case 'l':
            nj++;
            break;
        case 'r':
            nj--;
            break;
        default:
            break;
    }

    if (ni >= 0 && ni < game_field.size() && nj >= 0 && nj < game_field[ni].size()) {
        std::swap(game_field[current_i][current_j], game_field[ni][nj]);
        current_i = ni;
        current_j = nj;
    }
}

void Game::shuffleField(int count) {
    srand(time(0));
    char directions[4]{
        'u', 'd', 'l', 'r'
    };
    for (int i = 0; i < count; i++) {
        int index = rand() % 4;
        move(directions[index]);
    }
}

void Game::drawField() const {
    for (int i = 0; i < game_field.size() + 1; i++) {
        DrawRectangle(0, i * (FIELD_SIZE + WALL_SIZE), SCREEN_WIDTH, WALL_SIZE, WALL_COLOR);
    }
    for (int i = 0; i < game_field.size() + 1; i++)
        DrawRectangle(i * (FIELD_SIZE + WALL_SIZE), 0, WALL_SIZE, SCREEN_HEIGHT, WALL_COLOR);
}

void Game::drawNumbers() const {
    for (int i = 0; i < game_field.size(); i++) {
        for (int j = 0; j < game_field[i].size(); j++) {
            if (game_field[i][j] == -1)
                continue;

            const int x = j * (FIELD_SIZE + WALL_SIZE) + WALL_SIZE;
            const int y = i * (FIELD_SIZE + WALL_SIZE) + WALL_SIZE;
            DrawRectangle(x, y, FIELD_SIZE, FIELD_SIZE, NUMBER_BACKGROUND);

            const char *text = std::to_string(game_field[i][j]).c_str();
            const int text_x = x + FIELD_SIZE / 2 - FONT_SIZE / 4;
            const int text_y = y + FIELD_SIZE / 2 - FONT_SIZE / 4;
            DrawText(text, text_x, text_y, FONT_SIZE, NUMBER_COLOR);
        }
    }
}

Game::Game() {
    game_field.resize(FIELD_COUNT, std::vector<int>(FIELD_COUNT));
    current_i = 3;
    current_j = 3;
    for (int i = 0; i < game_field.size(); i++)
        for (int j = 0; j < game_field.size(); j++)
            game_field[i][j] = i * 3 + j + i + 1;
    game_field[3][3] = -1;
    shuffleField(100);
}

void Game::run() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game 15");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(WHITE);
        drawField();
        drawNumbers();

        if (IsKeyPressed(KEY_UP)) {
            move('u');
        } else if (IsKeyPressed(KEY_DOWN)) {
            move('d');
        } else if (IsKeyPressed(KEY_LEFT)) {
            move('l');
        } else if (IsKeyPressed(KEY_RIGHT)) {
            move('r');
        }

        EndDrawing();
    }
    CloseWindow();
}
