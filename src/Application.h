#ifndef APPLICATION_H
#define APPLICATION_H
#include "Level.h"
#include "TextureManager.h"
#include "SDL3/SDL.h"

class Player;
class Level;

class Application
{
public:
    Application();
    ~Application();

    bool Init();
    void Render();
    void Run();
    void Shutdown();

private:
    void ProcessEvents();
    void Update(float deltaTime);
    void Render(float deltaTime);

    bool LoadResources() const;
    void ClearResources();

    float CalculateDeltaTime();
    void LimitFrameRate(float deltaTime);
private:
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    TextureManager* m_textures = nullptr;

    Player* m_player = nullptr;
    Level* m_level = nullptr;

    Uint64 m_lastCounter = 0;
    const Uint64 m_frequency = SDL_GetPerformanceFrequency();
    const float m_targetDelta = 1.0f / 60.0f;
};

#endif //APPLICATION_H