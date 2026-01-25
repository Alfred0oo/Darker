#include "Level.h"
#include "TextureManager.h"

Level::Level(TextureManager& textures) : m_textures(textures)
{
    m_tileset = m_textures.GetTexture("C:/dev/Darker/assets/tiles/grass_block.png");

    LoadTiles();
}

void Level::LoadTiles()
{
    const int cols = 1;
    const int rows = 1;

    for (int y = 0; y < rows; ++y)
    {
        for (int x = 0; x < cols; ++x)
        {
            const float tileSize = 32.0f;
            Tile t;
            t.x = x * tileSize;
            t.y = y * tileSize;
            t.width = tileSize;
            t.height = tileSize;
            t.tileIndex = 0; // only one tile for now
            m_tiles.push_back(t);
        }
    }
}

void Level::Update(float deltaTime)
{
    // For now, the level is static
    // Could animate tiles, scroll background, or update enemies
}

void Level::Render(SDL_Renderer* renderer)
{
    if (!m_tileset) return;

    for (const auto& tile : m_tiles)
    {
        SDL_FRect dst = { tile.x, tile.y, tile.width, tile.height };
        SDL_RenderTexture(renderer, m_tileset, nullptr, &dst);
    }
}
