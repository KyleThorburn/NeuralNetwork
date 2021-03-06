#pragma once
#include <vector>

struct Connection
{
	double weight;
	double deltaWeight;
};

typedef std::vector<class CNeuron> Layer;

class CNeuron
{
public:
	CNeuron(unsigned int aNumOfOutputs, unsigned int aIndex);
	~CNeuron();
	inline void SetOutputValue(double aVal) { myOutputVal = aVal; }
	inline double GetOutputValue() { return myOutputVal; }

	void FeedForward(const Layer& aPrevLayer);
	void CalcOutputGradients(double aTargetValue);
	void CalcHiddenGradients(const Layer& aNextLayer);
	void UpdateInputWeights(Layer& aPrevLayer);

	inline static double RandomWeight();
	inline static double ActivationFunction(double aSum);
	inline static double ActivationFunctionDerivative(double aSum);

private:
	double SumDOW(const Layer& aNextLayer) const;

private:
	double myOutputVal;
	double myGradient;
	static double eta;    // [0.0 .. 1.0] overall net training rate.
	static double alpha; // [0.0 .. n] multiplier of last weight change (momentum).
	std::vector<Connection> myOutputWeights;
	unsigned int myIndex;
};


double CNeuron::RandomWeight()
{
	return rand() / double(RAND_MAX);
}

// for forward progopgation
inline double CNeuron::ActivationFunction(double aSum)
{
	// tanh _ output range [ -1.0 .. 1.0 ]
	
	return tanh(aSum); // returns the hyperbolic tangent of its input.
}

// for back propogation
inline double CNeuron::ActivationFunctionDerivative(double aSum)
{
	// tanh derivative

	return 1.0 - aSum * aSum;
}
