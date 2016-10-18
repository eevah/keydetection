#pragma once

#include <string>
#include <sstream>
#include <boost/algorithm/string/trim.hpp>

#include "../key/Key.h"

class SortObjectWrapper
{

private:
	Key *object;
	double sort_value = 0;

public:
	SortObjectWrapper(Key *key, double sort_value);

	virtual Key* getObject();
	virtual double getValue();

	virtual void setValue(double value);

	virtual std::string toString();

//	virtual int compareTo(SortObjectWrapper *sO);

};
