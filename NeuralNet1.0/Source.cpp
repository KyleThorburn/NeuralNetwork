#include <iostream>

#include "GameWorld.h"

#define VERSION 1.0

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "NeuralNet " + std::to_string(VERSION));

	CGameWorld cGameWorld;
	cGameWorld.Init(&window);
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	
		cGameWorld.Update();
		cGameWorld.Render();

	}

	return 0;
}
