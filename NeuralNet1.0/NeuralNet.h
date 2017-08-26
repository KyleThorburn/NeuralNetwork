#pragma once

#include <vector>

//class CNeuron;
#include "Neuron.h"
typedef std::vector<CNeuron> Layer;

class CNeuralNet
{
public:
	CNeuralNet(const std::vector<unsigned int>& aTopology);

	void FeedForward(const std::vector<double>& aVal);
	void BackProp(const std::vector<double>& aVal);
	void GetResults(std::vector<double> aResultVal) const;

private:
	std::vector<Layer> myLayers;
};