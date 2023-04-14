#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <cstdlib>
#include <iostream>

constexpr int g_screenWidth = 640;
constexpr int g_screenHeight = 480;

int main(int argc, char *args[]) {
  SDL_Window *pWindow = nullptr;
  SDL_Surface *pSurface = nullptr;
  if (SDL_Init(SDL_INIT_VIDEO)) {
    std::cout << "SLD cound not initialize! SDL_ERROR: " << SDL_GetError()
              << '\n';
    return EXIT_FAILURE;
  }
  pWindow = SDL_CreateWindow("tutorial", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, g_screenWidth,
                             g_screenHeight, SDL_WINDOW_SHOWN);
  if (!pWindow) {
    std::cout << "Window cound not be created!\n";
    return EXIT_FAILURE;
  }

  pSurface = SDL_GetWindowSurface(pWindow);
  SDL_FillRect(pSurface, nullptr, SDL_MapRGB(pSurface->format, 0xff, 0xff, 0xff));
  SDL_UpdateWindowSurface(pWindow);
  SDL_Event e;
  bool quit = false;
  while (quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT)
        quit = true;
    }
  }
  SDL_DestroyWindow(pWindow);
  SDL_Quit();
  return EXIT_SUCCESS;
}
