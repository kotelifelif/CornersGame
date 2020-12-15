#pragma once
#include "Figure.h"
#include "Board.h"

#include <vector>

#include <SFML/Graphics.hpp>

class Player {
 public:
  Player();
  Player(const std::vector<Figure>& figures);
  void Draw(sf::RenderWindow& window) const;
  std::vector<Figure> GetFigures() const;
  Figure GetFigure(const int position) const;
  void SetFigurePosition(const int figure_number,
                         const sf::Vector2f& screen_position);
  void SetFigurePosition(Board& board, const int figure_position, const int row,
                         const int column);

 private:
  std::vector<Figure> figures_;
};

