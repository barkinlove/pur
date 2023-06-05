#pragma once
#include "Object.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

class Target final : public Object<sf::RectangleShape, sf::Vector2f> {
public:
  Target(sf::Vector2f size, sf::Color color);

  std::size_t getPointCount() const noexcept {
    return m_baseShape.getPointCount();
  }

  sf::Vector2f getPoint(std::size_t idx) const noexcept {
    return m_baseShape.getPoint(idx);
  }
};
