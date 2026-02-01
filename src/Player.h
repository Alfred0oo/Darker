#ifndef DARK_GAME_PLAYER_H
#define DARK_GAME_PLAYER_H

#include "TextureManager.h"

class TextureManager;

class Player
{
public:
    explicit Player(TextureManager& textureManager, int windowHeight, int windowWidth);

    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

    void Update(float deltaTime);
    void Render(SDL_Renderer* renderer, int frame);

    void SetPosition(float x, float y);
    void SetVelocity(float vx, float vy);
    void SetXVelocity(float vx);
    void SetYVelocity(float vy);

    void SetFacing(SDL_FlipMode facing) { m_facing = facing; }

    void jump();
    [[nodiscard]] bool IsJumping() const { return inAir; };

    [[nodiscard]] int getLives() const {return this->lives;};
    void decreaseLives();
    void increaseLives();
private:
    TextureManager& m_textures;
    SDL_Texture* m_texture = nullptr;
    int windowHeight;
    int windowWidth;

    float m_width = 96.0f;
    float m_height = 96.0f;
    float m_x = 0.0f;
    float m_y = static_cast<float>(windowHeight - m_height - 32);

    float m_vx = 0.0f;
    float m_vy = 0.0f;

    SDL_FlipMode m_facing = SDL_FLIP_NONE;
    bool inAir = false;

    int lives{};
};

#endif //DARK_GAME_PLAYER_H