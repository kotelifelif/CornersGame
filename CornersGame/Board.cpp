#include "Board.h"

#include <SFML/Graphics.hpp>

#include "Constants.h"

using namespace constants;

Board::Board(const sf::Texture& texture, const sf::Vector2i& initial_position) :
	sprite_(texture)
{
	cells_.resize(kRows);
	for (size_t i = 0; i < kRows; ++i) {
		for (size_t j = 0; j < kColumns; ++j) {
			Cell cell;
			cell.is_busy = false;
			cell.color = FigureColor::kNone;
			cell.rectangle = sf::FloatRect(initial_position.x + i * kCellSizeX, initial_position.y + j * kCellSizeY, kCellSizeX, kCellSizeY);
			cells_[i].push_back(cell);
		}
	}
}

Board::Board()
{
	
}

void Board::Draw(sf::RenderWindow& window) const
{
	window.draw(sprite_);
}

void Board::SetBusy(const int row, const int column, const bool is_busy)
{
	cells_.at(row).at(column).is_busy = is_busy;
}

bool Board::GetBusy(const int row, const int column) const
{
	return cells_.at(row).at(column).is_busy;
}

bool Board::GetBusy(const sf::Vector2f& point) const
{
	for (const auto& cell_row : cells_) {
		for (const auto& cell : cell_row) {
			if (cell.rectangle.contains(point) && !cell.is_busy) {
				return false;
			}
		}
	}
	return true;
}

void Board::SetBusy(const sf::Vector2f& point, const bool is_busy)
{
	// Maybe add find from std::algorithm
	for (auto& cell_row : cells_) {
		for (auto& cell : cell_row) {
			if (cell.rectangle.contains(point)) {
				cell.is_busy = is_busy;
			}
		}
	}
}

Cell Board::GetCell(const int row, const int column) const
{
	return cells_.at(row).at(column);
}

Cell Board::GetCell(const sf::Vector2f& point) const
{
	for (const auto& cell_row : cells_) {
		for (const auto& cell : cell_row) {
			if (cell.rectangle.contains(point)) {
				return cell;
			}
		}
	}
	return Cell();
}

void Board::SetCollor(const int row, const int column, const FigureColor color)
{
	cells_.at(row).at(column).color = color;
}

void Board::SetCollor(const sf::Vector2f& point, const FigureColor color)
{
	for (auto& cell_row : cells_) {
		for (auto& cell : cell_row) {
			if (cell.rectangle.contains(point)) {
				cell.color = color;
			}
		}
	}
}

sf::Vector2f Board::ConvertToBoardPosition(const sf::Vector2f& point)
{
	// Maybe add find from std::algorithm
	for (auto& cell_row : cells_) {
		for (auto& cell : cell_row) {
			if (cell.rectangle.contains(point)) {
				// Add constants
				sf::Vector2f board_position(cell.rectangle.left + kXOffset, cell.rectangle.top + kYOffset);
				return board_position;
			}
		}
	}
	return sf::Vector2f();
}

std::pair<int, int> Board::GetPointLocation(const sf::Vector2f& point) const
{
	for (size_t i = 0; i < kRows; ++i) {
		for (size_t j = 0; j < kColumns; ++j) {
			if (cells_[i][j].rectangle.contains(point)) {
				return std::make_pair(i, j);
			}
		}
	}
	return std::pair<int, int>();
}

std::pair<int, int> Board::GetCellCoordinats(Cell cell) const
{
	for (size_t i = 0; i < cells_.size(); ++i) {
		for (size_t j = 0; j < cells_.size(); ++j) {
			if (cell == cells_[i][j]) {
				return std::make_pair(i, j);
			}
		}
	}
	return std::pair<int, int>();
}

std::vector<std::vector<Cell>> Board::GetCells() const
{
	return cells_;
}

bool Cell::operator==(const Cell right)
{
	return this->rectangle == right.rectangle;
}

bool Cell::operator!=(const Cell right)
{
	return this->rectangle != right.rectangle;
}
