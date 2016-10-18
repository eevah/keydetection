#include "DetectedKey.h"

DetectedKey::DetectedKey()
{
	this->startKey = nullptr;
	this->endKey = nullptr;
	this->accuracy = 0;
}

DetectedKey::DetectedKey(Key *startKey, Key *endKey, double accuracy)
{
	this->startKey = startKey;
	this->endKey = endKey;
	this->accuracy = accuracy;
}

Key *DetectedKey::getStartKey()
{
	return startKey;
}

Key *DetectedKey::getEndKey()
{
	if (startKey->equals(endKey))
	{
		return Key::NO_KEY;
	}
	return endKey;
}

double DetectedKey::getAccuracyValue()
{
	return accuracy;
}

Accuracy *DetectedKey::getAccuracy()
{
	return Accuracy::getAccuracy(static_cast<char>(accuracy * 100));
}

void DetectedKey::setStartKey(Key *startKey)
{
	this->startKey = startKey;
}

void DetectedKey::setEndKey(Key *endKey)
{
	this->endKey = endKey;
}

void DetectedKey::setAccuracy(double value)
{
	accuracy = value;
}

bool DetectedKey::isValid()
{
	return ((startKey != nullptr) && (startKey->isValid() || accuracy > 0.0));
}

std::string DetectedKey::toString()
{
	StringBuilder *result = new StringBuilder();
	result->append("[key: ");
	result->append(startKey);
	result->append("->");
	result->append(endKey);
	result->append(", accuracy: ");
	result->append(accuracy);
	result->append("]");
	return result->toString();
}
