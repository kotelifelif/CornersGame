// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// http://www.viva64.com

#include "AI.h"
#include "Figure.h"

#include <algorithm>
#include <utility>
#include <vector>
#include <cmath>

#include "Constants.h"


AI::AI(const bool is_black) : is_black_(is_black), figure_number_(0), kMaxDepth(1) {}

int AI::FindBestMove(Board& board, Player& player, int depth) {
  int score = GetHeuristic(board, player);
  if (depth == kMaxDepth) {
    return score;
  }

  std::vector<Figure> figures = player.GetFigures();
  int figure_number = -1;
  Cell figure_cell;
  std::vector<Cell> path;
  int sum_distance = constants::kRows * constants::kColumns *
                     constants::kFigureColumns * constants::kFigureRows;
  for (size_t i = 0; i < figures.size(); ++i) {
    figure_cell = board.GetCell(figures[i].GetPosition());
    sf::Vector2i figure_cell_coordinates = board.GetCellCoordinates(figure_cell);

    if (figure_cell_coordinates.x - 1 >= 0) {
      sum_distance = CheckMove(
          board, player, figure_cell_coordinates,
          sf::Vector2i(figure_cell_coordinates.x - 1, figure_cell_coordinates.y),
          depth, sum_distance, i, score);
    }

    if (figure_cell_coordinates.x + 1 < constants::kRows) {
      sum_distance = CheckMove(
          board, player, figure_cell_coordinates,
          sf::Vector2i(figure_cell_coordinates.x + 1, figure_cell_coordinates.y),
          depth, sum_distance, i, score);
    }

    if (figure_cell_coordinates.y - 1 >= 0) {
      sum_distance = CheckMove(
          board, player, figure_cell_coordinates,
          sf::Vector2i(figure_cell_coordinates.x, figure_cell_coordinates.y - 1),
          depth, sum_distance, i, score);
    }

    if (figure_cell_coordinates.y + 1 < constants::kColumns) {
      sum_distance = CheckMove(
          board, player, figure_cell_coordinates,
          sf::Vector2i(figure_cell_coordinates.x, figure_cell_coordinates.y + 1),
          depth, sum_distance, i, score);
    }
  }

  return sum_distance;
}

std::pair<sf::Vector2i, int> AI::GetMove(const Board& board, Player& player) const {
  return std::make_pair(destination_coordinates_, figure_number_);
}

int AI::GetHeuristic(Board& board, Player& player) {
  int result = 0;
  std::vector<Figure> figures = player.GetFigures();
  sf::Vector2i figure_coordinates;
  sf::Vector2f figure_point;
  for (Figure& figure : figures) {
    figure_point = figure.GetPosition();
    figure_coordinates = board.GetCellCoordinates(board.GetCell(figure_point));
    if (!is_black_) {
      for (int i = constants::kRows - 1;
           i > constants::kRows - constants::kFigureRows; --i) {
        for (int j = constants::kColumns;
             j > constants::kColumns - constants::kFigureColumns; --j) {
          result += static_cast<int>(sqrt(pow(figure_coordinates.x - i, 2) +
                         pow(figure_coordinates.y - j, 2)));
        }
      }
    } else {
      for (int i = 0; i < constants::kFigureRows; ++i) {
        for (int j = 0; j < constants::kFigureColumns; ++j) {
          result += static_cast<int>(sqrt(pow(figure_coordinates.x - i, 2) +
                         pow(figure_coordinates.y - j, 2)));
        }
      }
    }
  }

  return result;
}

int AI::CheckMove(Board& board, Player& player, sf::Vector2i& old_coordinates,
                  const sf::Vector2i& new_coordinates, int depth,
                  int sum_distance, int figure_number, int score) {
  if (!board.GetCell(new_coordinates.x, new_coordinates.y).is_busy) {
    board.SetBusy(old_coordinates.x, old_coordinates.y, false);

    board.SetBusy(new_coordinates.x, new_coordinates.y, true);
    player.SetFigurePosition(board, figure_number, new_coordinates.x, new_coordinates.y);

    // Launch minimax algorithm
    score = FindBestMove(board, player, depth + 1);
    // Check if new value is better
    if (score < sum_distance) {
      figure_number_ = figure_number;
      sum_distance = score;
      destination_coordinates_ = new_coordinates;
    }

    board.SetBusy(old_coordinates.x, old_coordinates.y, true);
    board.SetBusy(new_coordinates.x, new_coordinates.y, false);
    player.SetFigurePosition(board, figure_number, old_coordinates.x, old_coordinates.y);
  }
  return sum_distance;
}
