#include "KeyRelation.h"

char KeyRelation::RELATION_TONIC = 0;
char KeyRelation::RELATION_TONIC_MODAL = 1;
char KeyRelation::RELATION_DOMINANT = 2;
char KeyRelation::RELATION_DOMINANT_MODAL = 3;
char KeyRelation::RELATION_SUBDOMINANT = 4;
char KeyRelation::RELATION_SUBDOMINANT_MODAL = 5;
char KeyRelation::RELATION_RELATIVE_TONIC = 6;
char KeyRelation::RELATION_RELATIVE_DOMINANT = 7;
char KeyRelation::RELATION_RELATIVE_SUBDOMINANT = 8;
char KeyRelation::RELATION_NONE = std::numeric_limits<char>::max();
KeyRelation *KeyRelation::INVALID_RELATION = new KeyRelation(-std::numeric_limits<float>::infinity(), RELATION_NONE);

KeyRelation::KeyRelation()
{
}

KeyRelation::KeyRelation(float difference, char relationship)
{
//	if (log->isTraceEnabled())
//	{
//		log->trace(std::wstring(L"KeyRelation(): difference=") + difference + std::wstring(L", relationship=") + std::to_wstring(relationship));
//	}
	this->difference = difference;
	this->relationship = relationship;
}

float KeyRelation::getDifference()
{
	return difference;
}

char KeyRelation::getRelationship()
{
	return relationship;
}

bool KeyRelation::hasDifference()
{
	return (difference != -std::numeric_limits<float>::infinity());
}

bool KeyRelation::isCompatible()
{
	return isCompatible(true);
}

bool KeyRelation::isCompatible(bool strict)
{
	return isCompatible(relationship, strict);
}

bool KeyRelation::isCompatible(char relationship, bool strict)
{
	if (strict)
	{
		return (relationship != RELATION_NONE) && (relationship != RELATION_RELATIVE_DOMINANT) && (relationship != RELATION_RELATIVE_SUBDOMINANT);
	}
	return relationship != RELATION_NONE;
}

bool KeyRelation::isValid()
{
	return difference != -std::numeric_limits<float>::infinity();
}

void KeyRelation::setDifference(float difference)
{
	this->difference = difference;
}

void KeyRelation::setRelationship(char relationship)
{
	this->relationship = relationship;
}

int KeyRelation::compareTo(KeyRelation *oRelation)
{
	if (relationship < oRelation->getRelationship())
	{
		return -1;
	}
	if (relationship > oRelation->getRelationship())
	{
		return 1;
	}
	return 0;
}

std::wstring KeyRelation::toString()
{
	return toString(relationship);
}

std::wstring KeyRelation::toString(char relationship)
{
	if (relationship == RELATION_NONE)
	{
		return L"";
	}
	else if (relationship == RELATION_TONIC)
	{
		return L"Tonic";
	}
	else if (relationship == RELATION_SUBDOMINANT)
	{
		return L"Subdominant";
	}
	else if (relationship == RELATION_DOMINANT)
	{
		return L"Dominant";
	}
	else if (relationship == RELATION_TONIC_MODAL)
	{
		return L"Tonic Modal";
	}
	else if (relationship == RELATION_SUBDOMINANT_MODAL)
	{
		return L"Subdominant Modal";
	}
	else if (relationship == RELATION_DOMINANT_MODAL)
	{
		return L"Dominant Modal";
	}
	else if (relationship == RELATION_RELATIVE_TONIC)
	{
		return L"Relative Tonic";
	}
	else if (relationship == RELATION_RELATIVE_SUBDOMINANT)
	{
		return L"Relative Subdominant";
	}
	else if (relationship == RELATION_RELATIVE_DOMINANT)
	{
		return L"Relative Dominant";
	}
	return L"";
}
