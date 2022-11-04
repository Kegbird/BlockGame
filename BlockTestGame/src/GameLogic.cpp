#include "headers/GameLogic.hpp"

GameLogic::GameLogic(sf::Vector2f grid_position, unsigned int rows, unsigned int columns)
{
	_font.loadFromFile(MENU_FONT);

	_game_score_text.setFont(_font);
	_game_score_text.setString(GAME_SCORE_TEXT);
	_game_score_text.setFillColor(GAME_SCORE_COLOR);
	_game_score_text.setPosition(GAME_SCORE_POSITION);
	_game_score_text.setCharacterSize(GAME_SCORE_CHARACTER_SIZE);

	_game_timer_text.setFont(_font);
	_game_timer_text.setFillColor(GAME_TIMER_COLOR);
	_game_timer_text.setPosition(GAME_TIMER_POSITION);
	_game_timer_text.setCharacterSize(GAME_TIMER_CHARACTER_SIZE);

	srand(time(NULL));
	_blocks = new sf::RectangleShape*[rows];
	_block_types = new BlockType*[rows];

	for (int i = 0; i < rows; i++)
	{
		_block_types[i] = new BlockType[columns];
		_blocks[i] = new sf::RectangleShape[columns];
		for (int j = 0; j < columns; j++)
		{
			_blocks[i][j] = sf::RectangleShape(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
			_blocks[i][j].setPosition(sf::Vector2f(GRID_POSITION.x + j*BLOCK_SIZE, GRID_POSITION.y + i * BLOCK_SIZE));
		}
	}

	_bomb_texture.loadFromFile("textures/Bomb_Texture.png");
	_stripe_texture.loadFromFile("textures/Stripe_Texture.png");

	_game_score = 0;
	_exit = _game_over = false;
	_rows = rows;
	_columns = columns;
}


GameLogic::~GameLogic()
{
	for (int i = 0; i < _rows; i++)
	{
		delete[] _block_types[i];
		delete[] _blocks[i];
	}
	delete[] _block_types;
	delete[] _blocks;
}

void GameLogic::StartGame()
{
	RandomizeBlocks();
	_time_before_gameover = GAME_INITIAL_TIMER;
	_last_timestamp = std::chrono::high_resolution_clock::now();
	_game_score = 0;
	_exit = _game_over = false;
}

void GameLogic::Update()
{
	auto timestamp = std::chrono::high_resolution_clock::now();
	auto time_elapsed_from_last_timestamp = std::chrono::duration_cast<std::chrono::seconds>(timestamp - _last_timestamp).count();

	if (time_elapsed_from_last_timestamp >= 1.0f)
	{
		_last_timestamp = timestamp;
		_time_before_gameover--;
	}

	if (_time_before_gameover > 0)
	{
		_game_score_text.setString(GAME_SCORE_TEXT + std::to_string(_game_score));
		_game_timer_text.setString(std::to_string(_time_before_gameover));
	}
	else
	{
		_game_over = true;
	}
}

void GameLogic::HandleEvent(sf::Event event, sf::RenderWindow* window)
{
	switch (event.type)
	{
	case sf::Event::KeyReleased:
		HandleKeyReleased(event.key.code);
		break;
	case sf::Event::MouseButtonReleased:
		HandleMouseButtonReleased(event.key.code, window);
		break;
	}
}

void GameLogic::HandleKeyReleased(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::Escape:
		_exit = true;
		break;
	default:
		break;
	}
}

void GameLogic::DestroyBlocks(sf::Vector2i mouse_position)
{
	if (mouse_position.x<GRID_POSITION.x ||
		mouse_position.x>GRID_POSITION.x + BLOCK_SIZE * _columns ||
		mouse_position.y<GRID_POSITION.y ||
		mouse_position.y>GRID_POSITION.y + BLOCK_SIZE * _rows)
		return;

	mouse_position.x -= GRID_POSITION.x;
	mouse_position.y -= GRID_POSITION.y;

	unsigned int block_row = mouse_position.y / BLOCK_SIZE;
	unsigned int block_column = mouse_position.x / BLOCK_SIZE;

	if (block_row >= _rows || block_column >= _columns)
		return;

	BlockType block_type = _block_types[block_row][block_column];

	switch (block_type)
	{
		case COLOR:
			Reduce(block_row, block_column);
			break;
		case BOMB:
			Bomb(block_row, block_column);
			break;
		case STRIPE:
			Stripe(block_row);
			break;
	}
}

void GameLogic::Reduce(int row, int column)
{
	std::set<std::tuple<int, int>> block_visited;
	std::stack<std::tuple<int, int>> block_to_visit;
	block_to_visit.push(std::tuple<int, int>(row, column));
	std::tuple<int, int> coordinates;

	int other_row;
	int other_column;
	do
	{
		std::tuple<int, int> current_coordinates = block_to_visit.top();
		block_to_visit.pop();
		block_visited.insert(current_coordinates);

		row = std::get<0>(current_coordinates);
		column = std::get<1>(current_coordinates);

		//Left
		coordinates = std::tuple<int, int>(row, column - 1);
		other_row = std::get<0>(coordinates);
		other_column = std::get<1>(coordinates);
		if (other_column >= 0 && CompareBlockColors(row, column, other_row, other_column) && block_visited.find(coordinates) == block_visited.end())
		{
			block_to_visit.push(coordinates);
		}
		//Right
		coordinates = std::tuple<int, int>(row, column + 1);
		other_row = std::get<0>(coordinates);
		other_column = std::get<1>(coordinates);
		if (column + 1 < _columns && CompareBlockColors(row, column, other_row, other_column) && block_visited.find(coordinates) == block_visited.end())
		{
			block_to_visit.push(coordinates);
		}
		//Up
		coordinates = std::tuple<int, int>(row - 1, column);
		other_row = std::get<0>(coordinates);
		other_column = std::get<1>(coordinates);
		if (row - 1 >= 0 && CompareBlockColors(row, column, other_row, other_column) && block_visited.find(coordinates) == block_visited.end())
		{
			block_to_visit.push(coordinates);
		}
		//Down
		coordinates = std::tuple<int, int>(row + 1, column);
		other_row = std::get<0>(coordinates);
		other_column = std::get<1>(coordinates);
		if (row + 1 < _rows && CompareBlockColors(row, column, other_row, other_column) && block_visited.find(coordinates) == block_visited.end())
		{
			block_to_visit.push(coordinates);
		}
	} while (block_to_visit.size()>0);

	SoundManager* sound_manager = SoundManager::GetInstance();
	if (block_visited.size() > 1)
	{
		_game_score += EvaluateScoreIncrement(block_visited.size());

		std::set<std::tuple<int, int>>::iterator it;
		for (it = block_visited.begin(); it != block_visited.end(); it++)
		{
			coordinates = *it;
			row = std::get<0>(coordinates);
			column = std::get<1>(coordinates);
			RandomizeBlock(row, column);
		}

		_time_before_gameover += EvaluateTimeIncrement(block_visited.size());
		//After every action, the grid is checked to verify if the game can continue
		_game_over = IsGameOver();

		sound_manager->PlaySound(REDUCE_SOUND);
	}
	else
	{
		sound_manager->PlaySound(WRONG_ACTION_SOUND);
	}
}

bool GameLogic::CanReduce(int row, int column)
{
	std::set<std::tuple<int, int>> block_visited;
	std::stack<std::tuple<int, int>> block_to_visit;
	block_to_visit.push(std::tuple<int, int>(row, column));
	std::tuple<int, int> coordinates;

	int other_row;
	int other_column;
	do
	{
		std::tuple<int, int> current_coordinates = block_to_visit.top();
		block_to_visit.pop();
		block_visited.insert(current_coordinates);

		row = std::get<0>(current_coordinates);
		column = std::get<1>(current_coordinates);

		//Left
		coordinates = std::tuple<int, int>(row, column - 1);
		other_row = std::get<0>(coordinates);
		other_column = std::get<1>(coordinates);
		if (other_column >= 0 && CompareBlockColors(row, column, other_row, other_column) && block_visited.find(coordinates) == block_visited.end())
		{
			block_to_visit.push(coordinates);
		}
		//Right
		coordinates = std::tuple<int, int>(row, column + 1);
		other_row = std::get<0>(coordinates);
		other_column = std::get<1>(coordinates);
		if (column + 1 < _columns && CompareBlockColors(row, column, other_row, other_column) && block_visited.find(coordinates) == block_visited.end())
		{
			block_to_visit.push(coordinates);
		}
		//Up
		coordinates = std::tuple<int, int>(row - 1, column);
		other_row = std::get<0>(coordinates);
		other_column = std::get<1>(coordinates);
		if (row - 1 >= 0 && CompareBlockColors(row, column, other_row, other_column) && block_visited.find(coordinates) == block_visited.end())
		{
			block_to_visit.push(coordinates);
		}
		//Down
		coordinates = std::tuple<int, int>(row + 1, column);
		other_row = std::get<0>(coordinates);
		other_column = std::get<1>(coordinates);
		if (row + 1 < _rows && CompareBlockColors(row, column, other_row, other_column) && block_visited.find(coordinates) == block_visited.end())
		{
			block_to_visit.push(coordinates);
		}
	} while (block_to_visit.size() > 0);

	if (block_visited.size() > 1)
		return true;
	return false;
}

bool GameLogic::IsGameOver()
{
	for (int i = 0; i < _rows; i++)
	{
		for (int j = 0; j < _columns; j++)
		{
			if (_block_types[i][j] != COLOR || CanReduce(i, j))
				return false;
		}
	}
	return true;
}

void GameLogic::Stripe(int row)
{
	_time_before_gameover += EvaluateTimeIncrement(_columns);
	for (int i = 0; i < _columns; i++)
		RandomizeBlock(row, i);
	_game_score += EvaluateScoreIncrement(_columns);

	SoundManager* sound_manager = SoundManager::GetInstance();
	sound_manager->PlaySound(STRIPE_SOUND);
}

void GameLogic::Bomb(int row, int column)
{
	_game_score += EvaluateScoreIncrement(9);
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if (row + i < 0 || row + i >= _rows || column + j < 0 || column + j >= _columns)
				continue;
			RandomizeBlock(row + i, column + j);
		}
	}
	_time_before_gameover += EvaluateTimeIncrement(9);

	SoundManager* sound_manager = SoundManager::GetInstance();
	sound_manager->PlaySound(BOMB_SOUND);
}

void GameLogic::HandleMouseButtonReleased(sf::Keyboard::Key key, sf::RenderWindow* window)
{
	switch (key)
	{
	case sf::Mouse::Left:
		sf::Vector2i mouse_position = sf::Mouse::getPosition(*window);
		DestroyBlocks(mouse_position);
		break;
	}
}

void GameLogic::ShowGame(sf::RenderWindow* window)
{
	for (int i = 0; i < _rows; i++)
	{
		for (int j = 0; j < _columns; j++)
			window->draw(_blocks[i][j]);
	}
	window->draw(_game_score_text);
	window->draw(_game_timer_text);
}

unsigned int GameLogic::GetScore()
{
	return _game_score;
}

bool GameLogic::CompareBlockColors(int first_row, int first_column, int second_row, int second_column)
{
	sf::Color first_color = _blocks[first_row][first_column].getFillColor();
	sf::Color second_color = _blocks[second_row][second_column].getFillColor();
	return first_color.r == second_color.r && first_color.g == second_color.g && first_color.b == second_color.b;
}

void GameLogic::RandomizeBlocks()
{
	for (int i = 0; i < _rows; i++)
	{
		for (int j = 0; j < _columns; j++)
			RandomizeBlock(i, j);
	}
}

void GameLogic::RandomizeBlock(unsigned int row, unsigned int column)
{
	unsigned int seed = rand() % 101;
	if (seed <= COLOR_BLOCK_PROBABILITY)
	{
		//Color block
		_block_types[row][column] = COLOR;
		_blocks[row][column].setFillColor(RandomizeColor());
		//To remove the texture (apparently is the correct way)
		_blocks[row][column].setTexture(NULL);
	}
	else
	{
		//Special block
		seed = rand() % 101;
		if (seed <= 50)
		{
			_block_types[row][column] = BOMB;
			_blocks[row][column].setTexture(&_bomb_texture);
		}
		else
		{
			_block_types[row][column] = STRIPE;
			_blocks[row][column].setTexture(&_stripe_texture);
		}
		//To remove the remove the previous color (if there is)
		_blocks[row][column].setFillColor(sf::Color::White);
	}
}

sf::Color GameLogic::RandomizeColor()
{
	unsigned int seed = rand() % NUMBER_OF_COLORS;
	switch (seed)
	{
	case 0:
		return sf::Color::Red;
	case 1:
		return sf::Color::Blue;
	case 2:
		return sf::Color::Green;
	case 3:
		return sf::Color::Yellow;
	case 4:
		return sf::Color(100, 64, 0);
	default:
		return sf::Color(56, 0, 100);
	}
}
