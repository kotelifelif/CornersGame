#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

struct Cell
{
	bool is_busy;
	sf::FloatRect rectangle;
};

class Board
{
public:
	Board(const sf::Texture& texture, const sf::Vector2i& initial_position);
	Board();
	void Draw(sf::RenderWindow& window) const;
	void SetBusy(const int row, const int column, const bool is_busy);
	bool GetBusy(const int row, const int column) const;
	
	// Maybe rename
	bool GetBusy(const sf::Vector2f& point) const;
	void SetBusy(const sf::Vector2f& point, const bool is_busy);
	
	sf::Vector2f ConvertToBoardPosition(const sf::Vector2f& point);
private:
	std::vector <std::vector<Cell>> cells_;
	sf::Sprite sprite_;
};

