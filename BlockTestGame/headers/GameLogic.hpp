#pragma once
#include <chrono>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <set>
#include <tuple>
#include <stack>
#include "SFML/Graphics.hpp"
#include "Constants.hpp"
#include "SoundManager.hpp"

class GameLogic
{
public:
	GameLogic(sf::Vector2f grid_position, unsigned int rows, unsigned int columns);
	virtual ~GameLogic();
	void StartGame();
	void Update();
	void HandleEvent(sf::Event event, sf::RenderWindow* window);
	void HandleKeyReleased(sf::Keyboard::Key key);
	void DestroyBlocks(sf::Vector2i mouse_position);
	bool CanReduce(int row, int column);
	void Reduce(int row, int column);
	void Stripe(int row);
	void Bomb(int row, int column);
	unsigned int  EvaluateScoreIncrement(unsigned int number_of_match);
	unsigned int  EvaluateTimeIncrement(unsigned int number_of_match);
	void HandleMouseButtonReleased(sf::Keyboard::Key key, sf::RenderWindow* window);
	void ShowGame(sf::RenderWindow* window);
	unsigned int GetScore();
	bool CompareBlockColors(int first_row, int first_column, int second_row, int second_column);
	bool  Exit();
	bool  GameOver();
	bool IsGameOver();
private:
	void RandomizeBlocks();
	void RandomizeBlock(unsigned int row, unsigned int column);
	sf::Color RandomizeColor();
	sf::Font _font;
	sf::Texture _bomb_texture;
	sf::Texture _stripe_texture;
	sf::Text _game_timer_text;
	sf::Text _game_score_text;
	BlockType** _block_types;
	sf::RectangleShape** _blocks;
	unsigned int _game_score;
	unsigned int _rows;
	unsigned int _columns;
	unsigned int _time_before_gameover;
	std::chrono::steady_clock::time_point _last_timestamp;
	bool _exit;
	bool _game_over;
};


bool inline GameLogic::Exit()
{
	return _exit;
}

bool inline GameLogic::GameOver()
{
	return _game_over;
}

unsigned int inline GameLogic::EvaluateScoreIncrement(unsigned int number_of_match)
{
	return (number_of_match - 1) * 80 + pow((number_of_match - 2) / 5, 2);
}

unsigned int inline GameLogic::EvaluateTimeIncrement(unsigned int number_of_match)
{
	return (10 + pow((number_of_match - 2) / 3, 2) * 20);
}
