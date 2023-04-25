#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <optional>

struct Color {
  static const sf::Color CarrotOrange;
  static const sf::Color SeaColor;
  static const sf::Color SandColor;
};

const sf::Color Color::CarrotOrange{237, 145, 33, 255};
const sf::Color Color::SeaColor{54, 186, 179, 255};
const sf::Color Color::SandColor{194, 178, 128, 255};

int main(int argc, char *args[]) {
  sf::RenderWindow window(sf::VideoMode(800, 800), "My Window");
  sf::View view = window.getDefaultView();
  view.setSize(800, -800);
  //view.setCenter(0, window.getSize().y);
  window.setView(view);
  sf::CircleShape evader{10.f}, pursuer{2.f};
  sf::RectangleShape target{sf::Vector2f{100, 50}};
  evader.setFillColor(Color::SeaColor);
  pursuer.setFillColor(Color::CarrotOrange);
  target.setFillColor(Color::SandColor);
  evader.setPosition(350.f, 100.f);
  pursuer.setPosition(200.f, 300.f);
  target.setPosition(window.getSize().x - 200, 200);
  sf::Vector2f dest;
  for (int i = 0; i < target.getPointCount(); ++i) {
      sf::Vector2f point = sf::Vector2f{ target.getPoint(i).x + target.getPosition().x, target.getPoint(i).y + target.getPosition().y };
      std::cout << point.y << '\n';
      if (dest.x == 0 && dest.y == 0) {
          dest = point;
          continue;
      }
      sf::Vector2f vectorTo = point - evader.getPosition();
      sf::Vector2f destPoint = dest - evader.getPosition();
      double vectorToLength = std::pow(vectorTo.x, 2) + std::pow(vectorTo.y, 2);
      double destLength = std::pow(destPoint.x, 2) + std::pow(destPoint.y, 2);
      dest = vectorToLength < destLength ? point : dest;
  }
  std::cout << dest.x << ' ' << dest.y << '\n';
  sf::Event e;
  int count = 0;
  while (window.isOpen()) {
    count = count != -1 ? ++count : -1;
    while (window.pollEvent(e)) {
      if (e.type == sf::Event::Closed) {
        window.close();
        return EXIT_SUCCESS;
      }
    }
    window.clear(sf::Color::Black);
    float speed = 0.1f;
    sf::Vector2f eCurrentPosition = evader.getPosition();
    auto l = [](double x, sf::Vector2f currentPosition, sf::Vector2f dest) {
        return (dest.y * (x - currentPosition.x) + currentPosition.y * (dest.x - x)) / (dest.x - currentPosition.x);
    };
    evader.setPosition(eCurrentPosition.x + speed, l(eCurrentPosition.x + speed, eCurrentPosition, dest));
    sf::Vector2f pCurrentPosition = pursuer.getPosition();
    float xcord = pCurrentPosition.x < eCurrentPosition.x ? pCurrentPosition.x + speed : pCurrentPosition.x - speed;
    pursuer.setPosition(xcord , l(xcord, pCurrentPosition, eCurrentPosition));
    window.draw(evader);
    window.draw(pursuer);
    window.draw(target);
    window.display();
  }
  return EXIT_SUCCESS;
}
