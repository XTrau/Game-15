#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include <vector>


class Game {
    const int SCREEN_WIDTH = 810, SCREEN_HEIGHT = 810;
    const int WALL_SIZE = 10;
    const int FIELD_SIZE = 190;
    const int FONT_SIZE = 48;
    const int FIELD_COUNT = 4;

    const Color WALL_COLOR = BLACK;
    const Color NUMBER_COLOR = BLACK;
    const Color NUMBER_BACKGROUND = WHITE;


    std::vector<std::vector<int> > game_field;
    int current_i, current_j;

    void move(char direction);

    void shuffleField(int count);

    void drawField() const;

    void drawNumbers() const;

public:
    Game();

    void run();
};


#endif //GAME_H
