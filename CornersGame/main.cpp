#include "Player.h"
#include "Board.h"
#include "GameManager.h"
#include "AI.h"
#include "GameState.h"
#include "MenuState.h"
#include "WinnerState.h"
#include "GameContext.h"

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

#include <SFML/Graphics.hpp>

#include "Constants.h"

using namespace sf;
using namespace std;
using namespace constants;



int main()
{
	const string kWindowName("The Corners game");
	RenderWindow window(VideoMode(kWindowWidth, kWindowHeight), kWindowName);

	
	GameContext context(new MenuState());
	//GameState state(false, window);
	//MenuState state(window);
	//WinnerState state(window);


	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			//state.Update(event, window);
			context.Update(event, window);
		}


		window.clear(Color::White);
		context.Draw(window);
		//state.Draw(window);

		window.display();
	}

	return 0;
}