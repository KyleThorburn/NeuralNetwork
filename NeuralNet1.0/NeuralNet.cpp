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
			myLayers.back().push_back(CNeuron(numOfOutputs, neuronNum));

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

	for (unsigned int i = 0; i < aInputValues.size(); ++i)
	{
		myLayers[0][i].SetOutputValue(aInputValues[i]);
	}

	// Forward propogate

	for (unsigned int layerNum = 1; layerNum < myLayers.size(); ++layerNum)
	{
		Layer& prevLayer = myLayers[layerNum - 1];

		for (unsigned int neuronNum = 0; neuronNum < myLayers[layerNum].size() - 1; ++neuronNum)
		{
			myLayers[layerNum][neuronNum].FeedForward(prevLayer);
		}
	}

}

void CNeuralNet::BackProp(const std::vector<double>& aVal)
{
	// Calculate overall net error. (Root Mean Square of output neuron errors)

	// Calculate layer gradients

	// Calculate gradients on hidden layers.

	// for all layers: first hidden -> output .. update connection weights.
}

void CNeuralNet::GetResults(std::vector<double> aResultVal) const
{
}
