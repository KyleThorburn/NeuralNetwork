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

		// force bias neuron's output value to 1.0.
		myLayers.back().back().SetOutputValue(1.0);
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

void CNeuralNet::BackProp(const std::vector<double>& aTargetValues)
{
	// Calculate overall net error. ("Root Mean Square" of output neuron errors)

	Layer& outputLayer = myLayers.back();
	myError = 0.0;
										//not including the bias
	for (unsigned int n = 0; n < outputLayer.size() - 1; ++n)
	{
		double delta = aTargetValues[n] - outputLayer[n].GetOutputValue();
		myError += delta * delta;
	}

	myError /= outputLayer.size() - 1;
	myError = sqrt(myError); // get avg.squared  (RMS)

	// Recent avg. measurement.
	myRecentAvgError = (myRecentAvgError * myRecentAvgSmoothingFactor + myError)
		/ (myRecentAvgSmoothingFactor + 1);


	// Calculate layer gradients

	for (unsigned int n = 0; n < outputLayer.size() - 1; ++n)
	{
		outputLayer[n].CalcOutputGradients(aTargetValues[n]);
	}

	// Calculate gradients on hidden layers.

									//rightmost hidden layer
	for (unsigned int layerNum = myLayers.size() - 2; layerNum > 0; --layerNum)
	{
		Layer& hiddenLayer = myLayers[layerNum];
		Layer& nextLayer = myLayers[layerNum + 1];

		for (unsigned int n = 0; n < hiddenLayer.size(); ++n)
		{
			hiddenLayer[n].CalcHiddenGradients(nextLayer);
		}
	}

	// for all layers: first hidden -> output .. update connection weights.

	for (unsigned int layerNum = myLayers.size() - 1; layerNum > 0; --layerNum)
	{
		Layer& currLayer = myLayers[layerNum];
		Layer& prevLayer = myLayers[layerNum - 1];

		for (unsigned int n = 0; n < currLayer.size() - 1; ++n)
		{
			currLayer[n].UpdateInputWeights(prevLayer);
		}
	}
}

void CNeuralNet::GetResults(std::vector<double>& aResultValues)
{
	aResultValues.clear();

	for (unsigned int n = 0; n < myLayers.back().size() - 1; ++n)
	{
		aResultValues.push_back(myLayers.back()[n].GetOutputValue());
	}
}
