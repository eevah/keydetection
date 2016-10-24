#include "KeyProbability.h"
#include "filters/KeyProbabilityFilter.h"
#include "filters/SingleKeyProbabilityFilter.h"
#include "filters/MultiKeyProbabilityFilter.h"
#include "DetectedKey.h"
#include "filters/KeyProbabilitySet.h"

double KeyProbability::analyze_segment_size = 0.1;


struct {
	bool operator() (SortObjectWrapper& lhs, SortObjectWrapper& rhs) {
		return (lhs.getValue() < rhs.getValue()); // sort in ascending order
	}
} compareKeyProbabilities;

KeyProbability::KeyProbability(double segmentTime)
{
	segment_totals.resize(12);

	double ionianProb[] = {0.2, 0.0, 0.12, 0.0, 0.16, 0.12, 0.0, 0.16, 0.0, 0.12, 0.0, 0.12};
	std::vector<double> vectIonianProb = std::vector<double>(ionianProb, ionianProb + sizeof ionianProb / sizeof ionianProb[0]);
	filters.push_back(new SingleKeyProbabilityFilter(true, "ionian", vectIonianProb));

	double lydianProb[] = {0.2, 0.0, 0.12, 0.0, 0.16, 0.0, 0.12, 0.16, 0.0, 0.12, 0.0, 0.12};
	std::vector<double> vectLydianProb = std::vector<double>(lydianProb, lydianProb + sizeof lydianProb / sizeof lydianProb[0]);
	filters.push_back(new SingleKeyProbabilityFilter(true, "lydian", vectLydianProb));

	double mixolydianProb[] = {0.2, 0.0, 0.12, 0.0, 0.16, 0.12, 0.0, 0.16, 0.0, 0.12, 0.12, 0.0};
	std::vector<double> vectMixolydianProb = std::vector<double>(mixolydianProb, mixolydianProb + sizeof mixolydianProb / sizeof mixolydianProb[0]);
	filters.push_back(new SingleKeyProbabilityFilter(true, "mixolydian", vectMixolydianProb));

	double aeolianProb1[] = {0.2, 0.0, 0.12, 0.16, 0.0, 0.12, 0.0, 0.16, 0.12, 0.0, 0.12, 0.0};
	double aeolianProb2[] = {0.2, 0.0, 0.12, 0.16, 0.0, 0.12, 0.0, 0.16, 0.12, 0.0, 0.0, 0.12};
	std::vector<std::vector<double>> aeolianProbVect = RectangularVectors::ReturnRectangularDoubleVector(2, 12);
	aeolianProbVect[0] = std::vector<double>(aeolianProb1, aeolianProb1 + sizeof aeolianProb1 / sizeof aeolianProb1[0]);
	aeolianProbVect[1] = std::vector<double>(aeolianProb2, aeolianProb2 + sizeof aeolianProb2 / sizeof aeolianProb2[0]);
	filters.push_back(new MultiKeyProbabilityFilter(false, "aeolian", aeolianProbVect)); // harmonic

	double dorianProb1[] = {0.2, 0.0, 0.12, 0.16, 0.0, 0.12, 0.0, 0.16, 0.0, 0.12, 0.12, 0.0};
	double dorianProb2[] = {0.2, 0.0, 0.12, 0.16, 0.0, 0.12, 0.0, 0.16, 0.0, 0.12, 0.0, 0.12};
	std::vector<std::vector<double>> dorianProbVect = RectangularVectors::ReturnRectangularDoubleVector(2, 12);
	dorianProbVect[0] = std::vector<double>(dorianProb1, dorianProb1 + sizeof dorianProb1 / sizeof dorianProb1[0]);
	dorianProbVect[1] = std::vector<double>(dorianProb2, dorianProb2 + sizeof dorianProb2 / sizeof dorianProb2[0]);
	filters.push_back(new MultiKeyProbabilityFilter(false, "dorian", dorianProbVect)); // augmented


	double phrygianProb[] = {0.2, 0.12, 0.0, 0.16, 0.0, 0.12, 0.0, 0.16, 0.12, 0.0, 0.12, 0.0};
	std::vector<double> vectPhrygianProb = std::vector<double>(phrygianProb, phrygianProb + sizeof phrygianProb / sizeof phrygianProb[0]);
	filters.push_back(new SingleKeyProbabilityFilter(false, "phrygian", vectPhrygianProb));
}

DetectedKey *KeyProbability::getDetectedKey()
{
	return getDetectedKey(false);
}

DetectedKey *KeyProbability::getDetectedKey(bool logDetails)
{
	try
	{
		std::vector<SortObjectWrapper> results;
		double best_filter_probability = 0.0;
		double max_probability = 0.0;
		double min_probability = std::numeric_limits<double>::max();
		double total_probability = 0.0;
		if (filters.size() > 0)
		{
			for (int f = 0; f < filters.size(); ++f)
			{
				KeyProbabilityFilter *filter = static_cast<KeyProbabilityFilter*>(filters[f]);
				KeyProbabilitySet *resultSet = filter->getNormalizedProbabilities();
				resultSet->addResults(results);
				double filter_probability = resultSet->getMaxProbability();
				if (filter_probability > max_probability)
				{
					max_probability = filter_probability;
				}
				double min_filter_probability = resultSet->getMinProbability();
				if (min_filter_probability < min_probability)
				{
					min_probability = min_filter_probability;
				}
				double total = resultSet->getTotalProbability();
				total_probability += total;
				if (total > best_filter_probability)
				{
					best_filter_probability = total;
				}
			}
			double average = total_probability / (filters.size() * 12);
			double range = max_probability - min_probability;
			double accuracy = (max_probability - average) / range;
			if (accuracy < 0.0)
			{
				accuracy = 0.0;
			}
			if (accuracy > 1.0)
			{
				accuracy = 1.0;
			}

			//SortObjectWrapper *array_Renamed = &results[0];
			std::vector<SortObjectWrapper> array_Renamed = results;
//			int arrayLength = (sizeof(array_Renamed)/sizeof(*array_Renamed));
			std::sort(array_Renamed.begin(), array_Renamed.end(), compareKeyProbabilities);
			std::vector<double> buckets(12);
			double minor_pts = 0.0;
			int num_minors = 0;
			double major_pts = 0.0;
			int num_majors = 0;
			for (int i = array_Renamed.size()-1; i >= 0; --i)
			{
//				SortObjectWrapper so = static_cast<SortObjectWrapper>(array_Renamed[i]);
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':

//				void *obj = so.getObject();
				SortObjectWrapper so = array_Renamed[i];
				Key *k = so.getObject();
				int st = k->getScaleType();
				KeyCode *kCode = k->getKeyCode();
				k->getKeyCode();
//				std::cout << so.toString() << "\n";
//				std::string soStr = so.toString();
//				Key *kTest = Key::getKey(so.toString());

//				std::cout << kCode->toString() << "\n";
				std::string keycode = kCode->toString();



				//TODO: Make sure this works
//				std::string keycode = Key::getKey(so.toString())->getKeyCode()->toString();
//				if (logDetails && log->isTraceEnabled())
//				{
////JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
//					log->trace(std::wstring(L"debugKeyScores(): key=") + so->getObject()->toString() + std::wstring(L", score=") + so->getValue() + std::wstring(L", keycode=") + keycode);
//				}
//				StringBuilder *keycode_int = new StringBuilder();
				std::string keycode_int = "";

				for (int c = 0; c < keycode.length(); ++c)
				{
					if (std::isdigit(keycode[c]))
					{
						keycode_int += keycode[c]; //->append(keycode[c]);
					}
					else if ((keycode[c] == 'A'))
					{
						minor_pts += so.getValue();
						++num_minors;
					}
					else if ((keycode[c] == 'B'))
					{
						major_pts += so.getValue();
						++num_majors;
					}
				}
				int index = std::stoi(keycode_int) - 1;
				buckets[index] += so.getValue();
			}
//			if (logDetails && log->isTraceEnabled())
//			{
//				log->trace(L"debugKeyScores(): key region buckets=");
//			}
			double max_bucket = 0.0;
			int max_index = -1;
			for (int i = 0; i < 12; ++i)
			{
//				if (logDetails && log->isTraceEnabled())
//				{
//					log->trace(std::wstring(L"debugKeyScores(): \t") + std::to_wstring(i + 1) + std::wstring(L": ") + std::to_wstring(buckets[i]));
//				}
				if (buckets[i] > max_bucket)
				{
					max_bucket = buckets[i];
					max_index = i + 1;
				}
			}
//			if (logDetails && log->isTraceEnabled())
//			{
//				log->trace(std::wstring(L"debugKeyScores(): max region=") + std::to_wstring(max_index));
//			}
//			if (logDetails && log->isTraceEnabled())
//			{
//				log->trace(std::wstring(L"debugKeyScores(): major score=") + std::to_wstring(major_pts));
//			}
//			if (logDetails && log->isTraceEnabled())
//			{
//				log->trace(std::wstring(L"debugKeyScores(): minor score=") + std::to_wstring(minor_pts));
//			}
			for (int i = array_Renamed.size() - 1; i >= 0; --i)
			{
				SortObjectWrapper so = array_Renamed[i];
				if (so.getValue() == 0.0)
				{
					return new DetectedKey(Key::NO_KEY, Key::NO_KEY, 0.0);
				}
				Key *predicted_key = static_cast<Key*>(so.getObject());
//				if (logDetails && log->isTraceEnabled())
//				{
//					log->trace(std::wstring(L"debugKeyScores(): predicted key=") + predicted_key);
//				}
				return new DetectedKey(predicted_key, Key::NO_KEY, accuracy);
			}
		}
	}
	catch (std::exception &e)
	{
		std::cout << "debugKeyScores(): error creating debug output " << e.what() << "\n";
		//log->error(L"debugKeyScores(): error creating debug output", e);
	}
	return nullptr;
}

bool KeyProbability::hasNoData()
{
	bool all_zeros = true;
	for (int f = 0; f < filters.size(); ++f)
	{
		KeyProbabilityFilter *filter = static_cast<KeyProbabilityFilter*>(filters[f]);
		if (!filter->isAllZeros())
		{
			all_zeros = false;
		}
	}
	return all_zeros;
}

void KeyProbability::add(std::vector<double> &totals, double time)
{
	segment_size += time;
	for (int i = 0; i < totals.size(); ++i)
	{
		segment_totals[i] += totals[i];
	}
	if (segment_size > analyze_segment_size)
	{
		processSegment();
	}
}

void KeyProbability::add(std::vector<int> &totals, double time)
{
	segment_size += time;
	for (int i = 0; i < totals.size(); ++i)
	{
		segment_totals[i] += totals[i];
	}
	if (segment_size > analyze_segment_size)
	{
		processSegment();
	}
}

void KeyProbability::finish()
{
	if (segment_size > 0)
	{
		processSegment();
	}
}

void KeyProbability::processSegment()
{
	double total = 0;
	for (int i = 0; i < 12; ++i)
	{
		total += segment_totals[i];
	}
	if (total > 0)
	{
		for (int i = 0; i < 12; ++i)
		{
			segment_totals[i] /= total;
		}
	}
	for (int f = 0; f < filters.size(); ++f)
	{
//		KeyProbabilityFilter *filter = filters[f];
//		std::string s = typeid(filter).name();
		//SingleKeyProbabilityFilter filter1 =  dynamic_cast<SingleKeyProbabilityFilter&> (filters[f]);
		//std::string s = typeid(filter1).name();
		//filter1.add(segment_totals);
//		std::cout << "hi";
//		KeyProbabilityFilter *filter = static_cast<KeyProbabilityFilter*>(filters[f]);
		filters[f]->add(segment_totals);
	}
	segment_size = 0;
	for (int i = 0; i < segment_totals.size(); ++i)
	{
		segment_totals[i] = 0;
	}
}

int KeyProbability::safeindex(int index)
{
	while (index < 1)
	{
		index += 12;
	}
	while (index > 12)
	{
		index -= 12;
	}
	return index;
}
