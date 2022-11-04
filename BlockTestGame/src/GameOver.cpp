#include "GameOver.hpp"

GameOver::GameOver()
{
	_font.loadFromFile(MENU_FONT);

	_game_over_text.setOrigin(0.5f, 0.5f);
	_game_over_text.setFont(_font);
	_game_over_text.setString(GAME_OVER_TEXT);
	_game_over_text.setFillColor(GAME_OVER_COLOR);
	_game_over_text.setPosition(GAME_OVER_POSITION);
	_game_over_text.setCharacterSize(GAME_OVER_CHARACTER_SIZE);

	_final_score_text.setOrigin(0.5f, 0.5f);
	_final_score_text.setFont(_font);
	_final_score_text.setFillColor(FINAL_SCORE_COLOR);
	_final_score_text.setPosition(FINAL_SCORE_POSITION);
	_final_score_text.setCharacterSize(FINAL_SCORE_CHARACTER_SIZE);

	_tip_text.setOrigin(0.5f, 0.5f);
	_tip_text.setFont(_font);
	_tip_text.setString(TIP_TEXT);
	_tip_text.setFillColor(TIP_COLOR);
	_tip_text.setPosition(TIP_POSITION);
	_tip_text.setCharacterSize(TIP_CHARACTER_SIZE);

	_exit = _return_to_menu = false;
}

GameOver::~GameOver()
{
}

void  GameOver::SetFinalScore(unsigned int final_score)
{
	_final_score_text.setString(std::to_string(final_score));
}

void GameOver::HandleEvent(sf::Event event)
{
	switch (event.type)
	{
	case sf::Event::KeyReleased:
		HandleKeyReleased(event.key.code);
		break;
	}
}

void GameOver::HandleKeyReleased(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::Escape:
		_exit = true;
		break;
	case sf::Keyboard::Enter:
		SoundManager* sound_manager = SoundManager::GetInstance();
		sound_manager->PlaySound(BUTTON_SOUND);
		_return_to_menu = true;
		break;
	}
}

void GameOver::HandleMouseButtonReleased(sf::Keyboard::Key key)
{
}

void GameOver::WriteFinalScore(unsigned int final_score)
{
	std::fstream file;
	file.open(FINAL_SCORES_FILE, std::ios_base::app | std::ios_base::in);
	if (file.is_open())
		file << final_score << std::endl;
}

void GameOver::ShowGameOver(sf::RenderWindow* window)
{
	window->draw(_game_over_text);
	window->draw(_final_score_text);
	window->draw(_tip_text);
}