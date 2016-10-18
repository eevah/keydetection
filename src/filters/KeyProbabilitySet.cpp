#include <limits>
#include "KeyProbabilitySet.h"

constexpr double lowest_double = std::numeric_limits<double>::lowest();
const bool detect_advanced_keys = false; //TODO: this is from prop. file

KeyProbabilitySet::KeyProbabilitySet(std::vector<double> &normalizedProbabilities, bool major, const std::string &type)
{
    this->normalizedProbabilities = normalizedProbabilities;
    this->major = major;
    this->type = type;
    //TODO: Enable logging
//    if (log->isDebugEnabled())
//    {
//        double total = 0.0;
//        for (int i = 0; i < normalizedProbabilities.size(); ++i)
//        {
//            total += normalizedProbabilities[i];
//        }
//        double diff = std::abs(total - 1.0);
//        if (diff > 0.00001)
//        {
//            log->debug(std::wstring(L"KeyProbabilitySet(): improper probability set, total=") + std::to_wstring(total));
//        }
//    }
}

double KeyProbabilitySet::getProbability(int index)
{
    return normalizedProbabilities[index];
}

double KeyProbabilitySet::getMaxProbability()
{
    double maximum = lowest_double;
    for (int i = 0; i < 12; ++i)
    {
        if (normalizedProbabilities[i] > maximum)
        {
            maximum = normalizedProbabilities[i];
        }
    }
    return maximum;
}

double KeyProbabilitySet::getTotalProbability()
{
    double total = 0.0;
    for (int i = 0; i < 12; ++i)
    {
        total += normalizedProbabilities[i];
    }
    return total;
}

double KeyProbabilitySet::getMinProbability()
{
    double minimum = std::numeric_limits<double>::max();
    for (int i = 0; i < 12; ++i)
    {
        if (normalizedProbabilities[i] < minimum)
        {
            minimum = normalizedProbabilities[i];
        }
    }
    return minimum;
}

Key *KeyProbabilitySet::getKey()
{
    double maximum = lowest_double;
    int index = -1;
    for (int i = 0; i < 12; ++i)
    {
        if (normalizedProbabilities[i] > maximum)
        {
            maximum = normalizedProbabilities[i];
            index = i;
        }
    }
    return getKey(index, major, type);
}

std::string KeyProbabilitySet::getType()
{
    return type;
}

bool KeyProbabilitySet::isMajor()
{
    return major;
}


//TODO: just push data to results and modify SortObjectWrapper
void KeyProbabilitySet::addResults(std::vector<SortObjectWrapper> &results)
{
    for (int i = 0; i < 12; ++i)
    {
        Key *tempKey = getKey(i, major, type);
        SortObjectWrapper tempVar(tempKey, normalizedProbabilities[i]);
        results.push_back(tempVar);
    }
}

Key *KeyProbabilitySet::getKey(int index, bool major, const std::string &type)
{
    StringBuilder *key = new StringBuilder();
    if (index == 0)
    {
        key->append("A");
    }
    else if (index == 1)
    {
        key->append("A#");
    }
    else if (index == 2)
    {
        key->append("B");
    }
    else if (index == 3)
    {
        key->append("C");
    }
    else if (index == 4)
    {
        key->append("C#");
    }
    else if (index == 5)
    {
        key->append("D");
    }
    else if (index == 6)
    {
        key->append("D#");
    }
    else if (index == 7)
    {
        key->append("E");
    }
    else if (index == 8)
    {
        key->append("F");
    }
    else if (index == 9)
    {
        key->append("F#");
    }
    else if (index == 10)
    {
        key->append("G");
    }
    else if (index == 11)
    {
        key->append("G#");
    }
    else
    {
        return Key::NO_KEY;
    }
    if (!major)
    {
        key->append("m");
    }
    if (detect_advanced_keys)//RE3Properties::getBoolean(L"detect_advanced_keys"))
    {
        key->append(" ");
        key->append(type);
    }

    std::string keyStr = key->toString();
    boost::algorithm::trim(keyStr);
    return Key::getKey(keyStr);
}

