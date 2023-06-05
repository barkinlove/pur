#pragma once
#include "Object.hpp"
#include <SFML/Graphics/CircleShape.hpp>

class Actor final : public Object<sf::CircleShape, float> {
public:
  Actor(float size, sf::Color color);
};
