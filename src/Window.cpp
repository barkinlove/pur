#include "Window.hpp"

Window::Window(sf::VideoMode mode, std::string title)
  : m_window(mode, title)
{
  sf::View view = m_window.getDefaultView();
  view.setSize(800, -800);
  m_window.setView(view);
}

Window::~Window() {
  m_window.close();
}

sf::Vector2u Window::getSize() const noexcept {
  return m_window.getSize();
}

bool Window::isOpen() const
{
  return m_window.isOpen();
}

bool Window::pollEvent(sf::Event& event) {
  return m_window.pollEvent(event);
}

void Window::clear(const sf::Color& color) {
  m_window.clear(color);
}

void Window::display() {
  m_window.display();
}
