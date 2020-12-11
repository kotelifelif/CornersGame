#include "MenuState.h"
#include "Constants.h"

using namespace constants;

MenuState::MenuState() {
	// Texture and Sprite for board
	board_texture_.loadFromFile("../images/board.png");
	board_ = Board(board_texture_, Vector2i(kInitialPositionX, kInitialPositionY));

	// Texture for white figure
	figure_texture_.loadFromFile("../images/figures.png");
	
	black_figure_ = Figure(figure_texture_, IntRect(kPersonFigureStartPositionX, kPersonFigureStartPositionY, kFigureWidth, kFigureHeight), Vector2f(kPersonPositionInCellX + 3 * kCellSizeX, kPersonPositionInCellY + 4 * kCellSizeY));
	white_figure_ = Figure(figure_texture_, IntRect(kAiFigureStartPositionX, kAiFigureStartPositionY, kFigureWidth, kFigureHeight), Vector2f(kPersonPositionInCellX + 4 * kCellSizeX, kPersonPositionInCellY + 4 * kCellSizeY));

	font_.loadFromFile("../fonts/arial.ttf");
	text_.setFont(font_);
	text_.setString(L"Выбери фигуру");
	text_.setCharacterSize(24);
	text_.setPosition(Vector2f(kPersonPositionInCellX + 2 * kCellSizeX, kPersonPositionInCellY + 3 * kCellSizeY));

}

MenuState::~MenuState()
{
}

void MenuState::Draw(RenderWindow& window) {
	board_.Draw(window);
	black_figure_.Draw(window);
	white_figure_.Draw(window);
	window.draw(text_);
}

GameStateType MenuState::Update(Event& event, RenderWindow& window) {
		if (event.type == Event::MouseButtonPressed) {
			if (event.key.code == Mouse::Left) {
				if (black_figure_.GetSprite().getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
					return GameStateType::kBlackGameState;
				}
				else if (white_figure_.GetSprite().getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
					return GameStateType::kWhiteGameState;
				}
			}
		}

		return GameStateType::kNoState;
}
