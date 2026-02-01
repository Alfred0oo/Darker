#include "Application.h"
#include "Player.h"
#include "Level.h"
#include "Input.h"

#include "SDL3_image/SDL_image.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_timer.h"
#include "iostream"

#define WIDTH 1280
#define HEIGHT 720

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
          "The Dark Game", WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE, &m_window, &m_renderer);

    SDL_SetRenderVSync(m_renderer, -1);

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

    m_player = new Player(*m_textures, HEIGHT, WIDTH);
    m_level = new Level(*m_textures, 100, HEIGHT);
    m_inputs = new InputHandler();

    return true;
}

void Application::Run()
{
    bool running = true;
    SDL_Event event;
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;

    while (running)
    {
        frameStart = SDL_GetTicks();
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT || event.key.key == SDLK_ESCAPE)
            {
                running = false;
            }
        }

        const bool* keyStates = SDL_GetKeyboardState(nullptr);
        m_inputs->HandleInputs(keyStates, *m_player);

        float deltaTime = CalculateDeltaTime();

        Update(deltaTime);

        SDL_SetRenderDrawColor(m_renderer, 0x8f, 0xd3, 0xff, 255);
        SDL_RenderClear(m_renderer);

        Render();

        SDL_RenderPresent(m_renderer);
        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < frameDelay)
        {
            SDL_Delay(frameDelay - frameTime);
        }
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
    Uint32 frame = SDL_GetTicks() / 250 % 4;
    if (m_level) m_level->Render(m_renderer);
    if (m_player) m_player->Render(m_renderer, frame);
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