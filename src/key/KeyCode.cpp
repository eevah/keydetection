#include "KeyCode.h"

//using com::mixshare::rapid_evolution::RE3Properties;
KeyCode *KeyCode::NO_KEYCODE = new KeyCode();

KeyCode::KeyCode()
{
}

KeyCode::KeyCode(__int8 keyValue, char scaleType, __int8 shift)
{
//	if (log->isTraceEnabled())
//	{
//		log->trace(std::wstring(L"KeyCode(): keyValue=") + keyValue + std::wstring(L", scaleType=") + scaleType + std::wstring(L", shift=") + std::to_wstring(shift));
//	}
	this->keyValue = keyValue;
	this->scaleType = scaleType;
	this->shift = shift;
}

__int8 KeyCode::getKeyValue()
{
	return keyValue;
}

__int8 KeyCode::getShift()
{
	return shift;
}

char KeyCode::getScaleType()
{
	return scaleType;
}

bool KeyCode::isValid()
{
	return ((keyValue != std::numeric_limits<char>::min()) && (scaleType != std::numeric_limits<wchar_t>::min()) && (shift != std::numeric_limits<char>::min()));
}

bool KeyCode::isMinor()
{
	return ((scaleType == 'A') || (scaleType == 'D') || (scaleType == 'P') || (scaleType == 'C'));
}

std::string KeyCode::toString()
{
	//TODO: Create properties file
	//return toString(RE3Properties::getBoolean(L"show_advanced_key_information"));
	return toString(true);
}

std::string KeyCode::toString(bool showDetails)
{
	if (showDetails)
	{
		if (cachedToStringWithDetails == "")
		{
			cachedToStringWithDetails = calculateKeyCodeString(showDetails);
		}
		return cachedToStringWithDetails;
	}
	else
	{
		if (cachedToString == "")
		{
			cachedToString = calculateKeyCodeString(showDetails);
		}
		return cachedToString;
	}
}

std::string KeyCode::toFileFriendlyString()
{
	std::string shortKeyCode = toString(false);
	if ((shortKeyCode == "") || shortKeyCode == "")
	{
		return "";
	}
	if (shortKeyCode.length() <= 2)
	{
		return std::string("0") + shortKeyCode;
	}
	return shortKeyCode;
}

void KeyCode::invalidate()
{
	cachedToString = "";
	cachedToStringWithDetails = "";
}

int KeyCode::compareTo(KeyCode *oKeyCode)
{
	if (isValid() && oKeyCode->isValid())
	{
		if (keyValue < oKeyCode->keyValue)
		{
			return -1;
		}
		if (keyValue > oKeyCode->keyValue)
		{
			return 1;
		}
		if (isMinor() && !oKeyCode->isMinor())
		{
			return -1;
		}
		if (!isMinor() && oKeyCode->isMinor())
		{
			return 1;
		}
		if (scaleType < oKeyCode->scaleType)
		{
			return -1;
		}
		if (scaleType > oKeyCode->scaleType)
		{
			return 1;
		}
		if (shift < oKeyCode->shift)
		{
			return -1;
		}
		if (shift > oKeyCode->shift)
		{
			return 1;
		}
		return 0;
	}
	if (isValid())
	{
		return -1;
	}
	if (oKeyCode->isValid())
	{
		return 1;
	}
	return 0;
}

std::string KeyCode::calculateKeyCodeString(bool showDetails)
{
	std::string result = "";

	if (!isValid())
	{
		return result;
	}
	else
	{
		//StringBuilder *result = new StringBuilder();
		//TODO: Create properties file
		//if ((keyValue < 10) && RE3Properties::getBoolean(L"prefix_keycode_values"))
		if ((keyValue < 10) && true)
		{
			result += "0"; //->append("0");
		}
		result += std::to_string(keyValue); //->append(keyValue);
		if (showDetails)
		{
			char displayScaleType = scaleType;
			if (displayScaleType == 'I')
			{
				displayScaleType = 'B';
			}
			result += displayScaleType; //->append(displayScaleType);
		}
		else
		{
			if ((scaleType == 'I') || (scaleType == 'L') || (scaleType == 'M'))
			{
				result += 'B'; //->append('B');
			}
			else
			{
				result += 'A'; //->append('A');
			}
		}
		if (shift > 0)
		{
			result += " +"; //->append(" +");
			result += std::to_string(shift); //->append(shift);
		}
		else if (shift < 0)
		{
			result += ' '; //->append(" ");
			result += std::to_string(shift); //->append(shift);
		}
		return result; //->toString();
	}
}

KeyCode *KeyCode::getKeyCode(__int8 keyValue, char scaleType, __int8 shift)
{
	std::string primaryKey = calculatePrimaryKey(keyValue, scaleType, shift);
	KeyCode *result = static_cast<KeyCode*>(keyCodeFlyWeights[primaryKey]);
	if (result == nullptr)
	{
		result = new KeyCode(keyValue, scaleType, shift);
		keyCodeFlyWeights[primaryKey] = result;
	}
	return result;
}

//TODO: Commented out because it's not used anywhere yet
//void KeyCode::invalidateCache()
//{
//	Iterator<KeyCode*> iter = keyCodeFlyWeights.values().begin();
//	while (iter->hasNext())
//	{
//		KeyCode *keyCode = static_cast<KeyCode*>(iter->next());
//		keyCode->invalidate();
//		iter++;
//	}
//}

std::unordered_map<std::string, KeyCode*> KeyCode::keyCodeFlyWeights;

std::string KeyCode::calculatePrimaryKey(__int8 keyValue, char scaleType, __int8 shift)
{
	StringBuilder *result = new StringBuilder();
	result->append(keyValue);
	result->append(L",");
	result->append(scaleType);
	result->append(L",");
	result->append(shift);
	return result->toString();
}

std::string KeyCode::getCachedToString()
{
	return cachedToString;
}

void KeyCode::setCachedToString(const std::string &cachedToString)
{
	this->cachedToString = cachedToString;
}

std::string KeyCode::getCachedToStringWithDetails()
{
	return cachedToStringWithDetails;
}

void KeyCode::setCachedToStringWithDetails(const std::string &cachedToStringWithDetails)
{
	this->cachedToStringWithDetails = cachedToStringWithDetails;
}

void KeyCode::setKeyValue(char keyValue)
{
	this->keyValue = keyValue;
}

void KeyCode::setScaleType(char scaleType)
{
	this->scaleType = scaleType;
}

void KeyCode::setShift(char shift)
{
	this->shift = shift;
}
