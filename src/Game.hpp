#pragma once
#include "Actor.hpp"
#include "Config.hpp"
#include "Randomizer.hpp"
#include "Target.hpp"
#include "Window.hpp"
#include <SFML/Window/Event.hpp>
#include <random>

class Game
{
public:
  static Game& instance()
  {
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
  void init();
  void initTarget();
  void initActors();
  void initRandomizer();

private:
  Window m_window;
  Actor m_evader, m_pursuer, m_target;
  sf::Event m_event;
  const Config m_config;
  Randomizer m_randomizer;
};
