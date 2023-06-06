#pragma once
#include "Object.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <functional>

class Actor final : public Object<sf::CircleShape, float> {
public:
	Actor(float size, sf::Color color);
	std::vector<sf::CircleShape> getTrajectory(sf::Vector2f origin, sf::Vector2f end, std::function<float(float x, sf::Vector2f, sf::Vector2f)> strategy);
};
