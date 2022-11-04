#pragma once
#include<iostream>
#include<string>
#include "headers/SFML/Graphics.hpp"

//WINDOW VALUES
const std::string GAME_NAME_TEXT = "Block Game";
const unsigned int SCREEN_WIDTH = 1280;
const unsigned int SCREEN_HEIGHT = 720;

//MENU VALUES
const std::string MENU_FONT = "fonts/Uncracked.otf";
const unsigned int MENU_OPTIONS_NUMBER = 2;
const std::string MENU_OPTIONS_TEXT[] = {"Play", "Quit"};
const std::string HIGH_SCORE_TEXT = "Higher score ";
const unsigned int GAME_TITLE_CHARACTER_SIZE = 150;
const unsigned int HIGH_SCORE_CHARACTER_SIZE = 50;
const sf::Vector2f GAME_TITLE_POSITION = sf::Vector2f(SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT/5.0f);
const sf::Vector2f MENU_OPTIONS_POSITIONS[] = { sf::Vector2f(3.0*SCREEN_WIDTH/4.0f, SCREEN_HEIGHT / 4.0f ), 
												sf::Vector2f(3.0 * SCREEN_WIDTH / 4.0f, (SCREEN_HEIGHT / 4.0f) * 2.0f) };
const sf::Vector2f HIGH_SCORE_POSITION = sf::Vector2f(SCREEN_WIDTH / 4.0f, 2.0f*SCREEN_HEIGHT / 5.0f);
const unsigned int MENU_OPTIONS_CHARACTER_SIZE = 100;
const unsigned int PLAY_OPTION = 0;
const unsigned int EXIT_OPTION = 1;
const sf::Color GAME_TITLE_COLOR = sf::Color::White;
const sf::Color MENU_OPTION_DEFAULT_COLOR = sf::Color::White;
const sf::Color MENU_OPTION_SELECTED_COLOR = sf::Color::Red;
const sf::Color HIGH_SCORE_COLOR = sf::Color::Yellow;

//GAME VALUES
const unsigned int GAME_ROWS = 8;
const unsigned int GAME_COLUMNS = 8;
//Upper left position of the grid (all blocks will be placed according to it)
const sf::Vector2f GRID_POSITION = sf::Vector2f(440.0f, 200.0f);
const float BLOCK_SIZE = 50.0f;
const unsigned int COLOR_BLOCK_PROBABILITY = 95;
const unsigned int NUMBER_OF_COLORS = 6;
const float GAME_INITIAL_TIMER = 120;
const std::string GAME_SCORE_TEXT = "Score ";
const sf::Vector2f GAME_SCORE_POSITION = sf::Vector2f(25.0f, 25.0f);
const sf::Color GAME_SCORE_COLOR = sf::Color::Yellow;
const unsigned int GAME_SCORE_CHARACTER_SIZE = 100;
const sf::Vector2f GAME_TIMER_POSITION = sf::Vector2f(640.0f, 25.0f);
const sf::Color GAME_TIMER_COLOR = sf::Color::Red;
const unsigned int GAME_TIMER_CHARACTER_SIZE = 100;

//GAME OVER VALUES
const std::string FINAL_SCORES_FILE = "Final_Scores.dat";
const sf::Vector2f GAME_OVER_POSITION = sf::Vector2f(320.0f, 100.0f);
const sf::Color GAME_OVER_COLOR = sf::Color::Red;
const unsigned int GAME_OVER_CHARACTER_SIZE = 150;
const std::string GAME_OVER_TEXT = "GAME OVER";

const sf::Color FINAL_SCORE_COLOR = sf::Color::Yellow;
const sf::Vector2f FINAL_SCORE_POSITION = sf::Vector2f(320.0f, 250.0);
const unsigned int FINAL_SCORE_CHARACTER_SIZE = 100;

const sf::Vector2f TIP_POSITION = sf::Vector2f(320.0f, 500.0f);
const sf::Color TIP_COLOR = sf::Color::White;
const unsigned int TIP_CHARACTER_SIZE = 50;
const std::string TIP_TEXT = "Press Enter to return to the main menu...";

//SOUND FX
const std::string BOMB_SOUND_FX_FILE = "sounds/Bomb_Sound_Fx.wav";
const std::string STRIPE_SOUND_FX_FILE = "sounds/Stripe_Sound_Fx.wav";
const std::string BUTTON_SOUND_FX_FILE = "sounds/Button_Sound_Fx.wav";
const std::string REDUCE_SOUND_FX_FILE = "sounds/Reduce_Sound_Fx.wav";
const std::string WRONG_ACTION_FX_FILE = "sounds/Wrong_Action_Sound_Fx.wav";

enum GameState
{
	MENU,
	GAME,
	GAME_OVER
};

enum BlockType
{
	COLOR,
	BOMB,
	STRIPE
};

enum SoundType
{
	BUTTON_SOUND,
	BOMB_SOUND,
	STRIPE_SOUND,
	REDUCE_SOUND,
	WRONG_ACTION_SOUND
};