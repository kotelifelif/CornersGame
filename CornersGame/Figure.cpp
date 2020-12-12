#include "Figure.h"

Figure::Figure() {}

Figure::Figure(const sf::Texture& texture, const sf::IntRect& rectangle,
               const sf::Vector2f& offset, const Cell& target_cell_)
    : texture_(texture),
      sprite_(texture, rectangle),
      target_cell_(target_cell_) {
  sprite_.move(offset);
}

void Figure::Draw(sf::RenderWindow& window) const { window.draw(sprite_); }

void Figure::SetPosition(const sf::Vector2f& position) {
  sprite_.setPosition(position);
}

sf::Vector2f Figure::GetPosition() const { return sprite_.getPosition(); }

sf::Sprite Figure::GetSprite() const { return sprite_; }

void Figure::SetTargetCell(const Cell& cell) { target_cell_ = cell; }

Cell Figure::GetTargetCell() { return target_cell_; }
