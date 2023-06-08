#include "CollisionSystem.hpp"
#include "Actor.hpp"
#include <SFML/Graphics/Rect.hpp>

bool CollisionSystem::collide(Actor first, Actor second) {
  sf::FloatRect first_bounds = first.getShape().getGlobalBounds();
  sf::FloatRect second_bounds = second.getShape().getGlobalBounds();
  return first_bounds.intersects(second_bounds);
}
