#include "AI.h"
#include "Figure.h"

#include <algorithm>
#include <utility>
#include <vector>

#include "Constants.h"


std::pair<sf::Vector2i, int> AI::FindBestMove(Board& board, Player& player) {
  sf::Vector2i best_move(0, 0);

  std::vector<Figure> figures = player.GetFigures();
  int shortest_path_length = constants::kRows * constants::kColumns;
  int figure_number = -1;
  int evaluation = 0;
  Cell figure_cell;
  std::vector<Cell> path;
  for (int i = 0; i < figures.size(); ++i) {
    figure_cell = board.GetCell(figures[i].GetPosition());
    path = GetShortestPath(board, figure_cell, figures[i].GetTargetCell());
    if (path.size() < shortest_path_length && !path.empty()) {
      shortest_path_length = path.size();
      figure_number = i;
      auto coordinats = board.GetCellCoordinats(*path.begin());
      best_move = sf::Vector2i(coordinats.first, coordinats.second);
    }
  }
  return std::make_pair(best_move, figure_number);
}

// Implementation of Dijkstra algorithm
std::vector<Cell> AI::GetShortestPath(Board& board, Cell source_cell,
                                      Cell destination_cell) {
  std::vector<std::vector<Cell>> cells = board.GetCells();
  std::vector<std::vector<std::vector<Cell>>> adjacent_cells(cells.size());
  std::vector<std::vector<std::vector<int>>> cost(cells.size());
  const int kCost = 1;

  for (int i = 0; i < cells.size(); ++i) {
    adjacent_cells.at(i).resize(cells.at(0).size());
    cost.at(i).resize(cells.at(0).size());
    for (int j = 0; j < cells[i].size(); ++j) {
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

      if ((i + 1) < cells.size()) {
        if (!cells[i + 1][j].is_busy) {
          adjacent_cells[i][j].push_back(cells[i + 1][j]);
          cost[i][j].push_back(kCost);
        }
      }

      if ((j + 1) < cells[i].size()) {
        if (!cells[i][j + 1].is_busy) {
          adjacent_cells[i][j].push_back(cells[i][j + 1]);
          cost[i][j].push_back(kCost);
        }
      }
    }
  }

  int max = constants::kRows * constants::kColumns;
  std::vector<std::vector<int>> distances(
      adjacent_cells.size(), std::vector<int>(adjacent_cells.size(), max));
  std::vector<std::vector<Cell>> previous(
      adjacent_cells.size(), std::vector<Cell>(adjacent_cells.size(), Cell()));
  // priority by distance (first), second - vertex
  std::vector<std::pair<int, Cell>> processed;

  std::pair<int, int> source_coordinats = board.GetCellCoordinats(source_cell);
  distances[source_coordinats.first][source_coordinats.second] = 0;

  for (int i = 0; i < adjacent_cells.size(); ++i) {
    for (int j = 0; j < adjacent_cells[i].size(); ++j) {
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
    auto coordinates = board.GetCellCoordinats(vertex);
    processed.pop_back();

    for (int i = 0;
         i < adjacent_cells[coordinates.first][coordinates.second].size();
         ++i) {
      Cell neighbor = adjacent_cells[coordinates.first][coordinates.second][i];
      int neighbor_cost = cost[coordinates.first][coordinates.second][i];

      auto neighbor_coordinates = board.GetCellCoordinats(neighbor);
      if (distances[neighbor_coordinates.first][neighbor_coordinates.second] >
          distances[coordinates.first][coordinates.second] + neighbor_cost) {
        distances[neighbor_coordinates.first][neighbor_coordinates.second] =
            distances[coordinates.first][coordinates.second] + neighbor_cost;
        // Maybe change
        previous[neighbor_coordinates.first][neighbor_coordinates.second] =
            vertex;

        // Change priority
        processed.push_back(std::make_pair(
            distances[neighbor_coordinates.first][neighbor_coordinates.second],
            neighbor));
      }
    }
  }

  std::vector<Cell> path;
  std::pair<int, int> destination_coordinats =
      board.GetCellCoordinats(destination_cell);

  // Change for black and white case
  // If there are no path to destination cell
  if (distances[destination_coordinats.first][destination_coordinats.second] ==
      max) {
    for (size_t i = 0; i < constants::kRows; ++i) {
      for (size_t j = 0; j < constants::kColumns; ++j) {
        if (distances[i][j] != max) {
          destination_coordinats.first = i;
          destination_coordinats.second = j;
          break;
        }
      }
    }
  }

  Cell previous_cell = board.GetCell(destination_coordinats.first,
                                     destination_coordinats.second);
  while (previous_cell != source_cell) {
    path.push_back(previous_cell);
    auto previous_cell_coordinates = board.GetCellCoordinats(previous_cell);
    previous_cell = previous[previous_cell_coordinates.first]
                            [previous_cell_coordinates.second];
    previous_cell_coordinates = board.GetCellCoordinats(previous_cell);
  }
  std::reverse(path.begin(), path.end());

  return path;
}
