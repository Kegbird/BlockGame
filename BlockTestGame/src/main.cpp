#include <iostream>
#include "SFML/Graphics.hpp"
#include "GameManager.hpp"
#include "Menu.hpp"

int main()
{
	GameManager* game_manager = new GameManager();

	while (game_manager->IsRunning())
	{
		game_manager->InputProcessing();
		game_manager->Update();
		game_manager->Render();
	}

	delete game_manager;
	return 0;
}
