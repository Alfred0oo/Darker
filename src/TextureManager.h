#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <string>
#include <unordered_map>

#include "SDL3/SDL_render.h"

class TextureManager
{
public:
    TextureManager(SDL_Renderer *renderer);
    ~TextureManager();

    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;

    SDL_Texture* GetTexture(const std::string& path);

    void Clear();
private:
    SDL_Renderer *m_renderer;
    std::unordered_map<std::string, SDL_Texture*> m_textures;
};

#endif //TEXTUREMANAGER_H