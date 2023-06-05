#include "Actor.hpp"
#include "Color.hpp"
#include "Target.hpp"
#include "Window.hpp"
#include <iostream>
#include <cstdint>
#include <cmath>
#include <SFML/Window/Event.hpp>

int main(int argc, char *args[]) {
  Window w{sf::VideoMode(800, 800), "My Window"};
  Actor evader{10.f, Color::SeaColor}, pursuer{2.f, Color::CarrotOrange};
  Target target{sf::Vector2f{100.f, 50.f}, Color::SandColor};
  evader.setPos(350.f, 100.f);
  pursuer.setPos(200.f, 300.f);
  target.setPos(w.getSize().x - 200, 200);
  sf::Vector2f dest;
  for (int i = 0; i < target.getPointCount(); ++i) {
    sf::Vector2f point =
        sf::Vector2f{target.getPoint(i).x + target.getPos().x,
                     target.getPoint(i).y + target.getPos().y};
    std::cout << point.y << '\n';
    if (dest.x == 0 && dest.y == 0) {
      dest = point;
      continue;
    }
    sf::Vector2f vectorTo = point - evader.getPos();
    sf::Vector2f destPoint = dest - evader.getPos();
    double vectorToLength = std::pow(vectorTo.x, 2) + std::pow(vectorTo.y, 2);
    double destLength = std::pow(destPoint.x, 2) + std::pow(destPoint.y, 2);
    dest = vectorToLength < destLength ? point : dest;
  }
  std::cout << dest.x << ' ' << dest.y << '\n';
  sf::Event e;
  std::uint32_t count = 0;
  while (w.isOpen()) {
    count = count != -1 ? ++count : -1;
    while (w.pollEvent(e)) {
      if (e.type == sf::Event::Closed) {
        return EXIT_SUCCESS;
      }
    }
    w.clear(sf::Color::Black);
    float speed = 0.1f;
    sf::Vector2f eCurrentPosition = evader.getPos();
    auto l = [](double x, sf::Vector2f currentPosition, sf::Vector2f dest) {
      return (dest.y * (x - currentPosition.x) +
              currentPosition.y * (dest.x - x)) /
             (dest.x - currentPosition.x);
    };
    evader.setPos(eCurrentPosition.x + speed,
                       l(eCurrentPosition.x + speed, eCurrentPosition, dest));
    sf::Vector2f pCurrentPosition = pursuer.getPos();
    float xcord = pCurrentPosition.x < eCurrentPosition.x
                      ? pCurrentPosition.x + speed
                      : pCurrentPosition.x - speed;
    pursuer.setPos(xcord, l(xcord, pCurrentPosition, eCurrentPosition));
    w.draw(evader);
    w.draw(pursuer);
    w.draw(target);
    w.display();
  }
  return EXIT_SUCCESS;
}
