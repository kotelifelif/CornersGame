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


AI::AI(const bool is_black) : is_black_(is_black), figure_number_(0), move_() {}

int AI::FindBestMove(Board& board, Player& player, int depth) {
  int score = GetHeuristic(board, player);
  if (depth == 1) {
    return score;
  }

  sf::Vector2i best_move(0, 0);

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
          depth, sum_distance, i, score, Move::kLeft);
    }

    if (figure_cell_coordinates.x + 1 < constants::kRows) {
      sum_distance = CheckMove(
          board, player, figure_cell_coordinates,
          sf::Vector2i(figure_cell_coordinates.x + 1, figure_cell_coordinates.y),
          depth, sum_distance, i, score, Move::kRight);
    }

    if (figure_cell_coordinates.y - 1 >= 0) {
      sum_distance = CheckMove(
          board, player, figure_cell_coordinates,
          sf::Vector2i(figure_cell_coordinates.x, figure_cell_coordinates.y - 1),
          depth, sum_distance, i, score, Move::kDown);
    }

    if (figure_cell_coordinates.y + 1 < constants::kColumns) {
      sum_distance = CheckMove(
          board, player, figure_cell_coordinates,
          sf::Vector2i(figure_cell_coordinates.x, figure_cell_coordinates.y + 1),
          depth, sum_distance, i, score, Move::kUp);
    }
  }

  return sum_distance;
}

// Implementation of Dijkstra algorithm
std::vector<Cell> AI::GetShortestPath(const Board& board,
                                      const Cell& source_cell,
                                      const Cell& destination_cell) {
  std::vector<std::vector<Cell>> cells = board.GetCells();
  std::vector<std::vector<std::vector<Cell>>> adjacent_cells(cells.size());
  std::vector<std::vector<std::vector<int>>> cost(cells.size());
  const int kCost = 1;

  for (int i = 0; i < static_cast<int>(cells.size()); ++i) {
    adjacent_cells.at(i).resize(cells.at(0).size());
    cost.at(i).resize(cells.at(0).size());
    for (int j = 0; j < static_cast<int>(cells[i].size()); ++j) {
      if ((i - 1) >= 0) {
        if (!cells[i - 1][j].is_busy) {
          adjacent_cells[i][j].push_back(cells[i - 1][j]);
          cost[i][j].push_back(kCost);
        }
      }

      if ((j - 1) >= 0) {
        if (!cells[i][j - 1].is_busy) {
          adjacent_cells[i][j].push_back(cells[i][j - 1]);
          cost[i][j].push_back(kCost);
        }
      }

      if ((i + 1) < static_cast<int>(cells.size())) {
        if (!cells[i + 1][j].is_busy) {
          adjacent_cells[i][j].push_back(cells[i + 1][j]);
          cost[i][j].push_back(kCost);
        }
      }

      if ((j + 1) < static_cast<int>(cells[i].size())) {
        if (!cells[i][j + 1].is_busy) {
          adjacent_cells[i][j].push_back(cells[i][j + 1]);
          cost[i][j].push_back(kCost);
        }
      }
    }
  }

  int max_path_length = constants::kRows * constants::kColumns;
  std::vector<std::vector<int>> distances(
      adjacent_cells.size(),
      std::vector<int>(adjacent_cells.size(), max_path_length));
  std::vector<std::vector<Cell>> previous_cells(
      adjacent_cells.size(), std::vector<Cell>(adjacent_cells.size(), Cell()));
  // priority by distance (first), second - vertex
  std::vector<std::pair<int, Cell>> processed;

  sf::Vector2i source_coordinates = board.GetCellCoordinates(source_cell);
  distances[source_coordinates.x][source_coordinates.y] = 0;

  for (size_t i = 0; i < adjacent_cells.size(); ++i) {
    for (size_t j = 0; j < adjacent_cells[i].size(); ++j) {
      processed.push_back(std::make_pair(distances[i][j], board.GetCell(i, j)));
    }
  }

  while (!processed.empty()) {
    std::sort(
        processed.begin(), processed.end(),
        [&board](std::pair<int, Cell>& left, std::pair<int, Cell>& right) {
          return left.first > right.first;
        });

    auto& current = processed.back();
    int distance = current.first;
    Cell vertex = current.second;
    auto coordinates = board.GetCellCoordinates(vertex);
    processed.pop_back();

    for (size_t i = 0; i < adjacent_cells[coordinates.x][coordinates.y].size();
         ++i) {
      Cell neighbor = adjacent_cells[coordinates.x][coordinates.y][i];
      int neighbor_cost = cost[coordinates.x][coordinates.y][i];

      auto neighbor_coordinates = board.GetCellCoordinates(neighbor);
      if (distances[neighbor_coordinates.x][neighbor_coordinates.y] >
          distances[coordinates.x][coordinates.y] + neighbor_cost) {
        distances[neighbor_coordinates.x][neighbor_coordinates.y] =
            distances[coordinates.x][coordinates.y] + neighbor_cost;
        // Maybe change
        previous_cells[neighbor_coordinates.x][neighbor_coordinates.y] = vertex;

        // Change priority
        processed.push_back(std::make_pair(
            distances[neighbor_coordinates.x][neighbor_coordinates.y],
            neighbor));
      }
    }
  }

  std::vector<Cell> path;
  sf::Vector2i destination_coordinates =
      board.GetCellCoordinates(destination_cell);

  // Change for black and white case
  // If there are no path to destination cell
  if (distances[destination_coordinates.x][destination_coordinates.y] ==
      max_path_length) {
    for (size_t i = 0; i < constants::kRows; ++i) {
      for (size_t j = 0; j < constants::kColumns; ++j) {
        if (distances[i][j] != max_path_length) {
          destination_coordinates.x = i;
          destination_coordinates.y = j;
          break;
        }
      }
    }
  }

  Cell previous_cell =
      board.GetCell(destination_coordinates.x, destination_coordinates.y);
  while (previous_cell != source_cell) {
    path.push_back(previous_cell);
    sf::Vector2i previous_cell_coordinates =
        board.GetCellCoordinates(previous_cell);
    previous_cell = previous_cells[previous_cell_coordinates.x]
                                  [previous_cell_coordinates.y];
    previous_cell_coordinates = board.GetCellCoordinates(previous_cell);
  }
  std::reverse(path.begin(), path.end());

  return path;
}

std::pair<sf::Vector2i, int> AI::GetMove(Board& board, Player& player) const {
  std::vector<Figure> figures = player.GetFigures();
  Cell figure_cell = board.GetCell(figures[figure_number_].GetPosition());
  sf::Vector2i figure_cell_coordinates = board.GetCellCoordinates(figure_cell);
  switch (move_) {
    case (Move::kDown):
      figure_cell_coordinates.y--;
      return std::make_pair(figure_cell_coordinates, figure_number_);
    case (Move::kLeft):
      figure_cell_coordinates.x--;
      return std::make_pair(figure_cell_coordinates, figure_number_);
    case (Move::kRight):
      figure_cell_coordinates.x++;
      return std::make_pair(figure_cell_coordinates, figure_number_);
    case (Move::kUp):
      figure_cell_coordinates.y++;
      return std::make_pair(figure_cell_coordinates, figure_number_);
  }
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
                  int sum_distance, int i, int score, const Move move) {
  if (!board.GetCell(new_coordinates.x, new_coordinates.y).is_busy) {
    board.SetBusy(old_coordinates.x, old_coordinates.y, false);

    board.SetBusy(new_coordinates.x, new_coordinates.y, true);
    player.SetFigurePosition(board, i, new_coordinates.x, new_coordinates.y);

    // launch minimax algorithm
    score = FindBestMove(board, player, depth + 1);
    // check if new value is better
    if (score < sum_distance) {
      figure_number_ = i;
      sum_distance = score;
      move_ = move;

    }

    board.SetBusy(old_coordinates.x, old_coordinates.y, true);
    board.SetBusy(new_coordinates.x, new_coordinates.y, false);
    player.SetFigurePosition(board, i, old_coordinates.x, old_coordinates.y);
  }
  return sum_distance;
}
