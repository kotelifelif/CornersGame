#pragma once
#include "Figure.h"

#include <vector>

class Player
{
public:
	Player();
	Player(const std::vector<Figure>& figures);
	void Draw(RenderWindow& window) const;
	std::vector<Figure> GetFigures() const;
	Figure GetFigure(const int position) const;
	void SetFigurePosition(const int figure_number, const Vector2f &screen_position);
private:
	std::vector<Figure> figures_;

};

