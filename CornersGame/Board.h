#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

enum class FigureColor { kNone, kWhite, kBlack };

struct Cell {
  bool is_busy{};
  sf::FloatRect rectangle;
  FigureColor color{};
  bool operator==(const Cell& right);
  bool operator!=(const Cell& right);
};

class Board {
 public:
  Board(const sf::Texture& texture, const sf::Vector2i& initial_position);
  Board();
  
  void Draw(sf::RenderWindow& window) const;
  
  void SetBusy(const int row, const int column, const bool is_busy);
  void SetBusy(const int row, const int column, const bool is_busy,
               const FigureColor color);
  bool GetBusy(const int row, const int column) const;

  bool GetBusy(const sf::Vector2f& point) const;
  void SetBusy(const sf::Vector2f& point, const bool is_busy);
  void SetBusy(const sf::Vector2f& point, const bool is_busy, const FigureColor color);


  Cell GetCell(const int row, const int column) const;
  Cell GetCell(const sf::Vector2f& point) const;

  sf::Vector2f ConvertToBoardPosition(const sf::Vector2f& point);
  sf::Vector2i GetPointLocation(const sf::Vector2f& point) const;
  sf::Vector2i GetCellCoordinates(Cell cell) const;

  std::vector<std::vector<Cell>> GetCells() const;

 private:
  std::vector<std::vector<Cell>> cells_;
  sf::Sprite sprite_;
};

