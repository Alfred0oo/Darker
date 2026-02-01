#ifndef DARK_GAME_INPUT_H
#define DARK_GAME_INPUT_H
#include "Player.h"

class InputHandler {
public:
    InputHandler();

    static void HandleInputs(const bool keyStates[], Player& player);
private:
    int lastKey = 0;
};

#endif //DARK_GAME_INPUT_H
