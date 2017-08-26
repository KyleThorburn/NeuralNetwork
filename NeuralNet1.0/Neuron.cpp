#include "Neuron.h"


CNeuron::CNeuron(unsigned int aNumOfOutputs)
{
	for (unsigned int connection = 0; connection < aNumOfOutputs; ++connection)
	{
		myOutputWeights.push_back(Connection());
		myOutputWeights.back().weight = RandomWeight();
	}
}

CNeuron::~CNeuron()
{
}
