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

  template<typename T>
  void drawTrajectory(T obj, sf::Vector2f origin, sf::Vector2f end, std::function<float(float x, sf::Vector2f, sf::Vector2f)> strategy) {
      for (const auto& traj : obj.getTrajectory(origin, end, strategy)) {
          m_window.draw(traj);
      }
  }

  void display();

private:
  sf::RenderWindow m_window;
};
