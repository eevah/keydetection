#include "ShiftedKeyNotation.h"

ShiftedKeyNotation::ShiftedKeyNotation()
{
}

ShiftedKeyNotation::ShiftedKeyNotation(float root_value)
{
//	if (log->isTraceEnabled())
//	{
//		log->trace(std::wstring(L"ShiftedKeyNotation(): root_value=") + std::to_wstring(root_value));
//	}
	for (char i = 0; i < 12; ++i)
	{
		float diff = root_value - static_cast<float>(i);
		if (diff >= 11)
		{
			diff -= 12;
		}
		if (diff <= -11)
		{
			diff += 12;
		}
		if (std::abs(diff) <= 0.5)
		{
			rootNote = i;
			shift = diff;
		}
	}
}

ShiftedKeyNotation::ShiftedKeyNotation(char rootNote, float shift)
{
	this->rootNote = rootNote;
	this->shift = shift;
}

char ShiftedKeyNotation::getRootNote()
{
	return rootNote;
}

float ShiftedKeyNotation::getShift()
{
	return shift;
}

int ShiftedKeyNotation::getShiftInCents()
{
	return static_cast<int>(100.0 * shift);
}

char ShiftedKeyNotation::getRoot_note()
{
	return rootNote;
}

void ShiftedKeyNotation::setRootNote(char rootNote)
{
	this->rootNote = rootNote;
}

void ShiftedKeyNotation::setShift(float shift)
{
	this->shift = shift;
}
