#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;


int main()
{

	RenderWindow window(VideoMode(320, 480), "The Game!");



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
		window.display();
	}

	return 0;
}