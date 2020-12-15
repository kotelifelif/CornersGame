#pragma once
#include "State.h"
#include "Board.h"
#include "Player.h"
#include "AI.h"

#include <vector>

#include <SFML/Graphics.hpp>

class GameState : public State {
 public:
  GameState(bool is_white);
  virtual ~GameState();
  void Draw(sf::RenderWindow& window);
  GameStateType Update(sf::Event& event, sf::RenderWindow& window);

 private:
  AI ai_;
  bool is_white_;

  bool is_player_move_;
  int figure_number_;
  int x_offset_;
  int y_offset_;
  sf::Vector2f new_position_;
  sf::Vector2f old_position_;

  sf::Texture board_texture_;
  sf::Texture figure_texture_;

  Board board_;

  Player person_player_;
  Player ai_player_;

  std::vector<Figure> InitializeFigures(const sf::Texture& texture,
                                        const sf::IntRect& rectangle,
                                        const sf::Vector2i& initial_position,
                                        Board& board, const bool is_left_top);
  GameStateType CheckWinner();
};

