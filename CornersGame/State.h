#pragma once
#include <SFML/Graphics.hpp>

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
	virtual void Draw(sf::RenderWindow& window) = 0;
	virtual GameStateType Update(sf::Event& event, sf::RenderWindow& window) = 0;
};

