#pragma once

class Actor;

class CollisionSystem final {
public:
  static bool collide(Actor first, Actor second);
};
