#pragma once

#include "KeyProbabilityFilter.h"
#include "../RectangularVectors.h"
#include <string>
#include <vector>
#include <cmath>


class SingleKeyProbabilityFilter : public KeyProbabilityFilter
{

private:
	static double decay;

	bool major = false;
	std::string type;
//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: private double[][] pmatrix = new double[12][12];
	std::vector<std::vector<double>> pmatrix = RectangularVectors::ReturnRectangularDoubleVector(12, 12);

    //TODO: Is the following definition of size correct?
	std::vector<double> probability = std::vector<double>(12);

public:

	SingleKeyProbabilityFilter(bool major, const std::string &type, std::vector<double> &probabilities);

	virtual std::string getDescription();

	virtual void add(std::vector<double> &values);

	virtual void add(std::vector<int> &values);

	virtual double getProbability(int index);

	virtual void clearProbabilities();

	virtual KeyProbabilitySet *getNormalizedProbabilities();

	virtual bool isAllZeros();
};

