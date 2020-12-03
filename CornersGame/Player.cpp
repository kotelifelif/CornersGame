#include "Player.h"

#include <SFML/Graphics.hpp> 

using namespace std;
using namespace sf;

Player::Player(const vector<Figure>& figures) :
	figures_(figures)
{
}

void Player::Draw(RenderWindow& window) const
{
	for (const auto& figure : figures_) {
		figure.Draw(window);
	}
}
