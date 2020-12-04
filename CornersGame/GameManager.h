#pragma once
#include "Player.h"
#include "Figure.h"
#include "Board.h"

#include <SFML/Graphics.hpp>

class GameManager
{
public:
	static void MoveFigure(const Figure &figure, const Board &board, sf::Vector2f &new_position);
};

