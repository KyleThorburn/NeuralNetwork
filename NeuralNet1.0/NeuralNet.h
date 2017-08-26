#pragma once
#include <vector>

#include "Neuron.h"

class CNeuralNet
{
public:
	CNeuralNet(const std::vector<unsigned int>& aTopology);

	void FeedForward(const std::vector<double>& aInputValues);
	void BackProp(const std::vector<double>& aTargetValues);
	void GetResults(std::vector<double>& aResultValues);

private:
	std::vector<Layer> myLayers;
	double myError;
	double myRecentAvgError;
	double myRecentAvgSmoothingFactor;
};