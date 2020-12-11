#pragma once
#include "State.h"
#include "Board.h"
#include "Player.h"
#include "AI.h"

#include <vector>

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class GameState : public State
{
public:
	GameState(bool is_white);
	virtual ~GameState();
	void Draw(RenderWindow &window);
	GameStateType Update(Event& event, RenderWindow& window);
private:
	AI ai;
	// Maybe rename
	int n = 0;
	float dx = 0;
	float dy = 0;
	Vector2f old_position;
	Vector2f new_position;
	Figure new_figure;
	bool is_player_move_;
	bool is_white_move_;
	Texture board_texture_;
	Texture figure_texture_;
	Board board_;
	//RenderWindow *window_;
	Player person_player_;
	Player ai_player_;
	vector<Figure> InitializeFigures(const Texture& texture, const IntRect& rectangle, const Vector2i& initial_position,
		Board& board, bool is_left_top);

};

