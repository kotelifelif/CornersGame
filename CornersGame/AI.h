#pragma once
#include "Board.h"
#include "Player.h"

#include <vector>

#include <SFML/Graphics.hpp>

enum class Move {
    kLeft,
    kRight,
    kUp,
    kDown
};

class AI {
 public:
  //std::pair<sf::Vector2i, int> FindBestMove(Board& board, Player& player,
  //                                          int depth);
  AI(const bool is_black);
  int FindBestMove(Board& board, Player& player,
                                            int depth);
  std::vector<Cell> GetShortestPath(const Board& board, const Cell& source_cell,
                                    const Cell& destination_cell);
  std::pair<sf::Vector2i, int> GetMove(Board& board, Player& player) const; 

 private:
  bool is_black_;
  int figure_number_;
  Move move_;
  sf::Vector2i destination_coordinates_;
  int GetHeuristic(Board& board, Player& player);
  int CheckMove(Board& board, Player& player, sf::Vector2i& old_coordinates,
                 const sf::Vector2i& new_coordinates, int depth, int sum_distance,
                 int i, int score, const Move move);
};

