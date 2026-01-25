#ifndef PLAYER_H
#define PLAYER_H

#include "TextureManager.h"

class TextureManager;

class Player
{
public:
    explicit Player(TextureManager& textureManager);

    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

    void Update(float deltaTime);
    void Render(SDL_Renderer* renderer);

    void SetPosition(float x, float y);
    void SetVelocity(float vx, float vy);

    int getLives() const {return this->lives;};
    void decreaseLives();
    void increaseLives();
private:
    TextureManager& m_textures;
    SDL_Texture* m_texture = nullptr;

    float m_x = 100.0f;
    float m_y = 100.0f;
    float m_width = 32.0f;
    float m_height = 32.0f;

    float m_vx = 0.0f;
    float m_vy = 0.0f;

    int lives{};
};

#endif //PLAYER_H