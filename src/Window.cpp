#include "Window.hpp"
#include <SFML/Window/Event.hpp>
#include <cstdint>

Window::Window(sf::VideoMode mode, std::string title)
  : m_window(mode, title)
{
  sf::View view = m_window.getDefaultView();
  view.setSize(800, -800);
  m_window.setView(view);
}

Window::~Window()
{
  m_window.close();
}

sf::Vector2u Window::getSize() const noexcept
{
  return m_window.getSize();
}

bool Window::isOpen() const
{
  return m_window.isOpen();
}

bool Window::pollEvent(sf::Event& event)
{
  return m_window.pollEvent(event);
}

void Window::clear(const sf::Color& color)
{
  m_window.clear(color);
}

void Window::display()
{
  m_window.display();
}

void Window::loop(std::function<void()> callback)
{
  std::uint32_t count = 0;
  sf::Event event;
  while (m_window.isOpen()) {
    count = count != -1 ? ++count : -1;
    while (m_window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        return;
      }
    }
    m_window.clear(sf::Color::Black);
    callback();
  }
}
