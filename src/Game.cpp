#include "Game.hpp"
#include "CollisionSystem.hpp"
#include "Color.hpp"
#include "Randomizer.hpp"
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <nlohmann/json.hpp>

Game::Game()
  : m_window{ sf::VideoMode(1200, 1000), "Pursuit game" }
  , m_evader{ 10.f, Color::SeaColor }
  , m_pursuer{ 8.f, Color::CarrotOrange }
  , m_target{ 60.f, Color::SandColor }
  , m_config{ "config.json" }
{
  init();
}

void Game::init()
{
  initTarget();
  initRandomizer();
  initActors();
}

void Game::initTarget()
{
  std::cout << m_window.getSize().x << ' ' << m_window.getSize().y << '\n';
  float target_x =
    m_window.getSize().x - static_cast<float>(m_window.getSize().x) / 2 - 60.f;
  float target_y =
    m_window.getSize().y - static_cast<float>(m_window.getSize().y) / 2 - 60.f;
  m_target.setPos(target_x, target_y);
  std::cout << "Target has been initialized.\n";
}

void Game::initActors()
{
  sf::Vector2f evaderOrigin = m_randomizer.get();
  sf::Vector2f pursuerOrigin = m_randomizer.get();
  m_evader.setPos(evaderOrigin.x, evaderOrigin.y);
  m_pursuer.setPos(pursuerOrigin.x, pursuerOrigin.y);
  std::cout << "Actors have been initalized.\n";
}

void Game::initRandomizer()
{
  m_randomizer.setBounds(0, m_window.getSize().x - 400.f, 0, m_window.getSize().y - 200.f);
  float offset = 50.f;
  m_randomizer.setExcludeZone(
    { m_target.getPos().x - offset, m_target.getPos().y - offset },
    { m_target.getPos().x + 2 * m_target.getShape().getRadius() + offset,
      m_target.getPos().y + 2 * m_target.getShape().getRadius() + offset });
  std::cout << "Randomizer has been initialized.\n";
}

sf::Vector2f Game::getNearestPath() const
{
  return sf::Vector2f{ m_target.getPos().x, m_target.getPos().y + 60.f };
}

float Game::getDistance(sf::Vector2f origin, sf::Vector2f end)
{
  sf::Vector2f distance = end - origin;
  return distance.x * distance.x + distance.y * distance.y;
}

namespace {
bool almostEqual(sf::Vector2f first, sf::Vector2f second)
{
  float eps = 0.1f;
  return std::abs(first.x - second.x) <= eps ||
         std::abs(first.y - second.y) < eps;
}

float getSign(sf::Vector2f first, sf::Vector2f second)
{
  return first.x > second.x ? -1 : 1;
}
}

void Game::run()
{
  auto move = [](float x, sf::Vector2f currentPosition, sf::Vector2f dest) {
    return (dest.y * (x - currentPosition.x) +
            currentPosition.y * (dest.x - x)) /
           (dest.x - currentPosition.x);
  };

  sf::Vector2f dest = getNearestPath();

  bool charge = false;
  m_window.loop([this, move, dest, charge]() mutable {
    if (CollisionSystem::collide(m_evader, m_pursuer) ||
        CollisionSystem::collide(m_evader, m_target)) {
      return;
    }
    sf::Vector2f eCurrentPosition = m_evader.getPos();
    float xcord =
      eCurrentPosition.x + getSign(eCurrentPosition, dest) * m_config.speed;
    m_evader.setPos(
      xcord, move(xcord, eCurrentPosition, dest));

    float newX = (dest.x + m_evader.getPos().x) / 2;
    float newY = move(newX, m_evader.getPos(), dest);
    sf::Vector2f optimal_dest = sf::Vector2f{ newX, newY };

    sf::Vector2f pCurrentPosition = m_pursuer.getPos();
    xcord = pCurrentPosition.x +
            getSign(pCurrentPosition, eCurrentPosition) * m_config.speed;

    if (charge || almostEqual(m_pursuer.getPos(), optimal_dest)) {
      charge = true;
      m_pursuer.setPos(xcord, move(xcord, pCurrentPosition, eCurrentPosition));
      m_window.drawTrajectory(m_pursuer, pCurrentPosition, optimal_dest, move);
    } else {
      m_pursuer.setPos(xcord, move(xcord, pCurrentPosition, optimal_dest));
      m_window.drawTrajectory(m_pursuer, pCurrentPosition, optimal_dest, move);
    }

    Actor dest_area{ 5.f, sf::Color::White };
    dest_area.setPos(optimal_dest.x, optimal_dest.y - 2.5f);
    m_window.draw(dest_area);
    m_window.draw(m_evader);
    m_window.drawTrajectory(m_evader, eCurrentPosition, dest, move);
    m_window.draw(m_pursuer);
    m_window.draw(m_target);
    m_window.display();
  });
}

Game::~Game() {}
