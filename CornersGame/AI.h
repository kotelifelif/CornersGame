#pragma once
#include "Board.h"
#include "Player.h"

#include <vector>

#include <SFML/Graphics.hpp>

class AI {
 public:
  AI(const bool is_black);
  int FindBestMove(Board& board, Player& player, int depth);
  std::pair<sf::Vector2i, int> GetMove() const;

 private:
  bool is_black_;
  int figure_number_;
  sf::Vector2i destination_coordinates_;
  const int kMaxDepth;
  int GetHeuristic(Board& board, Player& player);
  int CheckMove(Board& board, Player& player, sf::Vector2i& old_coordinates,
                const sf::Vector2i& new_coordinates, int depth,
                int sum_distance, int figure_number, int score);
};

