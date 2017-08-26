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
	CNeuron(unsigned int aNrOfOutputs);
	~CNeuron();

private:
	double myOutputVal;
	std::vector<Connection> myOutputWeights;
};

