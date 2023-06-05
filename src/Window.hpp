#pragma once
#include "Object.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>
#include <functional>
#include <string>

class Window
{
public:
  Window(sf::VideoMode mode, std::string title);
  ~Window();

  sf::Vector2u getSize() const noexcept;
  bool isOpen() const;
  bool pollEvent(sf::Event& event);
  void clear(const sf::Color& color);
  void loop(std::function<void()> callback);

  template<typename T>
  void draw(T obj)
  {
    m_window.draw(obj.getShape());
  }

  void display();

private:
  sf::RenderWindow m_window;
};
