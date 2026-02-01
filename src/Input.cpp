#include "Input.h"
#include "Player.h"
#include "SDL3/SDL_scancode.h"


InputHandler::InputHandler() {};

void InputHandler::HandleInputs(const bool keyStates[], Player &player)
{
    if (keyStates[SDL_SCANCODE_A] && !keyStates[SDL_SCANCODE_D])
    {
        player.SetXVelocity(-100.0f);
    }
    else if (keyStates[SDL_SCANCODE_D] && !keyStates[SDL_SCANCODE_A])
    {
        player.SetXVelocity(100.0f);
    }
    else {
        player.SetXVelocity(0.0f);
    }
    if (keyStates[SDL_SCANCODE_SPACE] && !player.IsJumping())
    {
        player.jump();
    }
}