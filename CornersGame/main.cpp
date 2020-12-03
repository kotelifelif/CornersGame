#include "Player.h"

#include <vector>
#include <iostream>

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

	RenderWindow window(VideoMode(500, 500), "The Game!");

	// Texture and Sprite for board
	Texture board_texture;	
	board_texture.loadFromFile("../images/board.png");
	Sprite boardSprite(board_texture);

	// Texture for white figure
	Texture figure_texture;
	figure_texture.loadFromFile("../images/figures.png");
	
	// Sprite for black figure
	Sprite black_figure_sprite(figure_texture, IntRect(294, 6, 28, 50));
	vector<Figure> black_figures = InitializeFigures(figure_texture, IntRect(294, 6, 28, 50), Vector2i(42, 31));

	// Sprite for white figure
	Sprite white_figure_sprite(figure_texture, IntRect(294, 62, 28, 50));
	vector<Figure> white_figures = InitializeFigures(figure_texture, IntRect(294, 62, 28, 50), Vector2i(322, 311));

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

		for (Figure &black_figure : black_figures) {
			black_figure.Draw(window);
		}

		for (Figure& white_figure : white_figures) {
			white_figure.Draw(window);
		}

		window.display();
	}

	return 0;
}