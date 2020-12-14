#include "AI.h"
#include "Figure.h"

#include <algorithm>
#include <utility>
#include <vector>
#include <cmath>

#include "Constants.h"


AI::AI(const bool is_black) : is_black_(is_black) {}

int AI::FindBestMove(Board& board, Player& player, int depth) {
  int score = GetHeuristic(board, player);
  if (depth == 1) {
    return score;
  }

  sf::Vector2i best_move(0, 0);

  std::vector<Figure> figures = player.GetFigures();
  int shortest_path_length = constants::kRows * constants::kColumns;
  int figure_number = -1;
  Cell figure_cell;
  std::vector<Cell> path;
  int sum_distance = 1000;
  for (int i = 0; i < figures.size(); ++i) {
    figure_cell = board.GetCell(figures[i].GetPosition());
    sf::Vector2i figure_cell_coordinats = board.GetCellCoordinats(figure_cell);

    if (figure_cell_coordinats.x - 1 >= 0) {
      if (!board.GetCell(figure_cell_coordinats.x - 1, figure_cell_coordinats.y)
               .is_busy) {
        board.SetBusy(figure_cell_coordinats.x, figure_cell_coordinats.y,
                      false);
        board.SetCollor(figure_cell_coordinats.x, figure_cell_coordinats.y,
                        FigureColor::kNone);
        board.SetBusy(figure_cell_coordinats.x - 1, figure_cell_coordinats.y,
                      true);
        board.SetCollor(figure_cell_coordinats.x - 1, figure_cell_coordinats.y,
                        FigureColor::kWhite);
        Cell position = board.GetCell(figure_cell_coordinats.x - 1,
                                      figure_cell_coordinats.y);
        sf::Vector2f new_position =
            sf::Vector2f(position.rectangle.left + constants::kXOffset,
                         position.rectangle.top + constants::kYOffset);
        player.SetFigurePosition(i, new_position);

        // launch minimax algorithm
        score = FindBestMove(board, player, depth + 1);
        // check if new value is better
        if (score < sum_distance) {
          figure_number_ = i;
          sum_distance = score;
          move_ = Move::kLeft;
          //destination_coordinats_ = sf::Vector2i(figure_cell_coordinats.x - 1,
          //                                       figure_cell_coordinats.y);
        }

        board.SetBusy(figure_cell_coordinats.x, figure_cell_coordinats.y, true);
        board.SetCollor(figure_cell_coordinats.x, figure_cell_coordinats.y,
                        FigureColor::kWhite);
        board.SetBusy(figure_cell_coordinats.x - 1, figure_cell_coordinats.y,
                      false);
        board.SetCollor(figure_cell_coordinats.x - 1, figure_cell_coordinats.y,
                        FigureColor::kNone);
        position =
            board.GetCell(figure_cell_coordinats.x, figure_cell_coordinats.y);
        new_position =
            sf::Vector2f(position.rectangle.left + constants::kXOffset,
                         position.rectangle.top + constants::kYOffset);
        player.SetFigurePosition(i, new_position);
      }
    }

    if (figure_cell_coordinats.x + 1 < constants::kRows) {
      if (!board.GetCell(figure_cell_coordinats.x + 1, figure_cell_coordinats.y)
               .is_busy) {
        board.SetBusy(figure_cell_coordinats.x, figure_cell_coordinats.y,
                      false);
        board.SetCollor(figure_cell_coordinats.x, figure_cell_coordinats.y,
                        FigureColor::kNone);
        board.SetBusy(figure_cell_coordinats.x + 1, figure_cell_coordinats.y,
                      true);
        board.SetCollor(figure_cell_coordinats.x + 1, figure_cell_coordinats.y,
                        FigureColor::kWhite);
        Cell position = board.GetCell(figure_cell_coordinats.x + 1,
                                      figure_cell_coordinats.y);
        sf::Vector2f new_position =
            sf::Vector2f(position.rectangle.left + constants::kXOffset,
                         position.rectangle.top + constants::kYOffset);
        player.SetFigurePosition(i, new_position);

        // launch minimax algorithm
        score = FindBestMove(board, player, depth + 1);
        // check if new value is better
        if (score < sum_distance) {
          figure_number_ = i;
          sum_distance = score;
          move_ = Move::kRight;
          //destination_coordinats_ = sf::Vector2i(figure_cell_coordinats.x + 1,
          //                                       figure_cell_coordinats.y);
        }

        board.SetBusy(figure_cell_coordinats.x, figure_cell_coordinats.y, true);
        board.SetCollor(figure_cell_coordinats.x, figure_cell_coordinats.y,
                        FigureColor::kWhite);
        board.SetBusy(figure_cell_coordinats.x + 1, figure_cell_coordinats.y,
                      false);
        board.SetCollor(figure_cell_coordinats.x + 1, figure_cell_coordinats.y,
                        FigureColor::kNone);
        position =
            board.GetCell(figure_cell_coordinats.x, figure_cell_coordinats.y);
        new_position =
            sf::Vector2f(position.rectangle.left + constants::kXOffset,
                         position.rectangle.top + constants::kYOffset);
        player.SetFigurePosition(i, new_position);
      }
    }

    if (figure_cell_coordinats.y - 1 >= 0) {
      if (!board.GetCell(figure_cell_coordinats.x, figure_cell_coordinats.y - 1)
               .is_busy) {
        board.SetBusy(figure_cell_coordinats.x, figure_cell_coordinats.y,
                      false);
        board.SetCollor(figure_cell_coordinats.x, figure_cell_coordinats.y,
                        FigureColor::kNone);
        board.SetBusy(figure_cell_coordinats.x, figure_cell_coordinats.y - 1,
                      true);
        board.SetCollor(figure_cell_coordinats.x, figure_cell_coordinats.y - 1,
                        FigureColor::kWhite);
        Cell position = board.GetCell(figure_cell_coordinats.x,
                                      figure_cell_coordinats.y - 1);
        sf::Vector2f new_position =
            sf::Vector2f(position.rectangle.left + constants::kXOffset,
                         position.rectangle.top + constants::kYOffset);
        player.SetFigurePosition(i, new_position);

        // launch minimax algorithm
        score = FindBestMove(board, player, depth + 1);
        // check if new value is better
        if (score < sum_distance) {
          figure_number_ = i;
          sum_distance = score;
          move_ = Move::kDown;
          //destination_coordinats_ = sf::Vector2i(figure_cell_coordinats.x,
          //                                       figure_cell_coordinats.y - 1);
        }

        board.SetBusy(figure_cell_coordinats.x, figure_cell_coordinats.y, true);
        board.SetCollor(figure_cell_coordinats.x, figure_cell_coordinats.y,
                        FigureColor::kWhite);
        board.SetBusy(figure_cell_coordinats.x, figure_cell_coordinats.y - 1,
                      false);
        board.SetCollor(figure_cell_coordinats.x, figure_cell_coordinats.y - 1,
                        FigureColor::kNone);
        position =
            board.GetCell(figure_cell_coordinats.x, figure_cell_coordinats.y);
        new_position =
            sf::Vector2f(position.rectangle.left + constants::kXOffset,
                         position.rectangle.top + constants::kYOffset);
        player.SetFigurePosition(i, new_position);
      }
    }

    if (figure_cell_coordinats.y + 1 < constants::kColumns) {
      if (!board.GetCell(figure_cell_coordinats.x, figure_cell_coordinats.y + 1)
               .is_busy) {
        board.SetBusy(figure_cell_coordinats.x, figure_cell_coordinats.y,
                      false);
        board.SetCollor(figure_cell_coordinats.x, figure_cell_coordinats.y,
                        FigureColor::kNone);
        board.SetBusy(figure_cell_coordinats.x, figure_cell_coordinats.y + 1,
                      true);
        board.SetCollor(figure_cell_coordinats.x, figure_cell_coordinats.y + 1,
                        FigureColor::kWhite);
        Cell position = board.GetCell(figure_cell_coordinats.x,
                                      figure_cell_coordinats.y + 1);
        sf::Vector2f new_position =
            sf::Vector2f(position.rectangle.left + constants::kXOffset,
                         position.rectangle.top + constants::kYOffset);
        player.SetFigurePosition(i, new_position);

        // launch minimax algorithm
        score = FindBestMove(board, player, depth + 1);
        // check if new value is better
        if (score < sum_distance) {
          figure_number_ = i;
          sum_distance = score;
          move_ = Move::kUp;
          //destination_coordinats_ = sf::Vector2i(figure_cell_coordinats.x,
          //                                       figure_cell_coordinats.y + 1);
        }

        board.SetBusy(figure_cell_coordinats.x, figure_cell_coordinats.y, true);
        board.SetCollor(figure_cell_coordinats.x, figure_cell_coordinats.y,
                        FigureColor::kWhite);
        board.SetBusy(figure_cell_coordinats.x, figure_cell_coordinats.y + 1,
                      false);
        board.SetCollor(figure_cell_coordinats.x, figure_cell_coordinats.y + 1,
                        FigureColor::kNone);
        position =
            board.GetCell(figure_cell_coordinats.x, figure_cell_coordinats.y);
        new_position =
            sf::Vector2f(position.rectangle.left + constants::kXOffset,
                         position.rectangle.top + constants::kYOffset);
        player.SetFigurePosition(i, new_position);
      }
    }
  }
  // return std::make_pair(best_move, figure_number);
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

  int max_path_length = constants::kRows * constants::kColumns;
  std::vector<std::vector<int>> distances(
      adjacent_cells.size(),
      std::vector<int>(adjacent_cells.size(), max_path_length));
  std::vector<std::vector<Cell>> previous_cells(
      adjacent_cells.size(), std::vector<Cell>(adjacent_cells.size(), Cell()));
  // priority by distance (first), second - vertex
  std::vector<std::pair<int, Cell>> processed;

  sf::Vector2i source_coordinats = board.GetCellCoordinats(source_cell);
  distances[source_coordinats.x][source_coordinats.y] = 0;

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

    for (int i = 0; i < adjacent_cells[coordinates.x][coordinates.y].size();
         ++i) {
      Cell neighbor = adjacent_cells[coordinates.x][coordinates.y][i];
      int neighbor_cost = cost[coordinates.x][coordinates.y][i];

      auto neighbor_coordinates = board.GetCellCoordinats(neighbor);
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
  sf::Vector2i destination_coordinats =
      board.GetCellCoordinats(destination_cell);

  // Change for black and white case
  // If there are no path to destination cell
  if (distances[destination_coordinats.x][destination_coordinats.y] ==
      max_path_length) {
    for (size_t i = 0; i < constants::kRows; ++i) {
      for (size_t j = 0; j < constants::kColumns; ++j) {
        if (distances[i][j] != max_path_length) {
          destination_coordinats.x = i;
          destination_coordinats.y = j;
          break;
        }
      }
    }
  }

  Cell previous_cell =
      board.GetCell(destination_coordinats.x, destination_coordinats.y);
  while (previous_cell != source_cell) {
    path.push_back(previous_cell);
    sf::Vector2i previous_cell_coordinates =
        board.GetCellCoordinats(previous_cell);
    previous_cell = previous_cells[previous_cell_coordinates.x]
                                  [previous_cell_coordinates.y];
    previous_cell_coordinates = board.GetCellCoordinats(previous_cell);
  }
  std::reverse(path.begin(), path.end());

  return path;
}

std::pair<sf::Vector2i, int> AI::GetMove(Board& board, Player& player) const {
  std::vector<Figure> figures = player.GetFigures();
  Cell figure_cell = board.GetCell(figures[figure_number_].GetPosition());
  sf::Vector2i figure_cell_coordinats = board.GetCellCoordinats(figure_cell);
  switch (move_) {
    case (Move::kDown):
      figure_cell_coordinats.y--;
      return std::make_pair(figure_cell_coordinats, figure_number_);
    case (Move::kLeft):
      figure_cell_coordinats.x--;
      return std::make_pair(figure_cell_coordinats, figure_number_);
    case (Move::kRight):
      figure_cell_coordinats.x++;
      return std::make_pair(figure_cell_coordinats, figure_number_);
    case (Move::kUp):
      figure_cell_coordinats.y++;
      return std::make_pair(figure_cell_coordinats, figure_number_);
  }
  return std::make_pair(destination_coordinats_, figure_number_);
}

int AI::GetHeuristic(Board& board, Player& player) {
  int result = constants::kRows * constants::kColumns;
  std::vector<Figure> figures = player.GetFigures();
  sf::Vector2i figure_coordinats;
  sf::Vector2f figure_point;
  for (Figure& figure : figures) {
    figure_point = figure.GetPosition();
    figure_coordinats = board.GetCellCoordinats(board.GetCell(figure_point));
    for (int i = 0; i < constants::kFigureRows; ++i) {
      for (int j = 0; j < constants::kFigureColumns; ++j) {
        if (is_black_) {
          result +=
              sqrt(pow(figure_coordinats.x - (constants::kRows - i), 2) +
                   pow(figure_coordinats.y - (constants::kColumns - j), 2));
        } else {
          result += sqrt(pow(figure_coordinats.x - i, 2) +
                         pow(figure_coordinats.y - j, 2));
        }
      }
    }
  }
  return result;
}
