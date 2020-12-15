#pragma once
#include "State.h"
#include "Board.h"
#include "Figure.h"

#include <vector>

#include <SFML/Graphics.hpp>

class MenuState : public State {
 public:
  MenuState();
  virtual ~MenuState();
  void Draw(sf::RenderWindow& window) const override;
  GameStateType Update(sf::Event& event, sf::RenderWindow& window) override;

 private:
  sf::Font font_;
  sf::Text text_;

  sf::Texture board_texture_;
  sf::Texture figure_texture_;

  Figure white_figure_;
  Figure black_figure_;
  Board board_;

  const int kMenuXOffset;
  const int kMenuYOffset;
  const int kFontSize;
  const int kMenuBlackFigureOffsetX;
  const int kMenuBlackFigureOffsetY;
  const int kMenuWhiteFigureOffsetX;
  const int kMenuWhiteFigureOffsetY;
};

