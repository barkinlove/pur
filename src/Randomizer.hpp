#pragma once
#include <SFML/System/Vector2.hpp>
#include <random>

class Randomizer final
{
public:
  Randomizer();
  sf::Vector2f get();

  void setBounds(float xFrom, float xTo, float yFrom, float yTo);
  void setExcludeZone(sf::Vector2f left, sf::Vector2f right);

private:
  bool in(sf::Vector2f);
  float generateX();
  float generateY();

private:
  std::mt19937 m_twister;
  std::uniform_real_distribution<float> m_xDistribution;
  std::uniform_real_distribution<float> m_yDistribution;
  sf::Vector2f m_leftExcludeZoneCord, m_rightExcludeZoneCord;
};
