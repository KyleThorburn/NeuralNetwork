#pragma once
#include <vector>

struct Connection
{
	double weight;
	double deltaWeight;
};


class CNeuron
{
public:
	CNeuron(unsigned int aNumOfOutputs);
	~CNeuron();
	inline static double RandomWeight();

private:
	double myOutputVal;
	std::vector<Connection> myOutputWeights;
};

double CNeuron::RandomWeight()
{
	return rand() / double(RAND_MAX);
}
