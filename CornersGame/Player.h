#pragma once
#include "Figure.h"

#include <vector>

class Player
{
public:
	Player(const std::vector<Figure>& figures);
	void Draw(RenderWindow& window) const;
private:
	std::vector<Figure> figures_;
};

