#include "Application.h"
#include "SDL3/SDL.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
#include "Level.h"
#include "Player.h"

auto init_imgui(SDL_Window *window, SDL_Renderer *renderer) -> auto {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

  // Setup scaling
  float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
  ImGuiStyle &style = ImGui::GetStyle();
  style.ScaleAllSizes(
      main_scale); // Bake a fixed style scale. (until we have a
                   // solution for dynamic style scaling, changing this
                   // requires resetting Style + calling this again)
                   // makes this unnecessary. We leave both here for
                   // documentation purpose)
  style.FontScaleDpi = main_scale;

  style.FontSizeBase = 20.f;
  io.Fonts->AddFontDefault();

  ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
  ImGui_ImplSDLRenderer3_Init(renderer);
}

int main(int argc, char *argv[]) {

    // ImGui things
    // ImGui_ImplSDLRenderer3_NewFrame();
    // ImGui_ImplSDL3_NewFrame();
    // ImGui::NewFrame();
    // ImGui::ShowDemoWindow();
    // ImGui::Render();
    // ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);

  Application app;

  if (!app.Init()) return -1;
  app.Run();
  app.Shutdown();

  return 0;
}
