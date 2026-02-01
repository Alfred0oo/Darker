#include "Player.h"
#include "TextureManager.h"
#include  "Constants.h"
#include "SDL3/SDL_log.h"

const float jumpVelocity = -400.0f; // default value = 192
const float gravity = -jumpVelocity / 15;

Player::Player(TextureManager& textures, int windowHeight, int windowWidth) : m_textures(textures), windowHeight(windowHeight), windowWidth(windowWidth), lives(3)
{
    m_texture = textures.GetTexture("C:/dev/Darker/assets/sprites/sprite.png");
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

void Player::SetXVelocity(float vx)
{
    m_vx = vx;
}

void Player::SetYVelocity(float vy)
{
    m_vy = vy;
}

void Player::jump() {
    m_vy = jumpVelocity;
    inAir = true;
}

void Player::Update(float deltaTime)
{
    m_x += m_vx * deltaTime;
    m_vy += gravity;
    m_y += m_vy * deltaTime;

    if (m_x < 0 - m_width / 2) m_x = 0 - m_width / 2;
    if (m_y < 0) m_y = 0;
    if (m_x + m_width / 2 > windowWidth) m_x = windowWidth - m_width / 2;
    if (m_y + m_height > windowHeight - g_BLOCKSIZE)
    {
        m_y = windowHeight - m_height - g_BLOCKSIZE;
        inAir = false;
    }
    SDL_Log("%f\n", deltaTime);
}

void Player::Render(SDL_Renderer* renderer, int frame)
{
    if (!m_texture) return;

    SDL_FRect dst = { m_x, m_y, m_width, m_height };
    SDL_FRect src = {0.0f, 0, m_width, m_height};
    if (m_vx > 0)
    {
        src = {frame * m_width, 0, m_width, m_height};
        SetFacing(SDL_FLIP_NONE);
    }
    else if (m_vx < 0)
    {
        src = {frame * m_width, 0, m_width, m_height};
        SetFacing(SDL_FLIP_HORIZONTAL);
    }
    SDL_RenderTextureRotated(renderer, m_texture, &src, &dst, 0, 0, m_facing);
}

void Player::decreaseLives()
{
    lives--;
}

void Player::increaseLives()
{
    lives++;
}