#include "Randomizer.hpp"
#include <iostream>
#include <SFML/System/Vector2.hpp>

Randomizer::Randomizer()
  : m_twister{ std::random_device{}() }
{
}

void Randomizer::setBounds(float xFrom, float xTo, float yFrom, float yTo)
{
  m_xDistribution = std::uniform_real_distribution<float>{ xFrom, xTo };
  m_yDistribution = std::uniform_real_distribution<float>{ yFrom, yTo };
}

void Randomizer::setExcludeZone(sf::Vector2f left, sf::Vector2f right)
{
  m_leftExcludeZoneCord = left;
  m_rightExcludeZoneCord = right;
}

bool Randomizer::in(sf::Vector2f point)
{
  bool lessThanLeft =
    point.x <= m_rightExcludeZoneCord.x && point.y <= m_rightExcludeZoneCord.y;
  bool greaterThanRight =
    point.x >= m_leftExcludeZoneCord.x && point.y >= m_leftExcludeZoneCord.y;
  return lessThanLeft && greaterThanRight;
}

float Randomizer::generateX()
{
  return m_xDistribution(m_twister);
}

float Randomizer::generateY()
{
  return m_yDistribution(m_twister);
}

sf::Vector2f Randomizer::get()
{
  float x = generateX();
  float y = generateY();
  sf::Vector2f point{ x, y };
  int i = 0;
  while (true) {
    if (in(point)) {
      point = {generateX(), generateY()};
      continue;
    }
    break;
  }
  return point;
}
