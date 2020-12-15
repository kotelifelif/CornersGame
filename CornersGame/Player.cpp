#include "Player.h"
#include "Board.h"

#include <algorithm>

#include <SFML/Graphics.hpp> 

#include "Constants.h"

Player::Player() {}

Player::Player(const std::vector<Figure>& figures) : figures_(figures) {}

void Player::Draw(sf::RenderWindow& window) const {
  for (const auto& figure : figures_) {
    figure.Draw(window);
  }
}

std::vector<Figure> Player::GetFigures() const { return figures_; }

Figure Player::GetFigure(const int position) const {
  return figures_.at(position);
}

void Player::SetFigurePosition(const int figure_number,
                               const sf::Vector2f& screen_position) {
  figures_.at(figure_number).SetPosition(screen_position);
}

void Player::SetFigurePosition(Board& board, const int figure_position,
                               const int row, const int column) {
  Cell position = board.GetCell(row, column);
  sf::Vector2f new_position =
      sf::Vector2f(position.rectangle.left + constants::kXOffset,
                   position.rectangle.top + constants::kYOffset);
  SetFigurePosition(figure_position, new_position);
}


