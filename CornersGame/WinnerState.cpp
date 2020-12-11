#include "WinnerState.h"

#include "Constants.h"

using namespace sf;
using namespace std;
using namespace constants;

WinnerState::WinnerState()
{
	// Texture and Sprite for board
	board_texture_.loadFromFile("../images/board.png");
	board_ = Board(board_texture_, Vector2i(kInitialPositionX, kInitialPositionY));

	font_.loadFromFile("../fonts/arial.ttf");
	congratulatory_text_.setFont(font_);
	// Or computer?
	congratulatory_text_.setString(L"Вы победили!");
	congratulatory_text_.setCharacterSize(24);
	congratulatory_text_.setPosition(Vector2f(kPersonPositionInCellX + 2 * kCellSizeX, kPersonPositionInCellY + 3 * kCellSizeY));

	menu_text_.setFont(font_);
	menu_text_.setString(L"Перейти в меню");
	menu_text_.setCharacterSize(24);
	menu_text_.setPosition(Vector2f(kPersonPositionInCellX + 2 * kCellSizeX, kPersonPositionInCellY + 4 * kCellSizeY));
}

WinnerState::~WinnerState()
{
}

void WinnerState::Draw(RenderWindow& window)
{
	board_.Draw(window);
	window.draw(congratulatory_text_);
	window.draw(menu_text_);
}

GameStateType WinnerState::Update(Event& event, RenderWindow& window)
{
	if (event.type == Event::MouseButtonPressed) {
		if (event.key.code == Mouse::Left) {

		}
	}

	if (event.type == Event::MouseButtonReleased) {
		if (event.key.code == Mouse::Left) {
		}
	}
	return GameStateType::kNoState;
}
