#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <cstdlib>
#include <iostream>

constexpr std::uint32_t g_screenWidth = 640;
constexpr std::uint32_t g_screenHeight = 480;

SDL_Window* g_pWindow = nullptr;
SDL_Surface* g_pSurface = nullptr;
SDL_Surface* g_pPicture = nullptr;
std::string g_path = "assets/hello_world.bmp";

bool init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SLD cound not initialize! SDL_ERROR: " << SDL_GetError()
              << '\n';
    return false;
  }
  g_pWindow = SDL_CreateWindow("tutorial", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, g_screenWidth,
                               g_screenHeight, SDL_WINDOW_SHOWN);
  if (!g_pWindow) {
    std::cout << "Window cound not be created!\n";
    return EXIT_FAILURE;
  }
  g_pSurface = SDL_GetWindowSurface(g_pWindow);
  return true;
}

bool loadMedia(std::string path) {
  g_pPicture = SDL_LoadBMP(path.c_str());
  if (!g_pPicture) {
    std::cout << "Unable to load an image! SDL Error: " << SDL_GetError() << '\n';
    std::cout << "Image file: " << path << '\n';
    return false;
  }
  return true;
}

void close() {
  SDL_FreeSurface(g_pPicture);
  g_pPicture = nullptr;
  SDL_DestroyWindow(g_pWindow);
  g_pWindow = nullptr;
  SDL_Quit();
}

int main(int argc, char *args[]) {
  if (!init()) {
    return EXIT_FAILURE;
  }
  if (!loadMedia(g_path)) {
    return EXIT_FAILURE;
  }
  SDL_BlitSurface(g_pPicture, nullptr, g_pSurface, nullptr);
  SDL_UpdateWindowSurface(g_pWindow);
  SDL_Event e;
  bool quit = false;
  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }
  }
  close();
  return EXIT_SUCCESS;
}
