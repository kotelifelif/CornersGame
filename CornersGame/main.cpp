#include "Player.h"
#include "Board.h"
#include "GameManager.h"
#include "AI.h"

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

#include <SFML/Graphics.hpp>

#include "Constants.h"

using namespace sf;
using namespace std;
using namespace constants;

vector<Figure> InitializeFigures(const Texture &texture, const IntRect &rectangle, const Vector2i &initial_position,
								 Board &board, bool is_left_top) {

	vector<Figure> figures;
	for (int i = 0; i < kFigureRows; ++i) {
		for (int j = 0; j < kFigureColumns; ++j) {
			Figure player_figure(texture, rectangle, Vector2f(initial_position.x + i * kCellSizeX, initial_position.y + j * kCellSizeY));
			if (is_left_top) {
				player_figure.SetTargetCell(board.GetCell(kRows - i - 1, kColumns - j - 1));
				board.SetBusy(i, j, true);
				board.SetCollor(i, j, FigureColor::kWhite);
			}
			else {
				player_figure.SetTargetCell(board.GetCell(i, j));
				board.SetBusy(kRows - i - 1, kColumns - j - 1, true);
				board.SetCollor(i, j, FigureColor::kBlack);
			}
			figures.push_back(player_figure);
		}
	}
	return figures;
}

int main()
{
	const string kWindowName("The Corners game");
	RenderWindow window(VideoMode(kWindowWidth, kWindowHeight), kWindowName);

	// Texture and Sprite for board
	Texture board_texture;	
	board_texture.loadFromFile("../images/board.png");
	Board board(board_texture, Vector2i(kInitialPositionX, kInitialPositionY));

	// Texture for white figure
	Texture figure_texture;
	figure_texture.loadFromFile("../images/figures.png");
	
	// Create person player
	Player person_player(InitializeFigures(figure_texture, IntRect(kPersonFigureStartPositionX, kPersonFigureStartPositionY, kFigureWidth, kFigureHeight), Vector2i(kPersonPositionInCellX, kPersonPositionInCellY), board, true));

	// Create ai_player
	Player ai_player(InitializeFigures(figure_texture, IntRect(kAiFigureStartPositionX, kAiFigureStartPositionY, kFigureWidth, kFigureHeight), Vector2i(kAiPositionInCellX, kAiPositionInCellY), board, false));
	std::vector<Figure> figures = ai_player.GetFigures();
	for (int i = 0; i < figures.size(); ++i) {
		Cell cell = figures[i].GetTargetCell();
		auto location = board.GetCellCoordinats(cell);
		std::cout << location.first << " " << location.second << std::endl;
	}

	bool is_move = false;
	bool is_white = true;
	AI ai;
	// Maybe rename
	int n = 0;
	float dx = 0;
	float dy = 0;
	Vector2f old_position;
	Vector2f new_position;
	Figure new_figure;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (!is_white) {
				if (event.type == Event::MouseButtonPressed) {
					if (event.key.code == Mouse::Left) {
						Vector2i mouse_position = Mouse::getPosition(window);
						std::vector<Figure> person_figures = person_player.GetFigures();
						for (size_t i = 0; i < person_figures.size(); ++i) {
							auto rect = person_figures[i].GetSprite().getGlobalBounds();
							if (person_figures[i].GetSprite().getGlobalBounds().contains(mouse_position.x, mouse_position.y)) {
								n = i;
								is_move = true;
								new_figure = person_figures[i];
								dx = mouse_position.x - person_figures[i].GetSprite().getPosition().x;
								dy = mouse_position.y - person_figures[i].GetSprite().getPosition().y;
								old_position = person_figures[i].GetSprite().getPosition();
							}
						}
					}
				}

				if (event.type == Event::MouseButtonReleased) {
					if (event.key.code == Mouse::Left) {
						Vector2f p = new_figure.GetSprite().getPosition();
						new_position = Vector2f(Mouse::getPosition(window));
						// Maybe Vector2i
						pair<int, int> old_position_coordinates = board.GetPointLocation(old_position);
						pair<int, int> mouse_position_coordinates = board.GetPointLocation(Vector2f(Mouse::getPosition(window)));
						dx = abs(mouse_position_coordinates.first - old_position_coordinates.first);
						dy = abs(mouse_position_coordinates.second - old_position_coordinates.second);
						if ((!board.GetBusy(new_position)) && ((dx == 1 && dy == 0) || (dy == 1 && dx == 0))) {
							board.SetBusy(old_position, false);
							board.SetBusy(new_position, true);
							board.SetCollor(new_position, FigureColor::kBlack);
							board.SetCollor(old_position, FigureColor::kNone);
							new_position = board.ConvertToBoardPosition(new_position);
							if (is_white) {
								ai_player.SetFigurePosition(n, new_position);
							}
							else {
								person_player.SetFigurePosition(n, new_position);
								is_white = true;
							}
						}
					}
				}

				if (event.type == Event::KeyPressed) {
					if (event.key.code == Keyboard::Up) {
						Vector2f p = new_figure.GetSprite().getPosition();
						new_position = Vector2f(p.x, p.y - kCellSizeY);
						if (!board.GetBusy(new_position)) {
							board.SetBusy(old_position, false);
							board.SetBusy(new_position, true);
							if (is_white) {
								ai_player.SetFigurePosition(n, new_position);
							}
							else {
								person_player.SetFigurePosition(n, new_position);
							}

						}

					}
					else if (event.key.code == Keyboard::Left) {
						Vector2f p = new_figure.GetSprite().getPosition();
						new_position = Vector2f(p.x - kCellSizeX, p.y);
						if (!board.GetBusy(new_position)) {
							board.SetBusy(old_position, false);
							board.SetBusy(new_position, true);
							if (is_white) {
								ai_player.SetFigurePosition(n, new_position);
							}
							else {
								person_player.SetFigurePosition(n, new_position);
							}
						}

					}
					else if (event.key.code == Keyboard::Right) {
						is_move = false;
						Vector2f p = new_figure.GetSprite().getPosition();
						new_position = Vector2f(p.x + kCellSizeX, p.y);
						if (!board.GetBusy(new_position)) {
							board.SetBusy(old_position, false);
							board.SetBusy(new_position, true);
							if (is_white) {
								ai_player.SetFigurePosition(n, new_position);
							}
							else {
								person_player.SetFigurePosition(n, new_position);
							}
						}

					}
					else if (event.key.code == Keyboard::Down) {
						is_move = false;
						Vector2f p = new_figure.GetSprite().getPosition();
						new_position = Vector2f(p.x, p.y + kCellSizeY);
						if (!board.GetBusy(new_position)) {
							board.SetBusy(old_position, false);
							board.SetBusy(new_position, true);
							if (is_white) {
								ai_player.SetFigurePosition(n, new_position);
							}
							else {
								person_player.SetFigurePosition(n, new_position);
							}
						}
					}
				}
			}
			else {
				std::vector<Figure> ai_figures = ai_player.GetFigures();
				std::pair<sf::Vector2i, int> optimal_path = ai.FindBestMove(board, ai_player);

				Cell position = board.GetCell(optimal_path.first.x, optimal_path.first.y);
				sf::Vector2f figure_position(position.rectangle.left + kXOffset, position.rectangle.top + kYOffset);
				
				board.SetBusy(ai_figures[optimal_path.second].getPosition(), false);
				board.SetCollor(ai_figures[optimal_path.second].getPosition(), FigureColor::kNone);
				ai_player.SetFigurePosition(optimal_path.second, figure_position);
				
				board.SetBusy(figure_position, true);
				board.SetCollor(figure_position, FigureColor::kWhite);

				is_white = false;
			}
		}


		window.clear(Color::White);
		board.Draw(window);
		
		ai_player.Draw(window);
		person_player.Draw(window);

		window.display();
	}

	return 0;
}