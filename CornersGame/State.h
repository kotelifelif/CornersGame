#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

enum class GameStateType
{
	kNoState,
	kMenuState,
	kBlackGameState,
	kWhiteGameState,
	kWinnerState
};

class State
{
public:
	State() = default;
	virtual ~State() = default;
	virtual void Draw(RenderWindow& window) = 0;
	virtual GameStateType Update(Event& event, RenderWindow& window) = 0;
};

