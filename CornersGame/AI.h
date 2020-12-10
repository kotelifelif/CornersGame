#pragma once
#include "Board.h"
#include "Player.h"

#include <vector>

#include <SFML/Graphics.hpp>

class AI
{
public:
	std::pair<sf::Vector2i, int> FindBestMove(Board& board, Player& player);
	std::vector<Cell> GetShortestPath(Board& board, Cell source_cell, Cell destination_cell);
};

