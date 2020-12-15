// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// http://www.viva64.com

#include "Board.h"

#include <SFML/Graphics.hpp>

#include "Constants.h"

Board::Board(const sf::Texture& texture, const sf::Vector2i& initial_position)
    : sprite_(texture) {
  cells_.resize(constants::kRows);
  for (size_t i = 0; i < constants::kRows; ++i) {
    for (size_t j = 0; j < constants::kColumns; ++j) {
      Cell cell;
      cell.is_busy = false;
      cell.color = FigureColor::kNone;
      cell.rectangle =
          sf::FloatRect(initial_position.x + i * constants::kCellSizeX,
                        initial_position.y + j * constants::kCellSizeY,
                        constants::kCellSizeX, constants::kCellSizeY);
      cells_[i].push_back(cell);
    }
  }
}

Board::Board() {}

void Board::Draw(sf::RenderWindow& window) const { window.draw(sprite_); }

void Board::SetBusy(const int row, const int column, const bool is_busy) {
  cells_.at(row).at(column).is_busy = is_busy;
}

void Board::SetBusy(const int row, const int column, const bool is_busy,
                    const FigureColor color) {
  cells_.at(row).at(column).color = color;
  cells_.at(row).at(column).is_busy = is_busy;
}

bool Board::GetBusy(const int row, const int column) const {
  return cells_.at(row).at(column).is_busy;
}

bool Board::GetBusy(const sf::Vector2f& point) const {
  for (const auto& cell_row : cells_) {
    for (const auto& cell : cell_row) {
      if (cell.rectangle.contains(point) && !cell.is_busy) {
        return false;
      }
    }
  }
  return true;
}

void Board::SetBusy(const sf::Vector2f& point, const bool is_busy) {
  for (auto& cell_row : cells_) {
    for (auto& cell : cell_row) {
      if (cell.rectangle.contains(point)) {
        cell.is_busy = is_busy;
      }
    }
  }
}

void Board::SetBusy(const sf::Vector2f& point, const bool is_busy,
                    const FigureColor color) {
  for (auto& cell_row : cells_) {
    for (auto& cell : cell_row) {
      if (cell.rectangle.contains(point)) {
        cell.is_busy = is_busy;
        cell.color = color;
      }
    }
  }
}

Cell Board::GetCell(const int row, const int column) const {
  return cells_.at(row).at(column);
}

Cell Board::GetCell(const sf::Vector2f& point) const {
  for (const auto& cell_row : cells_) {
    for (const auto& cell : cell_row) {
      if (cell.rectangle.contains(point)) {
        return cell;
      }
    }
  }
  return Cell();
}


sf::Vector2f Board::ConvertToBoardPosition(const sf::Vector2f& point) {
  for (auto& cell_row : cells_) {
    for (auto& cell : cell_row) {
      if (cell.rectangle.contains(point)) {
        sf::Vector2f board_position(cell.rectangle.left + constants::kXOffset,
                                    cell.rectangle.top + constants::kYOffset);
        return board_position;
      }
    }
  }
  return sf::Vector2f();
}

sf::Vector2i Board::GetPointLocation(const sf::Vector2f& point) const {
  for (size_t i = 0; i < constants::kRows; ++i) {
    for (size_t j = 0; j < constants::kColumns; ++j) {
      if (cells_[i][j].rectangle.contains(point)) {
        return sf::Vector2i(i, j);
      }
    }
  }
  return sf::Vector2i(-1, -1);
}

sf::Vector2i Board::GetCellCoordinates(Cell cell) const {
  for (size_t i = 0; i < cells_.size(); ++i) {
    for (size_t j = 0; j < cells_.size(); ++j) {
      if (cell == cells_[i][j]) {
        return sf::Vector2i(i, j);
      }
    }
  }
  return sf::Vector2i(-1, -1);
}

std::vector<std::vector<Cell>> Board::GetCells() const { return cells_; }

bool Cell::operator==(const Cell& right) {
  return this->rectangle == right.rectangle;
}

bool Cell::operator!=(const Cell& right) {
  return this->rectangle != right.rectangle;
}
