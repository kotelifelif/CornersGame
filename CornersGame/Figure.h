#pragma once
#include "Board.h"

#include <SFML/Graphics.hpp>

class Figure {
 public:
  Figure();
  Figure(const sf::Texture& texture, const sf::IntRect& rectangle,
         const sf::Vector2f& offset);
  void Draw(sf::RenderWindow& window) const;

  void SetPosition(const sf::Vector2f& position);
  sf::Vector2f GetPosition() const;

  sf::Sprite GetSprite() const;

 private:
  sf::Sprite sprite_;
  sf::Texture texture_;
};

