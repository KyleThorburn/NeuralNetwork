#pragma once

#include <SFML\Graphics.hpp>

class CNeuralNet;

class CGameWorld
{
public:
	CGameWorld();
	~CGameWorld();

	void Init(sf::RenderWindow* aWindow);
	void Render();
	void Update();

private:
	sf::RenderWindow* myWindow;
	sf::CircleShape myNeuronSprite;

	CNeuralNet* myNeuralNet;
};

