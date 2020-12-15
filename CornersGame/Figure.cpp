// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// http://www.viva64.com

#include "Figure.h"

Figure::Figure() {}

Figure::Figure(const sf::Texture& texture, const sf::IntRect& rectangle,
               const sf::Vector2f& offset)
    : texture_(texture), sprite_(texture, rectangle) {
  sprite_.move(offset);
}

void Figure::Draw(sf::RenderWindow& window) const { window.draw(sprite_); }

void Figure::SetPosition(const sf::Vector2f& position) {
  sprite_.setPosition(position);
}

sf::Vector2f Figure::GetPosition() const { return sprite_.getPosition(); }

sf::Sprite Figure::GetSprite() const { return sprite_; }
