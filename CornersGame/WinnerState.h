#pragma once
#include "State.h"
#include "Board.h"
#include "Player.h"
#include "AI.h"

#include <vector>

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class WinnerState : public State
{
public:
	WinnerState();
	virtual ~WinnerState();
	void Draw(RenderWindow& window) override;
	GameStateType Update(Event& event, RenderWindow& window) override;
private:
	Font font_;
	sf::Text congratulatory_text_;
	sf::Text menu_text_;
	Texture board_texture_;
	Board board_;
};
