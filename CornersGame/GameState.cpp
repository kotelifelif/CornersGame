#include "GameState.h"
#include "AI.h"

#include <SFML/Graphics.hpp>

#include "Constants.h"

using namespace constants;
using namespace sf;
using namespace std;



GameState::GameState(bool is_white) : 
	ai()
{
	// Texture and Sprite for board
	board_texture_.loadFromFile("../images/board.png");
	board_ = Board(board_texture_, Vector2i(kInitialPositionX, kInitialPositionY));

	// Texture for white figure
	figure_texture_.loadFromFile("../images/figures.png");

	is_white_move_ = true;
	if (is_white) {
		is_player_move_ = true;
		// Create person player
		person_player_ = Player(InitializeFigures(figure_texture_, IntRect(kAiFigureStartPositionX, kAiFigureStartPositionY, kFigureWidth, kFigureHeight), Vector2i(kAiPositionInCellX, kAiPositionInCellY), board_, false));;
		// Create ai_player
		ai_player_ = Player(InitializeFigures(figure_texture_, IntRect(kPersonFigureStartPositionX, kPersonFigureStartPositionY, kFigureWidth, kFigureHeight), Vector2i(kPersonPositionInCellX, kPersonPositionInCellY), board_, true));
	}
	else {
		is_player_move_ = false;
		// Create person player
		person_player_ = Player(InitializeFigures(figure_texture_, IntRect(kPersonFigureStartPositionX, kPersonFigureStartPositionY, kFigureWidth, kFigureHeight), Vector2i(kPersonPositionInCellX, kPersonPositionInCellY), board_, true));
		// Create ai_player
		ai_player_ = Player(InitializeFigures(figure_texture_, IntRect(kAiFigureStartPositionX, kAiFigureStartPositionY, kFigureWidth, kFigureHeight), Vector2i(kAiPositionInCellX, kAiPositionInCellY), board_, false));
	}

}

GameState::~GameState()
{
}

void GameState::Draw(RenderWindow& window)
{
	board_.Draw(window);
	ai_player_.Draw(window);
	person_player_.Draw(window);
}


GameStateType GameState::Update(Event& event, RenderWindow& window)
{

	if (!is_white_move_) {
		if (event.type == Event::MouseButtonPressed) {
			if (event.key.code == Mouse::Left) {
				Vector2i mouse_position = Mouse::getPosition(window);
				std::vector<Figure> person_figures = person_player_.GetFigures();
				for (size_t i = 0; i < person_figures.size(); ++i) {
					auto rect = person_figures[i].GetSprite().getGlobalBounds();
					if (person_figures[i].GetSprite().getGlobalBounds().contains(mouse_position.x, mouse_position.y)) {
						n = i;
						is_player_move_ = true;
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
				pair<int, int> old_position_coordinates = board_.GetPointLocation(old_position);
				pair<int, int> mouse_position_coordinates = board_.GetPointLocation(Vector2f(Mouse::getPosition(window)));
				dx = abs(mouse_position_coordinates.first - old_position_coordinates.first);
				dy = abs(mouse_position_coordinates.second - old_position_coordinates.second);
				if ((!board_.GetBusy(new_position)) && ((dx == 1 && dy == 0) || (dy == 1 && dx == 0))) {
					board_.SetBusy(old_position, false);
					board_.SetBusy(new_position, true);
					board_.SetCollor(new_position, FigureColor::kBlack);
					board_.SetCollor(old_position, FigureColor::kNone);
					new_position = board_.ConvertToBoardPosition(new_position);
					if (is_white_move_) {
						ai_player_.SetFigurePosition(n, new_position);
					}
					else {
						person_player_.SetFigurePosition(n, new_position);
						is_white_move_ = true;
					}
				}
			}
		}

		if (event.type == Event::KeyPressed) {
			if (event.key.code == Keyboard::Up) {
				Vector2f p = new_figure.GetSprite().getPosition();
				new_position = Vector2f(p.x, p.y - kCellSizeY);
				if (!board_.GetBusy(new_position)) {
					board_.SetBusy(old_position, false);
					board_.SetBusy(new_position, true);
					if (is_white_move_) {
						ai_player_.SetFigurePosition(n, new_position);
					}
					else {
						person_player_.SetFigurePosition(n, new_position);
					}

				}

			}
			else if (event.key.code == Keyboard::Left) {
				Vector2f p = new_figure.GetSprite().getPosition();
				new_position = Vector2f(p.x - kCellSizeX, p.y);
				if (!board_.GetBusy(new_position)) {
					board_.SetBusy(old_position, false);
					board_.SetBusy(new_position, true);
					if (is_white_move_) {
						ai_player_.SetFigurePosition(n, new_position);
					}
					else {
						person_player_.SetFigurePosition(n, new_position);
					}
				}

			}
			else if (event.key.code == Keyboard::Right) {
				is_white_move_ = false;
				Vector2f p = new_figure.GetSprite().getPosition();
				new_position = Vector2f(p.x + kCellSizeX, p.y);
				if (!board_.GetBusy(new_position)) {
					board_.SetBusy(old_position, false);
					board_.SetBusy(new_position, true);
					if (is_white_move_) {
						ai_player_.SetFigurePosition(n, new_position);
					}
					else {
						person_player_.SetFigurePosition(n, new_position);
					}
				}

			}
			else if (event.key.code == Keyboard::Down) {
				is_white_move_ = false;
				Vector2f p = new_figure.GetSprite().getPosition();
				new_position = Vector2f(p.x, p.y + kCellSizeY);
				if (!board_.GetBusy(new_position)) {
					board_.SetBusy(old_position, false);
					board_.SetBusy(new_position, true);
					if (is_white_move_) {
						ai_player_.SetFigurePosition(n, new_position);
					}
					else {
						person_player_.SetFigurePosition(n, new_position);
					}
				}
			}
		}
	}
	else {
		std::vector<Figure> ai_figures = ai_player_.GetFigures();
		std::pair<sf::Vector2i, int> optimal_path = ai.FindBestMove(board_, ai_player_);

		Cell position = board_.GetCell(optimal_path.first.x, optimal_path.first.y);
		sf::Vector2f figure_position(position.rectangle.left + kXOffset, position.rectangle.top + kYOffset);

		board_.SetBusy(ai_figures[optimal_path.second].getPosition(), false);
		board_.SetCollor(ai_figures[optimal_path.second].getPosition(), FigureColor::kNone);
		ai_player_.SetFigurePosition(optimal_path.second, figure_position);

		board_.SetBusy(figure_position, true);
		board_.SetCollor(figure_position, FigureColor::kWhite);

		is_white_move_ = false;
	}

	return GameStateType::kNoState;
}


vector<Figure> GameState::InitializeFigures(const Texture& texture, const IntRect& rectangle, const Vector2i& initial_position,
	Board& board, bool is_left_top) {

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