#pragma once
#include "Window.hpp"
#include "Actor.hpp"
#include "Target.hpp"
#include <SFML/Window/Event.hpp>

class Game {
public:
  static Game& instance() {
    static Game s_game;
    return s_game;
  }
  Game(const Game&) = delete;
  Game& operator=(const Game&) = delete;

  void run();
  sf::Vector2f getNearestPath() const; 
  float getDistance(sf::Vector2f origin, sf::Vector2f end);

private:
  Game();
  ~Game();

private:
  Window m_window;
  Actor m_evader, m_pursuer;
  Target m_target;
  sf::Event m_event;

  static const float s_speed;
};
