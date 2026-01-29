#ifndef DARK_GAME_LEVEL_H
#define DARK_GAME_LEVEL_H
#include <vector>
#include <string>
#include "SDL3/SDL.h"

class TextureManager;

class Level
{
public:
    explicit Level(TextureManager& textures, int length, int windowHeight);

    Level(const Level&) = delete;
    Level& operator=(const Level&) = delete;

    void Update(float deltaTime);
    void Render(SDL_Renderer* renderer);
private:
    TextureManager& m_textures;
    int length;
    int windowHeight;

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
#endif //DARK_GAME_LEVEL_H