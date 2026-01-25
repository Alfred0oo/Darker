#include "TextureManager.h"

#include <SDL3_image/SDL_image.h>

TextureManager::TextureManager(SDL_Renderer* renderer) : m_renderer(renderer)
{

}

TextureManager::~TextureManager()
{
    Clear();
}

SDL_Texture* TextureManager::GetTexture(const std::string& path)
{
    auto it = m_textures.find(path);
    if (it != m_textures.end())
    {
        return it->second;
    }

    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface)
    {
        SDL_Log("TextureManager: Failed to load '%s': %s",
        path.c_str(), SDL_GetError());
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
    SDL_DestroySurface(surface);

    if (!texture)
    {
        SDL_Log("TextureManager: Failed to create texture '%s': %s", path.c_str(), SDL_GetError());
        return nullptr;
    }

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    m_textures[path] = texture;

    return texture;
}

void TextureManager::Clear()
{
    for (auto& pair : m_textures)
    {
        SDL_DestroyTexture(pair.second);
    }

    m_textures.clear();
}
