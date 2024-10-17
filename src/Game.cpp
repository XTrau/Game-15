#include "Game.h"

#include <ctime>
#include <cstdlib>
#include <string>

Game::Game() {
    game_field.resize(FIELD_COUNT, std::vector<int>(FIELD_COUNT));
    current_i = 3;
    current_j = 3;
    for (int i = 0; i < game_field.size(); i++)
        for (int j = 0; j < game_field.size(); j++)
            game_field[i][j] = i * 3 + j + i + 1;
    game_field[3][3] = -1;
    shuffleField();
}

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

void Game::shuffleField() {
    srand(time(nullptr));
    char directions[4]{
        'u', 'd', 'l', 'r'
    };
    for (int i = 0; i < SHUFFLE_COUNT; i++) {
        const int index = rand() % 4;
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
            const int text_x = x + FIELD_SIZE / 2 + WALL_SIZE / 2 - FONT_SIZE / 2;
            const int text_y = y + FIELD_SIZE / 2 + WALL_SIZE / 2 - FONT_SIZE / 2;
            DrawText(text, text_x, text_y, FONT_SIZE, NUMBER_COLOR);
        }
    }
}

bool Game::checkWin() const {
    for (int i = 0; i < game_field.size(); i++) {
        for (int j = 0; j < game_field[i].size(); j++) {
            if (i == game_field.size() - 1 && j == game_field[i].size() - 1)
                continue;
            int need_num = i * 3 + j + i + 1;
            if (game_field[i][j] != need_num)
                return false;
        }
    }


    return true;
}

void Game::restartGame() {
    shuffleField();
}

void Game::drawWin() const {
    std::string congrats1 = "Congratulations! You have won!";
    std::string congrats2 = "Press R to play again or ESC to exit the game";
    DrawText(
        congrats1.c_str(),
        SCREEN_WIDTH / 2 - FONT_SIZE * static_cast<int>(congrats1.size()) / 4,
        SCREEN_HEIGHT / 2 - FONT_SIZE,
        FONT_SIZE,
        NUMBER_COLOR
    );
    DrawText(
        congrats2.c_str(),
        SCREEN_WIDTH / 2 - FONT_SIZE * static_cast<int>(congrats2.size()) / 8,
        SCREEN_HEIGHT / 2 + FONT_SIZE,
        FONT_SIZE / 2,
        NUMBER_COLOR
    );
}


void Game::run() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game 15");
    Image gameIcon = LoadImage("../assets/gameIcon.png");
    SetWindowIcon(gameIcon);
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(WHITE);

        if (checkWin()) {
            drawWin();

            if (IsKeyPressed(KEY_R)) {
                restartGame();
            }

            EndDrawing();
            continue;
        }

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
