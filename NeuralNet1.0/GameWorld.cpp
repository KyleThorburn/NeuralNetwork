#include "GameWorld.h"

#include <vector>

#include "NeuralNet.h"

CGameWorld::CGameWorld()
{

}

CGameWorld::~CGameWorld()
{
	delete myNeuralNet;
	myNeuralNet = nullptr;
}

void CGameWorld::Init(sf::RenderWindow* aWindow)
{
	myWindow = aWindow;

	myNeuronSprite.setRadius(50);
	myNeuronSprite.setFillColor(sf::Color::Green);

	float midPoint = myNeuronSprite.getRadius() / 2.f;
	myNeuronSprite.setOrigin(midPoint, midPoint);
	myNeuronSprite.setPosition(0.f, 0.f);

	std::vector<unsigned int> topology;
	topology.push_back(3);
	topology.push_back(2);
	topology.push_back(1);

	myNeuralNet = new CNeuralNet(topology);
}


void CGameWorld::Render()
{
	myWindow->clear();
	myWindow->draw(myNeuronSprite);
	myWindow->display();
}

static unsigned int trainingPass = 0;

void CGameWorld::Update()
{
	std::vector<double> inputValues, targetValues, resultValues;


	myNeuralNet->FeedForward(inputValues);
	myNeuralNet->BackProp(targetValues);
	myNeuralNet->GetResults(resultValues);

}
