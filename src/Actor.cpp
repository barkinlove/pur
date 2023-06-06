#include "Actor.hpp"

Actor::Actor(float size, sf::Color color) : Object(size, color) {}

std::vector<sf::CircleShape> Actor::getTrajectory(sf::Vector2f origin, sf::Vector2f end, std::function<float(float x, sf::Vector2f, sf::Vector2f)> strategy) {
	std::vector<sf::CircleShape> trajectory;
	std::size_t count = 50;
	trajectory.reserve(count);
	float step = (end.x - origin.x) / count;
	float x = origin.x;
	float y = origin.y;
	for (std::size_t i = 0; i < count; ++i) {
		sf::CircleShape trace{ 1.f };
		x += step;
		y = strategy(x, origin, end);
		trace.setPosition(x, y);
		trajectory.push_back(std::move(trace));
	}
	return trajectory;
}
