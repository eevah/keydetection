#include "SingleKeyProbabilityFilter.h"
#include "KeyProbabilitySet.h"
#include <iostream>

double SingleKeyProbabilityFilter::decay = 1.0;

SingleKeyProbabilityFilter::SingleKeyProbabilityFilter(bool major, const std::string &type, std::vector<double> &probabilities)
{
	std::string typeStr( type.begin(), type.end() );
	if ((probabilities.empty()) || (probabilities.size() != 12))
	{
		//TODO: Log error
		std::string error = "SingleKeyProbabilityFilter(): probabilities array is incorrect lengh for key=" + typeStr;
		std::cout << error;
		//log->error(std::wstring(L"SingleKeyProbabilityFilter(): probabilities array is incorrect lengh for key=") + type);
	}
	double total = 0.0;
	int num_notes = 0;
	for (int i = 0; i < 12; ++i)
	{
		if (probabilities[i] > 0.0)
		{
			++num_notes;
		}
		total += probabilities[i];
	}
	if (std::abs(total - 1.0) > 0.0001)
	{
		//TODO: Log error
		std::string error = "SingleKeyProbabilityFilter(): total probability != 1.0 for key=" + typeStr;
		std::cout << error;
//		log->error(std::wstring(L"SingleKeyProbabilityFilter(): total probability != 1.0 for key=") + type);
	}
	this->major = major;
	this->type = type;
	for (int k = 0; k < 12; ++k)
	{
		for (int n = 0; n < 12; ++n)
		{
			int offset = n + k;
			if (offset >= 12)
			{
				offset -= 12;
			}
			pmatrix[k][offset] = probabilities[n];
		}
	}
}

std::string SingleKeyProbabilityFilter::getDescription()
{
	return type;
}

void SingleKeyProbabilityFilter::add(std::vector<double> &values)
{
	for (int k = 0; k < 12; ++k)
	{
		double total = 0.0;
		for (int n = 0; n < 12; ++n)
		{
			total += pmatrix[k][n] * values[n];
		}
		probability[k] = total + probability[k]; // * decay;
	}
}

void SingleKeyProbabilityFilter::add(std::vector<int> &values)
{
	for (int k = 0; k < 12; ++k)
	{
		double total = 0.0;
		for (int n = 0; n < 12; ++n)
		{
			total += pmatrix[k][n] * (static_cast<double>(values[n]));
		}
		probability[k] = total + probability[k]; // * decay;
	}
}

double SingleKeyProbabilityFilter::getProbability(int index)
{
	return probability[index];
}

void SingleKeyProbabilityFilter::clearProbabilities()
{
	for (int i = 0; i < 12; ++i)
	{
		probability[i] = 0.0;
	}
}

KeyProbabilitySet *SingleKeyProbabilityFilter::getNormalizedProbabilities()
{
	std::vector<double> normalizedProbabilities(12);
	double total = 0.0;
	for (int i = 0; i < 12; ++i)
	{
		total += probability[i];
	}
	for (int i = 0; i < 12; ++i)
	{
		normalizedProbabilities[i] = probability[i] / total;
	}
	return new KeyProbabilitySet(normalizedProbabilities, major, type);
}

bool SingleKeyProbabilityFilter::isAllZeros()
{
	for (int i = 0; i < 12; ++i)
	{
		if (probability[i] > 0.0)
		{
			return false;
		}
	}
	return true;
}

