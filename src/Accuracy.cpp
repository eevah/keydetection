#include "Accuracy.h"


Accuracy::Accuracy()
{
}

Accuracy::Accuracy(char accuracy)
{
	this->accuracy = accuracy;
}

char Accuracy::getAccuracy()
{
	return accuracy;
}

float Accuracy::getAccuracyNormalized()
{
	return (static_cast<float>(accuracy)) / 100.0f;
}

void Accuracy::setAccuracy(char accuracy)
{
	this->accuracy = accuracy;
}

std::wstring Accuracy::toString()
{
	//if (accuracy != 0)
		return std::to_wstring(accuracy) + std::wstring(L"%");
	//return "";
}

int Accuracy::compareTo(Accuracy *a)
{
	if (accuracy < a->accuracy)
	{
		return 1;
	}
	if (accuracy > a->accuracy)
	{
		return -1;
	}
	return 0;
}

//bool Accuracy::equals(void *o)
//{
//	if (static_cast<Accuracy*>(o) != nullptr)
//	{
//		Accuracy *a = static_cast<Accuracy*>(o);
//		return (accuracy == a->accuracy);
//	}
//	return false;
//}

int Accuracy::hashCode()
{
	return accuracy;
}

Accuracy *Accuracy::getAccuracy(char accuracyValue)
{
	return checkFactory(accuracyValue);
}

Accuracy *Accuracy::getAccuracy(int accuracyValue)
{
	return checkFactory(static_cast<char>(accuracyValue));
}

std::unordered_map<std::wstring, Accuracy*> Accuracy::accuracyFlyWeights;

std::wstring Accuracy::calculatePrimaryKey(char accuracyValue)
{
	return std::to_wstring(accuracyValue);
}

Accuracy *Accuracy::checkFactory(char accuracyValue)
{
	std::wstring primaryKey = calculatePrimaryKey(accuracyValue);
	Accuracy *result = static_cast<Accuracy*>(accuracyFlyWeights[primaryKey]);
	if (result == nullptr)
	{
//		if (log->isTraceEnabled())
//		{
//			log->trace(L"checkFactory(): no existing accuracy found");
//		}
		result = new Accuracy(accuracyValue);
		accuracyFlyWeights[primaryKey] = result;
	}
	return result;
}
