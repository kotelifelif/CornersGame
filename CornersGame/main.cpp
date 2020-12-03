#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;


int main()
{

	RenderWindow window(VideoMode(500, 500), "The Game!");

	// Texture and Sprite for board
	Texture boardTexture;	
	boardTexture.loadFromFile("../images/board.png");
	Sprite boardSprite(boardTexture);

	// Texture for figure
	Texture figureTexture;
	figureTexture.loadFromFile("../images/figures.png");
	
	// Sprite for black figure
	Sprite blackFigureSprite(figureTexture, IntRect(294, 6, 28, 50));
	blackFigureSprite.move(250, 250);

	// Sprite for white figure
	Sprite whiteFigureSprite(figureTexture, IntRect(294, 62, 28, 50));
	whiteFigureSprite.move(400, 400);

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
		window.draw(blackFigureSprite);
		window.draw(whiteFigureSprite);
		window.display();
	}

	return 0;
}