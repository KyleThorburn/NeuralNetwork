#include "Neuron.h"


CNeuron::CNeuron(unsigned int aNumOfOutputs, unsigned int aIndex)
{
	myIndex = aIndex;

	for (unsigned int connection = 0; connection < aNumOfOutputs; ++connection)
	{
		myOutputWeights.push_back(Connection());
		myOutputWeights.back().weight = RandomWeight();
	}
}

CNeuron::~CNeuron()
{
}

void CNeuron::FeedForward(const Layer & aPrevLayer)
{
	double sum = 0.0;

	 // Sums up the previous layers outputs, which are our inputs.
	// Also includes the bias-neuron.

	for (unsigned int n = 0; n < aPrevLayer.size(); ++n)
	{
		sum += aPrevLayer[n].myOutputVal * 
			aPrevLayer[n].myOutputWeights[myIndex].weight;
	}

	// Activation function

	myOutputVal = CNeuron::ActivationFunction(sum);
}