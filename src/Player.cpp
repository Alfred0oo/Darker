#include "Player.h"
#include "TextureManager.h"

Player::Player(TextureManager& textures, int windowHeight) : m_textures(textures), windowHeight(windowHeight), lives(3)
{
    m_texture = textures.GetTexture("C:/dev/Darker/assets/sprites/player.png");
}

void Player::SetPosition(float x, float y)
{
    m_x = x;
    m_y = y;
}

void Player::SetVelocity(float vx, float vy)
{
    m_vx = vx;
    m_vy = vy;
}

void Player::Update(float deltaTime)
{
    m_x += m_vx * deltaTime;
    m_y += m_vy * deltaTime;

    if (m_x < 0) m_x = 0;
    if (m_y < 0) m_y = 0;
    if (m_x + m_width > 1000) m_x = 1000 - m_width;
    if (m_y + m_height > 900) m_y = 900 - m_height;
}

void Player::Render(SDL_Renderer* renderer)
{
    if (!m_texture) return;

    SDL_FRect dst = { m_x, m_y, m_width, m_height };
    SDL_RenderTexture(renderer, m_texture, nullptr, &dst);
}

void Player::decreaseLives()
{
    lives--;
}

void Player::increaseLives()
{
    lives++;
}