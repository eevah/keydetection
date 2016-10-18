#pragma once

#include <vector>
#include "KeyProbabilitySet.h"

class KeyProbabilityFilter
{

public:
	virtual void add(std::vector<double> &values) = 0;

	virtual void add(std::vector<int> &values) = 0;

	virtual KeyProbabilitySet *getNormalizedProbabilities() = 0;

	virtual bool isAllZeros() = 0;

};