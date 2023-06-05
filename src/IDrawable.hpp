#pragma once
#include <SFML/Graphics/Shape.hpp>

template<typename T>
class IDrawable {
private:
  using shape_t = T;
public:
  virtual shape_t getShape() const noexcept = 0;
};
