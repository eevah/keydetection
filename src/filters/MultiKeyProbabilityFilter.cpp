#include "MultiKeyProbabilityFilter.h"
#include "SingleKeyProbabilityFilter.h"
#include "KeyProbabilitySet.h"

MultiKeyProbabilityFilter::MultiKeyProbabilityFilter(bool major, const std::string &type, std::vector<std::vector<double>> &probabilities)
{
	this->major = major;
	this->type = type;
	for (int p = 0; p < probabilities.size(); ++p)
	{
		SingleKeyProbabilityFilter *filter = new SingleKeyProbabilityFilter(major, type, probabilities[p]);
		filters.push_back(filter);
	}
}

std::string MultiKeyProbabilityFilter::getDescription()
{
	return type;
}

void MultiKeyProbabilityFilter::add(std::vector<double> &values)
{
	std::vector<double> add_probabilities(12);
	for (int f = 0; f < filters.size(); ++f)
	{
		SingleKeyProbabilityFilter *filter = static_cast<SingleKeyProbabilityFilter*>(filters[f]);
		filter->clearProbabilities();
		filter->add(values);
		for (int p = 0; p < 12; ++p)
		{
			if (filter->getProbability(p) > add_probabilities[p])
			{
				add_probabilities[p] = filter->getProbability(p);
			}
		}
	}
	for (int p = 0; p < 12; ++p)
	{
		probability[p] += add_probabilities[p];
	}
}

void MultiKeyProbabilityFilter::add(std::vector<int> &values)
{
	std::vector<double> add_probabilities(12);
	for (int f = 0; f < filters.size(); ++f)
	{
		SingleKeyProbabilityFilter *filter = static_cast<SingleKeyProbabilityFilter*>(filters[f]);
		filter->clearProbabilities();
		filter->add(values);
		for (int p = 0; p < 12; ++p)
		{
			if (filter->getProbability(p) > add_probabilities[p])
			{
				add_probabilities[p] = filter->getProbability(p);
			}
		}
	}
	for (int p = 0; p < 12; ++p)
	{
		probability[p] += add_probabilities[p];
	}
}

KeyProbabilitySet *MultiKeyProbabilityFilter::getNormalizedProbabilities()
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

bool MultiKeyProbabilityFilter::isAllZeros()
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
