#pragma once
#include "IDrawable.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>

template<typename T, typename S>
class Object : public IDrawable<T>
{
private:
  using base_t = T;
  using size_t = S;

protected:
  explicit Object(size_t size, sf::Color color)
    : m_baseShape(size)
  {
    m_baseShape.setFillColor(color);
  }

public:
  virtual void setPos(float x, float y) { m_baseShape.setPosition(x, y); }
  base_t getShape() const noexcept override { return m_baseShape; }

  virtual const sf::Vector2f& getPos() const noexcept
  {
    return m_baseShape.getPosition();
  }

protected:
  base_t m_baseShape;
};
