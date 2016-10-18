#include "Bpm.h"


Bpm *Bpm::NO_BPM = new Bpm(0.0f);

Bpm::Bpm()
{
}

Bpm::Bpm(float bpmValue)
{
	this->bpmValue = bpmValue;
}

Bpm::Bpm(double bpmValue)
{
	this->bpmValue = static_cast<float>(bpmValue);
}

Bpm::Bpm(boost::optional<float> bpmValue)
{
	this->bpmValue = !bpmValue ? 0.0f : bpmValue.get();
}

float Bpm::getBpmValue()
{
	return bpmValue;
}

boost::optional<float> Bpm::getDifference(Bpm *value)
{
	return getBpmDifference(bpmValue, value->getBpmValue());
}

boost::optional<float> Bpm::getDifference(float value)
{
	return getBpmDifference(bpmValue, value);
}

bool Bpm::isValid()
{
	return bpmValue != 0.0f;
}

boost::optional<double> Bpm::getBpmDifference(double sourceBpm, double targetBpm)
{
	if ((sourceBpm == 0.0) || (targetBpm == 0.0))
	{
		return boost::none;
	}
	if (sourceBpm == targetBpm)
	{
		return 0.0;
	}
	double diff_before_shift = targetBpm / sourceBpm * 100.0; // avoids calculating twice
	double diff = diff_before_shift - 100.0;
	if (diff < 0.0)
	{
		double diff2 = diff_before_shift * 2.0 - 100.0;
		if (diff2 == 0.0)
		{
			return 0.0;
		}
		else if (diff2 > 0)
		{
			if (-diff < diff2)
			{
				return diff;
			}
			else
			{
				return diff2;
			}
		}
		else
		{
			return getBpmDifference(sourceBpm, targetBpm * 2.0);
		}
	}
	else
	{ // diff > 0.0
		double diff2 = diff_before_shift / 2.0 - 100.0;
		if (diff2 == 0.0)
		{
			return 0.0;
		}
		else if (diff2 < 0)
		{
			if (diff < -diff2)
			{
				return diff;
			}
			else
			{
				return diff2;
			}
		}
		else
		{
			return getBpmDifference(sourceBpm, targetBpm / 2.0);
		}
	}
}

float Bpm::getBpmDifference(float sourceBpm, float targetBpm)
{
	if ((sourceBpm == 0.0f) || (targetBpm == 0.0f))
	{
		return 0.0f; // TODO: I added this line and commented out the next one
		//return boost::none;

		//TODO: This is because the result of this function is not checked anywhere for NONE (null) and it is float instead of optional float
		//TODO: You must fix this and/or make sure returning 0 doesn't cause problems
	}
	if (sourceBpm == targetBpm)
	{
		return 0.0f;
	}
	float diff_before_shift = targetBpm / sourceBpm * 100.0f; // avoids calculating twice
	float diff = diff_before_shift - 100.0f;
	if (diff < 0.0f)
	{
		float diff2 = diff_before_shift * 2.0f - 100.0f;
		if (diff2 == 0.0f)
		{
			return 0.0f;
		}
		else if (diff2 > 0.0f)
		{
			if (-diff < diff2)
			{
				return diff;
			}
			else
			{
				return diff2;
			}
		}
		else
		{
			return getBpmDifference(sourceBpm, targetBpm * 2.0f);
		}
	}
	else
	{ // diff > 0.0f
		float diff2 = diff_before_shift / 2.0f - 100.0f;
		if (diff2 == 0.0f)
		{
			return 0.0f;
		}
		else if (diff2 < 0.0f)
		{
			if (diff < -diff2)
			{
				return diff;
			}
			else
			{
				return diff2;
			}
		}
		else
		{
			return getBpmDifference(sourceBpm, targetBpm / 2.0f);
		}
	}
}

void Bpm::setBpmValue(float bpmValue)
{
	this->bpmValue = bpmValue;
}

float Bpm::getSimilarityWith(Bpm *otherBpm)
{
	return getSimilarity(bpmValue, otherBpm->bpmValue);
}

float Bpm::getSimilarity(float bpmValue1, float bpmValue2)
{
	if ((bpmValue1 == 0.0f) || (bpmValue2 == 0.0f))
	{
		return 0.0f;
	}
	float absDiff = std::abs(bpmValue1 - bpmValue2);
	float total = bpmValue1 + bpmValue2;
	float similarity = (total - absDiff * 2.0f) / total;
	return similarity;
}

std::wstring Bpm::toString()
{
	return toString(false);
}

std::wstring Bpm::toString(bool rounded)
{
	if (bpmValue != 0.0f)
	{
		if (rounded)
		{

			return std::to_wstring(std::round(bpmValue));
		}
		else
		{
			return std::to_wstring(bpmValue);
		}
	}
	return L"";
}

int Bpm::compareTo(Bpm *b)
{
	if ((bpmValue != 0.0f) && (b->bpmValue != 0.0f))
	{
		if (bpmValue < b->bpmValue)
		{
			return -1;
		}
		if (bpmValue > b->bpmValue)
		{
			return 1;
		}
		return 0;
	}
	if (bpmValue != 0.0f)
	{
		return -1;
	}
	if (b->bpmValue != 0.0f)
	{
		return 1;
	}
	return 0;
}

//bool Bpm::equals(void *o)
//{
//	if (dynamic_cast<Bpm*>(o) != nullptr)
//	{
//		Bpm *b = static_cast<Bpm*>(o);
//		return (bpmValue == b->bpmValue);
//	}
//	return false;
//}

int Bpm::hashCode()
{
	return static_cast<int>(bpmValue * 100);
}

