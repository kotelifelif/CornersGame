#pragma once
#include "Board.h"
#include "Player.h"

#include <vector>

#include <SFML/Graphics.hpp>

class AI
{
public:
	std::pair<sf::Vector2i, int> FindBestMove(const Board& board, const Player& player);
	std::vector<Cell> GetShortestPath(const Board& board, const Cell &source_cell, const Cell &destination_cell);
};

