#pragma once
#include <fstream>
#include "SFML/Graphics.hpp"
#include "Constants.hpp"
#include "SoundManager.hpp"

class GameOver
{
public:
	GameOver();
	virtual ~GameOver();
	void  SetFinalScore(unsigned int final_score);
	void HandleEvent(sf::Event event);
	void HandleKeyReleased(sf::Keyboard::Key key);
	void HandleMouseButtonReleased(sf::Keyboard::Key key);
	void WriteFinalScore(unsigned int final_score);
	void ShowGameOver(sf::RenderWindow* window);
	bool  Exit();
	bool ReturnToMenu();
private:
	sf::Font _font;
	sf::Text _game_over_text;
	sf::Text _final_score_text;
	sf::Text _tip_text;
	bool _exit;
	bool _return_to_menu;
};

bool inline GameOver::Exit()
{
	return _exit;
}

inline bool GameOver::ReturnToMenu()
{
	return _return_to_menu;
}