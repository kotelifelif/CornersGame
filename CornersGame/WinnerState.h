#pragma once
#include "State.h"
#include "Board.h"

#include <SFML/Graphics.hpp>

class WinnerState : public State {
 public:
  WinnerState(const bool is_player_win);
  virtual ~WinnerState();
  void Draw(sf::RenderWindow& window) override;
  GameStateType Update(sf::Event& event, sf::RenderWindow& window) override;

 private:
  sf::Font font_;
  sf::Text congratulatory_text_;
  sf::Text menu_text_;
  
  sf::Texture board_texture_;
  Board board_;
  
  const int kFontSize;
  const int kCongratulatoryTextOffsetX = 2;
  const int kCongratulatoryTextOffsetY = 3;
  const int kMenuTextOffsetX = 2;
  const int kMenuTextOffsetY = 4;
};
