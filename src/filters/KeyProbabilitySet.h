#pragma once

#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include "../stringbuilder.h"
#include "../key/Key.h"
#include "../util/SortObjectWrapper.h"

class KeyProbabilitySet
{

private:

public:
	std::vector<double> normalizedProbabilities;
private:
	bool major = false;
	std::string type;

public:
	KeyProbabilitySet(std::vector<double> &normalizedProbabilities, bool major, const std::string &type);

	virtual double getProbability(int index);

	virtual double getMaxProbability();

	virtual double getTotalProbability();

	virtual double getMinProbability();

	virtual Key *getKey();

	virtual std::string getType();
	virtual bool isMajor();

	virtual void addResults(std::vector<SortObjectWrapper> &results);

private:
	static Key *getKey(int index, bool major, const std::string &type);

};


