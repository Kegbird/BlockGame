#pragma once
#include "SFML/Graphics.hpp"
#include "Constants.hpp"
#include "Menu.hpp"
#include "GameLogic.hpp"
#include "GameOver.hpp"
#include "SoundManager.hpp"

class GameManager
{
	private:
	public:
		GameManager();
		virtual ~GameManager();
		void InputProcessing();
		void Update();
		void Render();
		bool IsRunning();
private:
	sf::RenderWindow* _window;
	sf::VideoMode _video_mode;
	sf::Event _event;
	Menu* _menu;
	GameLogic* _game_logic;
	GameOver* _game_over;
	GameState _game_state;
};

inline bool GameManager::IsRunning()
{
	if (_window == nullptr)
		return false;
	return _window->isOpen();
}