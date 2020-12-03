#include "Player.h"

#include <vector>
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

vector<Figure> InitializeFigures(const Texture &texture, const IntRect &rectangle, const Vector2i &initial_position) {
	constexpr int kFigureRows = 3;
	constexpr int kFigureColumns = 3;
	constexpr int kXOffset = 56;
	constexpr int kYOffset = 56;

	vector<Figure> figures;
	for (int i = 0; i < kFigureRows; ++i) {
		for (int j = 0; j < kFigureColumns; ++j) {
			Figure f(texture, rectangle, Vector2f(initial_position.x + i * kXOffset, initial_position.y + j * kYOffset));
			figures.push_back(f);
		}
	}
	return figures;
}

int main()
{
	constexpr int kWindowWidth = 500;
	constexpr int kWindowHeight = 500;
	const string kWindowName("The Corners game");
	RenderWindow window(VideoMode(kWindowWidth, kWindowHeight), kWindowName);

	// Texture and Sprite for board
	Texture board_texture;	
	board_texture.loadFromFile("../images/board.png");
	Sprite boardSprite(board_texture);

	// Texture for white figure
	Texture figure_texture;
	figure_texture.loadFromFile("../images/figures.png");
	
	// Create person player
	constexpr int kPersonFigureStartPositionX = 294;
	constexpr int kPersonFigureStartPositionY = 6;
	constexpr int kPersonPositionInCellX = 42;
	constexpr int kPersonPositionInCellY = 31;
	constexpr int kFigureWidth = 28;
	constexpr int kFigureHeight = 50;
	Player person_player(InitializeFigures(figure_texture, IntRect(kPersonFigureStartPositionX, kPersonFigureStartPositionY, kFigureWidth, kFigureHeight), Vector2i(kPersonPositionInCellX, kPersonPositionInCellY)));

	// Create ai_player
	constexpr int kAiFigureStartPositionX = 294;
	constexpr int kAiFigureStartPositionY = 62;
	constexpr int kAiPositionInCellX = 322;
	constexpr int kAiPositionInCellY = 311;
	Player ai_player(InitializeFigures(figure_texture, IntRect(kAiFigureStartPositionX, kAiFigureStartPositionY, kFigureWidth, kFigureHeight), Vector2i(kAiPositionInCellX, kAiPositionInCellY)));

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Up) cout << "Up";
				else if (event.key.code == Keyboard::Left) cout << "Left";
				else if (event.key.code == Keyboard::Right) cout << "Right";
			}
		}


		window.clear(Color::White);
		window.draw(boardSprite);
		
		ai_player.Draw(window);
		person_player.Draw(window);

		window.display();
	}

	return 0;
}