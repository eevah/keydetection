#include "SortObjectWrapper.h"


SortObjectWrapper::SortObjectWrapper(Key *key, double sort_value)
{
	this->object = key;
	this->sort_value = sort_value;
}

Key* SortObjectWrapper::getObject()
{
	return object;
}

double SortObjectWrapper::getValue()
{
	return sort_value;
}

void SortObjectWrapper::setValue(double value)
{
	this->sort_value = value;
}

std::string SortObjectWrapper::toString()
{
//TODO TASK: Make sure that this works
//	std::stringstream ss;
//	ss << object;
	return "ERROR, DON'T USE THIS";
}

//int SortObjectWrapper::compareTo(SortObjectWrapper *sO)
//{
//	if (sort_value < sO->sort_value)
//	{
//		return -1;
//	}
//	else if (sort_value > sO->sort_value)
//	{
//		return 1;
//	}
//	return 0;
//}