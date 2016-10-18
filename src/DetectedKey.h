#pragma once

#include <string>
#include "stringbuilder.h"
#include "Accuracy.h"
#include "key/Key.h"


class DetectedKey
{

private:
	Key *startKey;// = nullptr;
	Key *endKey; // = nullptr;
	double accuracy;// = 0;

public:
	DetectedKey();
	DetectedKey(Key *startKey, Key *endKey, double accuracy);

	virtual Key *getStartKey();
	virtual Key *getEndKey();
	virtual double getAccuracyValue();
	virtual Accuracy *getAccuracy();

	virtual void setStartKey(Key *startKey);
	virtual void setEndKey(Key *endKey);
	virtual void setAccuracy(double value);

	virtual bool isValid();

	virtual std::string toString();
};
