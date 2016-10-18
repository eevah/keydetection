#pragma once

#include <string>
#include <vector>
#include <limits>
#include <cctype>
#include <stdexcept>
#include <iostream>
#include "stringbuilder.h"
#include "DetectedKey.h"
#include "filters/KeyProbabilityFilter.h"

//using KeyProbabilityFilter = com::mixshare::rapid_evolution::audio::detection::key::filters::KeyProbabilityFilter;

class KeyProbability
{

private:

	static double analyze_segment_size; // seconds;

	////////////
	// FIELDS //
	////////////

	double segment_size = 0;
	std::vector<double> segment_totals;

	std::vector<KeyProbabilityFilter*> filters;

	//////////////////
	// CONSTRUCTORS //
	//////////////////

public:
	KeyProbability(double segmentTime);

	/////////////
	// GETTERS //
	/////////////

	virtual DetectedKey *getDetectedKey();
	virtual DetectedKey *getDetectedKey(bool logDetails);

	virtual bool hasNoData();

	/////////////
	// METHODS //
	/////////////

	virtual void add(std::vector<double> &totals, double time);

	virtual void add(std::vector<int> &totals, double time);

	virtual void finish();

//	virtual bool sortByFunction(SortObjectWrapper& lhs, SortObjectWrapper& rhs);

private:
	void processSegment();

	int safeindex(int index);

};

