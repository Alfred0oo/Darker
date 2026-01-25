#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include <string>
#include "SDL3/SDL.h"

class TextureManager;

class Level
{
public:
    explicit Level(TextureManager& textures);

    Level(const Level&) = delete;
    Level& operator=(const Level&) = delete;

    void Update(float deltaTime);
    void Render(SDL_Renderer* renderer);
private:
    TextureManager& m_textures;

    SDL_Texture* m_tileset = nullptr;
    struct Tile
    {
        float x, y;
        float width, height;
        int tileIndex;
    };
    std::vector<Tile> m_tiles;

    void LoadTiles();
};
#endif //LEVEL_H