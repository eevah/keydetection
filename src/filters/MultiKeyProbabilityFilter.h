#pragma once

#include "KeyProbabilityFilter.h"
#include "KeyProbabilitySet.h"
#include <string>
#include <vector>

class MultiKeyProbabilityFilter : public KeyProbabilityFilter
{

private:

	bool major = false;
	std::string type;
	std::vector<KeyProbabilityFilter*> filters;
	std::vector<double> probability = std::vector<double>(12);

public:
	MultiKeyProbabilityFilter(bool major, const std::string &type, std::vector<std::vector<double>> &probabilities);

	virtual std::string getDescription();

	virtual void add(std::vector<double> &values);

	virtual void add(std::vector<int> &values);

	virtual KeyProbabilitySet *getNormalizedProbabilities();

	virtual bool isAllZeros();

};

