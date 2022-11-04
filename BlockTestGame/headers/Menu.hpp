#pragma once
#include <fstream>
#include "SFML/Graphics.hpp"
#include "Constants.hpp"
#include "SoundManager.hpp"

class Menu
{
public:
	Menu();
	virtual ~Menu();
	void ShowMenu(sf::RenderWindow* window);
	bool  LaunchGame();
	std::string GetCurrentHigherScore();
	void HandleEvent(sf::Event event);
	void HandleKeyReleased(sf::Keyboard::Key key);
	bool Exit();
private:
	int _selected_item;
	sf::Font _font;
	sf::Text _menu_voices_text[MENU_OPTIONS_NUMBER];
	sf::Text _game_title_text;
	sf::Text _high_score_text;
	bool _exit;
	bool _launch_game;
};


bool inline Menu::Exit()
{
	return _exit;
}

bool inline Menu::LaunchGame()
{
	return _launch_game;
}