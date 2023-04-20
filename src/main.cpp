#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>

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
  sf::CircleShape evader{10.f}, pursuer{2.f};
  sf::RectangleShape target{sf::Vector2f{100, 50}};
  evader.setFillColor(Color::SeaColor);
  pursuer.setFillColor(Color::CarrotOrange);
  target.setFillColor(Color::SandColor);
  evader.setPosition(100.f, 100.f);
  pursuer.setPosition(200.f, 300.f);
  target.setPosition(window.getSize().x - 200, 200);
  sf::Event e;
  while (window.isOpen()) {
    while (window.pollEvent(e)) {
      if (e.type == sf::Event::Closed) {
        window.close();
        return EXIT_SUCCESS;
      }
    }
    window.clear(sf::Color::Black);
    evader.setPosition(evader.getPosition().x + 0.01f, evader.getPosition().y);
    pursuer.setPosition(evader.getPosition().x - 0.01f, pursuer.getPosition().y + 0.01f);
    window.draw(evader);
    window.draw(pursuer);
    window.draw(target);
    window.display();
  }
  return EXIT_SUCCESS;
}
