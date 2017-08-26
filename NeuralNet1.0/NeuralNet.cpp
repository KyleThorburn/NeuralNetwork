#include "NeuralNet.h"
//#include "Neuron.h"

#include <assert.h>

#include <iostream>

CNeuralNet::CNeuralNet(const std::vector<unsigned int>& aTopology)
{
	unsigned int numOfLayers = aTopology.size();

	for (unsigned int layerNum = 0; layerNum < numOfLayers; ++layerNum)
	{
		myLayers.push_back(Layer());

		unsigned int numOfOutputs;
		if (layerNum == aTopology.size() - 1)
			numOfOutputs = 0;
		else
			numOfOutputs = aTopology[layerNum + 1];

		for (unsigned int neuronNum = 0; neuronNum <= aTopology[layerNum]; ++neuronNum)
		{
			myLayers.back().push_back(CNeuron(numOfOutputs));

			if (neuronNum != aTopology[layerNum])
			
				std::cout << "Made a neuron!\n";
			else
				std::cout << "Made a bias-neuron!\n";
		}
		std::cout << "\n";
	}
}

void CNeuralNet::FeedForward(const std::vector<double>& aInputValues)
{
	assert(aInputValues.size() == myLayers[0].size() - 1 && 
		"The number of input values is not the same as the number of input neurons");
}

void CNeuralNet::BackProp(const std::vector<double>& aVal)
{
}

void CNeuralNet::GetResults(std::vector<double> aResultVal) const
{
}
