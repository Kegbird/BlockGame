#include "headers/GameManager.hpp"

GameManager::GameManager()
{
	_video_mode.height = SCREEN_HEIGHT;
	_video_mode.width = SCREEN_WIDTH;
	_window = new sf::RenderWindow(this->_video_mode, GAME_NAME_TEXT, sf::Style::Titlebar | sf::Style::Close);
	_game_state = MENU;
	_game_logic = nullptr;
	_game_over = nullptr;
	_event = sf::Event();
	_menu = new Menu();
}

GameManager::~GameManager()
{
	delete _window;
	SoundManager* sound_manager = SoundManager::GetInstance();
	sound_manager->Delete();

	switch (_game_state)
	{
	case MENU:
		delete _menu;
		break;
	case GAME:
		delete _game_logic;
		break;
	default:
		delete _game_over;
		break;
	}
}

void GameManager::InputProcessing()
{
	while (_window->pollEvent(_event))
	{
		switch (_game_state)
		{
			case MENU:
				_menu->HandleEvent(_event);
				break;
			case GAME:
				_game_logic->HandleEvent(_event, _window);
				break;
			case GAME_OVER:
				_game_over->HandleEvent(_event);
				break;
		}

		if (_event.type == sf::Event::Closed)
			_window->close();
	}
}

void GameManager::Update()
{
	switch (_game_state)
	{
	case MENU:
		if (_menu->LaunchGame())
		{
			delete _menu;
			_game_logic = new GameLogic(GRID_POSITION, GAME_ROWS, GAME_COLUMNS);
			_game_state = GAME;
			_game_logic->StartGame();
		}
		else if (_menu->Exit())
		{
			_window->close();
		}
		break;
	case GAME:
		_game_logic->Update();
		if (_game_logic->GameOver())
		{
			unsigned int final_score = _game_logic->GetScore();
			delete _game_logic;
			_game_state = GAME_OVER;
			_game_over = new GameOver();
			_game_over->SetFinalScore(final_score);
			_game_over->WriteFinalScore(final_score);
		}
		else if (_game_logic->Exit())
		{
			_window->close();
		}
		break;
	case GAME_OVER:
		if (_game_over->ReturnToMenu())
		{
			delete _game_over;
			_game_state = MENU;
			_menu = new Menu();
		}
		else if (_game_over->Exit())
		{
			_window->close();
		}
		break;
	}
}

void GameManager::Render()
{
	_window->clear();
	switch (_game_state)
	{
	case MENU:
		_menu->ShowMenu(_window);
		break;
	case GAME:
		_game_logic->ShowGame(_window);
		break;
	default:
		_game_over->ShowGameOver(_window);
		break;
	}
	_window->display();
}

