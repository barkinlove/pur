#include "Game.hpp"

int main(int argc, char *args[]) {
  Game& game = Game::instance();
  game.run();
  return EXIT_SUCCESS;
}
