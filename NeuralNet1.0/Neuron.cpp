#include "Neuron.h"

double CNeuron::eta = 0.15;
double CNeuron::alpha = 0.5;

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

void CNeuron::CalcOutputGradients(double aTargetValue)
{
	double delta = aTargetValue - myOutputVal;
	myGradient = delta * CNeuron::ActivationFunctionDerivative(myOutputVal);
}

void CNeuron::CalcHiddenGradients(const Layer & aNextLayer)
{
	double dow = SumDOW(aNextLayer);
	myGradient = dow * CNeuron::ActivationFunctionDerivative(myOutputVal);
}

void CNeuron::UpdateInputWeights(Layer & aPrevLayer)
{
	 // The weights to be updated are in the connection container,
	// in the neurons in the preceeding layer.

	for (unsigned int n = 0; n < aPrevLayer.size(); ++n)
	{
		CNeuron& currNeuron = aPrevLayer[n];

		double oldDeltaWeight = currNeuron.myOutputWeights[myIndex].deltaWeight;

		// eta = learning rate;  alpha = momentum rate;
		double newDeltaWeight = eta * currNeuron.GetOutputValue() 
			* myGradient + alpha * oldDeltaWeight;

		currNeuron.myOutputWeights[myIndex].deltaWeight = newDeltaWeight;
		currNeuron.myOutputWeights[myIndex].weight += newDeltaWeight;

	}
}

double CNeuron::SumDOW(const Layer & aNextLayer) const
{
	double sum = 0.0;

	// sum our contributions of the errors at the nodes we feed.

	for (unsigned int n = 0; aNextLayer.size() - 1; ++n)
	{
		sum += myOutputWeights[n].weight * aNextLayer[n].myGradient;
	}

	return sum;
}
