#include "headers/Menu.hpp"

Menu::Menu()
{
	_font.loadFromFile(MENU_FONT);

	_game_title_text.setFont(_font);
	_game_title_text.setString(GAME_NAME_TEXT);
	_game_title_text.setFillColor(GAME_TITLE_COLOR);
	_game_title_text.setPosition(GAME_TITLE_POSITION);
	_game_title_text.setCharacterSize(GAME_TITLE_CHARACTER_SIZE);


	for (int i = 0; i < MENU_OPTIONS_NUMBER; i++)
	{
		_menu_voices_text[i].setFont(_font);
		_menu_voices_text[i].setString(MENU_OPTIONS_TEXT[i]);
		_menu_voices_text[i].setFillColor(MENU_OPTION_DEFAULT_COLOR);
		_menu_voices_text[i].setPosition(MENU_OPTIONS_POSITIONS[i]);
		_menu_voices_text[i].setCharacterSize(MENU_OPTIONS_CHARACTER_SIZE);
	}
	if (MENU_OPTIONS_NUMBER > 0)
		_menu_voices_text[0].setFillColor(MENU_OPTION_SELECTED_COLOR);

	_high_score_text.setFont(_font);
	_high_score_text.setFillColor(HIGH_SCORE_COLOR);
	_high_score_text.setPosition(HIGH_SCORE_POSITION);
	_high_score_text.setCharacterSize(HIGH_SCORE_CHARACTER_SIZE);

	std::string current_high_score = GetCurrentHigherScore();
	if(current_high_score.length()>0)
		_high_score_text.setString(HIGH_SCORE_TEXT+current_high_score);

	_selected_item = 0;
	_exit = false;
	_launch_game = false;
}

Menu::~Menu()
{

}

void Menu::ShowMenu(sf::RenderWindow* window)
{
	window->draw(_game_title_text);
	window->draw(_high_score_text);
	for (int i = 0; i < MENU_OPTIONS_NUMBER; i++)
		window->draw(_menu_voices_text[i]);
}

void Menu::HandleEvent(sf::Event event)
{
	switch (event.type)
	{
	case sf::Event::KeyReleased:
		HandleKeyReleased(event.key.code);
		break;
	}
}

std::string Menu::GetCurrentHigherScore()
{
	int max = 0;
	int tmp = 0;
	std::string score;
	std::fstream file(FINAL_SCORES_FILE);
	while (getline(file, score))
	{
		try
		{
			tmp = std::stoi(score);
			if (tmp > max)
				max = tmp;
		}
		catch (std::exception e)
		{
			continue;
		}
	}

	if (max > 0)
		return std::to_string(max);
	return "";
}

void Menu::HandleKeyReleased(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::Up:
		_menu_voices_text[_selected_item].setFillColor(MENU_OPTION_DEFAULT_COLOR);
		_selected_item = _selected_item + 1 >= MENU_OPTIONS_NUMBER ? 0 : _selected_item + 1;
		_menu_voices_text[_selected_item].setFillColor(MENU_OPTION_SELECTED_COLOR);
		break;
	case sf::Keyboard::Down:
		_menu_voices_text[_selected_item].setFillColor(MENU_OPTION_DEFAULT_COLOR);
		_selected_item = _selected_item - 1 < 0 ? MENU_OPTIONS_NUMBER-1 : _selected_item - 1;
		_menu_voices_text[_selected_item].setFillColor(MENU_OPTION_SELECTED_COLOR);
		break;
	case sf::Keyboard::Escape:
		_exit = true;
		break;
	case sf::Keyboard::Enter:
		SoundManager* sound_manager = SoundManager::GetInstance();
		sound_manager->PlaySound(BUTTON_SOUND);
		if (_selected_item == EXIT_OPTION)
			_exit = true;
		else
			_launch_game = true;
		break;
	}
}
