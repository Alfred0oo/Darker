#include "Application.h"
#include "Player.h"
#include "Level.h"

#include "SDL3_image/SDL_image.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_timer.h"
#include "iostream"

Application::Application() :
m_window(nullptr),
m_renderer(nullptr),
m_textures(nullptr),
m_player(nullptr),
m_level(nullptr),
m_lastCounter(SDL_GetPerformanceCounter())
{
}

Application::~Application()
{
    Shutdown();
}

bool Application::Init()
{
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
    {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }
    bool success = SDL_CreateWindowAndRenderer(
          "The Dark Game", 1000, 900, SDL_WINDOW_RESIZABLE, &m_window, &m_renderer);

    if (success == false) {
        SDL_Log("Failed to initialize window or renderer: %s", SDL_GetError());
        return false;
    }

    m_textures = new TextureManager(m_renderer);

    if (!LoadResources())
    {
        SDL_Log("Failed to load resources: %s", SDL_GetError());
        return false;
    }

    m_player = new Player(*m_textures);
    m_level = new Level(*m_textures);

    return true;
}

void Application::Run()
{
    bool running = true;
    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_EVENT_QUIT:
                running = false;
            case SDL_EVENT_KEY_DOWN:
                if (event.key.key == SDLK_ESCAPE)
                {
                    running = false;
                }
            }
        }
        float deltaTime = CalculateDeltaTime();

        Update(deltaTime);

        SDL_SetRenderDrawColor(m_renderer, 0x8f, 0xd3, 0xff, 255);
        SDL_RenderClear(m_renderer);

        Render();

        SDL_RenderPresent(m_renderer);

        LimitFrameRate(deltaTime);
    }
}

void Application::Shutdown()
{
    ClearResources();

    if (m_renderer)
    {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }

    if (m_window)
    {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
    SDL_Quit();
}

void Application::Update(float deltaTime)
{
    if (m_level) m_level->Update(deltaTime);
    if (m_player) m_player->Update(deltaTime);
}

void Application::Render()
{
    if (m_level) m_level->Render(m_renderer);
    if (m_player) m_player->Render(m_renderer);
}

bool Application::LoadResources() const
{
    if (!m_textures->GetTexture("C:/dev/Darker/assets/sprites/player.png") ||
        !m_textures->GetTexture("C:/dev/Darker/assets/tiles/grass_block.png"))
    {
        return false;
    }

    return true;
}

void Application::ClearResources()
{
    delete m_player;
    m_player = nullptr;

    delete m_level;
    m_level = nullptr;

    delete m_textures;
    m_textures = nullptr;
}

float Application::CalculateDeltaTime()
{
    Uint64 current = SDL_GetPerformanceCounter();
    float delta = static_cast<float>(current - m_lastCounter) / m_frequency;
    m_lastCounter = current;

    if (delta > 0.1f) delta = 0.1f;

    return delta;
}

void Application::LimitFrameRate(float deltaTime)
{
    if (deltaTime > m_targetDelta)
    {
        Uint64 delayMs = static_cast<Uint32>((m_targetDelta - deltaTime) * 1000.0f);
        SDL_Delay(delayMs);
    }
}