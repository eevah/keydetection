#include <math.h>
#include "Key.h"
#include "../Bpm.h"
#include <boost/algorithm/string.hpp>
#include <iostream>

const bool propShowAdvancedKeyInfo = false;
const std::string propPreferredKeyFormat = "sharp"; // {sharp, flat, keycode}

const float M_E = 2.718281828459045;
const __int8 semiTonesPerOctave = 12;

float Key::bpmDifferencePerSemitone = static_cast<float> ( pow(M_E, (log(2) / semiTonesPerOctave)) * 100.0f - 100.0f );
int Key::SCALE_UNKNOWN = -1;
int Key::SCALE_IONIAN = 0;
int Key::SCALE_AEOLIAN = 1;
int Key::SCALE_LYDIAN = 2;
int Key::SCALE_MIXOLYDIAN = 3;
int Key::SCALE_DORIAN = 4;
int Key::SCALE_PHRYGIAN = 5;
int Key::SCALE_LOCRIAN = 6;
float Key::ROOT_UNKNOWN = -std::numeric_limits<float>::infinity();
std::vector<std::wstring> Key::wellFormedKeys = {L"A", L"Am", L"A#", L"Bb", L"A#m", L"Bbm", L"B", L"Bm", L"C", L"Cm", L"Db", L"C#", L"Dbm", L"C#m", L"D", L"Dm", L"Eb", L"D#", L"Ebm", L"D#m", L"E", L"Em", L"F", L"Fm", L"Gb", L"F#", L"Gbm", L"F#m", L"G", L"Gm", L"Ab", L"G#", L"Abm", L"G#m"};
std::vector<std::wstring> Key::advancedModes = {L"ionian", L"aeolian", L"lydian", L"mixolydian", L"dorian", L"phrygian", L"locrian"};
std::vector<std::wstring> Key::keycodeSuffixes = {L"A", L"B", L"I", L"L", L"M", L"D", L"P", L"C"};
bool Key::useFlatNotation = false;
Key *Key::NO_KEY = new Key(ROOT_UNKNOWN, SCALE_UNKNOWN);

Key::Key()
{
}

Key::Key(float rootValue, int scaleType)
{
	this->rootValue = rootValue;
	this->scaleType = scaleType;
	validateRootValue();
	shiftedNotation = new ShiftedKeyNotation(rootValue);
}

float Key::getRootValue()
{
	return rootValue;
}

std::string Key::getRootNoteDescription()
{
	int root_note = shiftedNotation->getRootNote();
	if (root_note == 0)
	{
		return "A";
	}
	if (root_note == 1)
	{
		return useFlatNotation ? "Bb" : "A#";
	}
	if (root_note == 2)
	{
		return "B";
	}
	if (root_note == 3)
	{
		return "C";
	}
	if (root_note == 4)
	{
		return useFlatNotation ? "Db" : "C#";
	}
	if (root_note == 5)
	{
		return "D";
	}
	if (root_note == 6)
	{
		return useFlatNotation ? "Eb" : "D#";
	}
	if (root_note == 7)
	{
		return "E";
	}
	if (root_note == 8)
	{
		return "F";
	}
	if (root_note == 9)
	{
		return useFlatNotation ? "Gb" : "F#";
	}
	if (root_note == 10)
	{
		return "G";
	}
	if (root_note == 11)
	{
		return useFlatNotation ? "Ab" : "G#";
	}
	return "UNKNOWN";
}

int Key::getScaleType()
{
	return scaleType;
}

std::string Key::getScaleTypeDescription()
{
	if (scaleType == 0)
	{
		return "ionian";
	}
	else if (scaleType == 1)
	{
		return "aeolian";
	}
	else if (scaleType == 2)
	{
		return "lydian";
	}
	else if (scaleType == 3)
	{
		return "mixolydian";
	}
	else if (scaleType == 4)
	{
		return "dorian";
	}
	else if (scaleType == 5)
	{
		return "phrygian";
	}
	else if (scaleType == 6)
	{
		return "locrian";
	}
	else
	{
		return "UNKNOWN";
	}
}

bool Key::isMinor()
{
	return ((scaleType == SCALE_AEOLIAN) || (scaleType == SCALE_DORIAN) || (scaleType == SCALE_PHRYGIAN) || (scaleType == SCALE_LOCRIAN));
}

ShiftedKeyNotation *Key::getShiftedKeyNotation()
{
	return shiftedNotation;
}

std::string Key::getShiftDescription()
{
	float shift = shiftedNotation->getShift();
	int shift_in_cents = static_cast<int>(shift * 100.0);
	if (shift_in_cents == 0)
	{
		return "NONE";
	}
	if (shift_in_cents > 0)
	{
		return std::string("+") + std::to_string(shift_in_cents);
	}
	else
	{
		return std::to_string(shift_in_cents);
	}
}

std::string Key::toString()
{
	return getPreferredKeyNotation();
}

std::string Key::toStringExact()
{
	return getPreferredKeyNotation(true);
}

std::string Key::getKeyNotationFlat()
{
	return getKeyNotationFlat(false);
}

std::string Key::getKeyNotationFlat(bool showDetails)
{
	if (rootValue == ROOT_UNKNOWN)
	{
		return "";
	}
	int root_note = shiftedNotation->getRootNote();
	StringBuilder *result = new StringBuilder();
	if (isMinor())
	{
		if (root_note == 0)
		{
			result->append("Am");
		}
		if (root_note == 1)
		{
			result->append("Bbm");
		}
		if (root_note == 2)
		{
			result->append("Bm");
		}
		if (root_note == 3)
		{
			result->append("Cm");
		}
		if (root_note == 4)
		{
			result->append("Dbm");
		}
		if (root_note == 5)
		{
			result->append("Dm");
		}
		if (root_note == 6)
		{
			result->append("Ebm");
		}
		if (root_note == 7)
		{
			result->append("Em");
		}
		if (root_note == 8)
		{
			result->append("Fm");
		}
		if (root_note == 9)
		{
			result->append("Gbm");
		}
		if (root_note == 10)
		{
			result->append("Gm");
		}
		if (root_note == 11)
		{
			result->append("Abm");
		}
	}
	else
	{
		if (root_note == 0)
		{
			result->append("A");
		}
		if (root_note == 1)
		{
			result->append("Bb");
		}
		if (root_note == 2)
		{
			result->append("B");
		}
		if (root_note == 3)
		{
			result->append("C");
		}
		if (root_note == 4)
		{
			result->append("Db");
		}
		if (root_note == 5)
		{
			result->append("D");
		}
		if (root_note == 6)
		{
			result->append("Eb");
		}
		if (root_note == 7)
		{
			result->append("E");
		}
		if (root_note == 8)
		{
			result->append("F");
		}
		if (root_note == 9)
		{
			result->append("Gb");
		}
		if (root_note == 10)
		{
			result->append("G");
		}
		if (root_note == 11)
		{
			result->append("Ab");
		}
	}
	if (showDetails)
	{
		appendMode(result);
	}
	appendShift(result);
	return result->toString();
}

std::string Key::getKeyNotationSharp()
{
	return getKeyNotationSharp(false);
}

std::string Key::getKeyNotationSharp(bool showDetails)
{
	if (rootValue == ROOT_UNKNOWN)
	{
		return "";
	}
	int root_note = shiftedNotation->getRootNote();
	StringBuilder *result = new StringBuilder();
	if (isMinor())
	{
		if (root_note == 0)
		{
			result->append("Am");
		}
		if (root_note == 1)
		{
			result->append("A#m");
		}
		if (root_note == 2)
		{
			result->append("Bm");
		}
		if (root_note == 3)
		{
			result->append("Cm");
		}
		if (root_note == 4)
		{
			result->append("C#m");
		}
		if (root_note == 5)
		{
			result->append("Dm");
		}
		if (root_note == 6)
		{
			result->append("D#m");
		}
		if (root_note == 7)
		{
			result->append("Em");
		}
		if (root_note == 8)
		{
			result->append("Fm");
		}
		if (root_note == 9)
		{
			result->append("F#m");
		}
		if (root_note == 10)
		{
			result->append("Gm");
		}
		if (root_note == 11)
		{
			result->append("G#m");
		}
	}
	else
	{
		if (root_note == 0)
		{
			result->append("A");
		}
		if (root_note == 1)
		{
			result->append("A#");
		}
		if (root_note == 2)
		{
			result->append("B");
		}
		if (root_note == 3)
		{
			result->append("C");
		}
		if (root_note == 4)
		{
			result->append("C#");
		}
		if (root_note == 5)
		{
			result->append("D");
		}
		if (root_note == 6)
		{
			result->append("D#");
		}
		if (root_note == 7)
		{
			result->append("E");
		}
		if (root_note == 8)
		{
			result->append("F");
		}
		if (root_note == 9)
		{
			result->append("F#");
		}
		if (root_note == 10)
		{
			result->append("G");
		}
		if (root_note == 11)
		{
			result->append("G#");
		}
	}
	if (showDetails)
	{
		appendMode(result);
	}
	appendShift(result);
	return result->toString();
}

std::string Key::getCustomKeyNotation()
{
	return getCustomKeyNotation(false);
}

std::string Key::getCustomKeyNotation(bool showDetails)
{
	if (rootValue == ROOT_UNKNOWN)
	{
		return "";
	}
	StringBuilder *result = new StringBuilder();
	result->append(getRootNoteDescription());
	if (isMinor())
	{
		result->append("m");
	}
	if (showDetails)
	{
		appendMode(result);
	}
	appendShift(result);
	return result->toString();
}

KeyCode *Key::getKeyCode()
{
	if (rootValue == ROOT_UNKNOWN)
	{
		return KeyCode::NO_KEYCODE;
	}
	else
	{
		int root_note = shiftedNotation->getRootNote();
		char keyCodeValue = -1;
		bool minor = isMinor();
		wchar_t keyCodeScaleType = minor ? L'A' : L'B';
		if (minor)
		{
			if (root_note == 0)
			{
				keyCodeValue = 8;
			}
			else if (root_note == 1)
			{
				keyCodeValue = 3;
			}
			else if (root_note == 2)
			{
				keyCodeValue = 10;
			}
			else if (root_note == 3)
			{
				keyCodeValue = 5;
			}
			else if (root_note == 4)
			{
				keyCodeValue = 12;
			}
			else if (root_note == 5)
			{
				keyCodeValue = 7;
			}
			else if (root_note == 6)
			{
				keyCodeValue = 2;
			}
			else if (root_note == 7)
			{
				keyCodeValue = 9;
			}
			else if (root_note == 8)
			{
				keyCodeValue = 4;
			}
			else if (root_note == 9)
			{
				keyCodeValue = 11;
			}
			else if (root_note == 10)
			{
				keyCodeValue = 6;
			}
			else if (root_note == 11)
			{
				keyCodeValue = 1;
			}
		}
		else
		{
			if (root_note == 0)
			{
				keyCodeValue = 11;
			}
			else if (root_note == 1)
			{
				keyCodeValue = 6;
			}
			else if (root_note == 2)
			{
				keyCodeValue = 1;
			}
			else if (root_note == 3)
			{
				keyCodeValue = 8;
			}
			else if (root_note == 4)
			{
				keyCodeValue = 3;
			}
			else if (root_note == 5)
			{
				keyCodeValue = 10;
			}
			else if (root_note == 6)
			{
				keyCodeValue = 5;
			}
			else if (root_note == 7)
			{
				keyCodeValue = 12;
			}
			else if (root_note == 8)
			{
				keyCodeValue = 7;
			}
			else if (root_note == 9)
			{
				keyCodeValue = 2;
			}
			else if (root_note == 10)
			{
				keyCodeValue = 9;
			}
			else if (root_note == 11)
			{
				keyCodeValue = 4;
			}
		}
		if (scaleType == SCALE_DORIAN)
		{
			keyCodeScaleType = L'D';
			++keyCodeValue;
		}
		else if (scaleType == SCALE_PHRYGIAN)
		{
			keyCodeScaleType = L'P';
			--keyCodeValue;
		}
		else if (scaleType == SCALE_LYDIAN)
		{
			keyCodeScaleType = L'L';
			++keyCodeValue;
		}
		else if (scaleType == SCALE_MIXOLYDIAN)
		{
			keyCodeScaleType = L'M';
			--keyCodeValue;
		}
		else if (scaleType == SCALE_LOCRIAN)
		{
			keyCodeScaleType = L'C';
			keyCodeValue -= 2;
		}
		else if (scaleType == SCALE_IONIAN)
		{
			keyCodeScaleType = L'I';
		}
		if (keyCodeValue < 1)
		{
			keyCodeValue += 12;
		}
		if (keyCodeValue > 12)
		{
			keyCodeValue -= 12;
		}
		char shift = static_cast<char>(shiftedNotation->getShift() * 100.0);
		return KeyCode::getKeyCode(keyCodeValue, keyCodeScaleType, shift);
	}
}

std::string Key::getGroupSSLString()
{
	if (rootValue == ROOT_UNKNOWN)
	{
		return "";
	}
	StringBuilder *result = new StringBuilder();
	result->append(getKeyCode());
	result->append(" ");
	result->append(getKeyNotationSharp());
	return result->toString();
}

std::string Key::getID3SafeKeyNotation()
{
	return getKeyNotationSharp(false);
}

std::string Key::getShortKeyNotation()
{
	return getPreferredKeyNotation(false);
}

std::string Key::getPreferredKeyNotation(const std::string &key)
{
	return Key::getKey(key)->getPreferredKeyNotation();
}

std::string Key::getPreferredKeyNotation()
{
	return getPreferredKeyNotation(propShowAdvancedKeyInfo);
}

std::string Key::getPreferredKeyNotation(bool showDetails)
{
	if (boost::iequals(propPreferredKeyFormat, "sharp"))
	{
		return getKeyNotationSharp(showDetails);
	}
	if (boost::iequals(propPreferredKeyFormat, "flat"))//(RE3Properties::getProperty(L"preferred_key_format").equalsIgnoreCase(L"flat"))
	{
		return getKeyNotationFlat(showDetails);
	}
	if (boost::iequals(propPreferredKeyFormat, "keycode"))// (RE3Properties::getProperty(L"preferred_key_format").equalsIgnoreCase(L"keycode"))
	{
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
		return getKeyCode()->toString(showDetails);
	}
	return getKeyNotationSharp(showDetails);
}

bool Key::isValid()
{
	return (rootValue != ROOT_UNKNOWN);
}

//bool Key::isWellFormed(const std::wstring &input)
//{
//	if ((input == "") || input == "")
//	{
//		return false;
//	}
//
//    //TODO: Ivana - created copy of input
//
//    std::wstring inputCopy = boost::to_lower_copy(input);
//    //input = boost::to_lower_copy(input);
//
//    // remove shift
//	int shift_index = (int)inputCopy.find(L"+");
//	if (shift_index >= 0)
//	{
//        inputCopy = boost::trim_copy(inputCopy.substr(0, shift_index));
//	}
//	shift_index = (int)inputCopy.find(L"-");
//	if (shift_index >= 0)
//	{
//        inputCopy = boost::trim_copy(inputCopy.substr(0, shift_index));
//	}
//	// remove advanced modes
//	for (int i = 0; i < advancedModes.size(); ++i)
//	{
//		int mode_index = (int)inputCopy.find(advancedModes[i]);
//		if (mode_index >= 0)
//		{
//            inputCopy = boost::trim_copy(inputCopy.substr(0, mode_index));
//		}
//	}
//	// check for normal keys
//	for (int i = 0; i < wellFormedKeys.size(); ++i)
//	{
//		if (boost::iequals(inputCopy, wellFormedKeys[i]))
//		{
//			return true;
//		}
//	}
//	// check for valid keycode
//	if (inputCopy.length() > 3)
//	{
//		return false;
//	}
//	if (inputCopy.length() < 2)
//	{
//		return false;
//	}
//	for (int i = 0; i < keycodeSuffixes.size(); ++i)
//	{
//		if (boost::ends_with(inputCopy, boost::to_lower_copy(keycodeSuffixes[i])))
//		{
//            inputCopy = inputCopy.substr(0, inputCopy.length() - 1);
//		}
//	}
//	try
//	{
//		int value = std::stoi(inputCopy);
//		if ((value >= 1) && (value <= 12))
//		{
//			return true;
//		}
//	}
//	catch (std::exception &e)
//	{
//	}
//	return false;
//}

bool Key::isValid(const std::wstring &key)
{
	if (key == L"")
	{
		return false;
	}
	if (key == L"")
	{
		return false;
	}
	bool val = false;
	if (key[0] == L'a')
	{
		val = true;
	}
	if (key[0] == L'A')
	{
		val = true;
	}
	if (key[0] == L'b')
	{
		val = true;
	}
	if (key[0] == L'B')
	{
		val = true;
	}
	if (key[0] == L'c')
	{
		val = true;
	}
	if (key[0] == L'C')
	{
		val = true;
	}
	if (key[0] == L'd')
	{
		val = true;
	}
	if (key[0] == L'D')
	{
		val = true;
	}
	if (key[0] == L'e')
	{
		val = true;
	}
	if (key[0] == L'E')
	{
		val = true;
	}
	if (key[0] == L'f')
	{
		val = true;
	}
	if (key[0] == L'F')
	{
		val = true;
	}
	if (key[0] == L'g')
	{
		val = true;
	}
	if (key[0] == L'G')
	{
		val = true;
	}
	if (!val)
	{
		// check for key code format
		try
		{
			bool firstnumeric = std::isdigit(key[0]);
			bool secondnumeric = std::isdigit(key[1]);
			if (firstnumeric && isValidKeyCodeLetter(key[1]))
			{
				val = true;
			}
			if (firstnumeric && secondnumeric && isValidKeyCodeLetter(key[2]))
			{
				val = true;
			}
		}
		catch (std::exception &e)
		{
		}
	}
	return val;
}

bool Key::isValidKeyCodeLetter(wchar_t c)
{
	c = std::tolower(c);
	if (c == L'a')
	{
		return true;
	}
	if (c == L'b')
	{
		return true;
	}
	if (c == L'i')
	{
		return true;
	}
	if (c == L'd')
	{
		return true;
	}
	if (c == L'p')
	{
		return true;
	}
	if (c == L'm')
	{
		return true;
	}
	if (c == L'l')
	{
		return true;
	}
	if (c == L'c')
	{
		return true;
	}
	return false;
}

Key *Key::getShiftedKeyByBpmDifference(float bpm_difference)
{
	return Key::getKey(rootValue + bpm_difference / bpmDifferencePerSemitone, scaleType);
}

Key *Key::getShiftedKeyBySemitones(float semitones)
{
	return Key::getKey(rootValue + semitones, scaleType);
}

KeyRelation *Key::getClosestKeyRelation(float sourceBpm, Key *sourceKey, float targetBpm, Key *targetKey)
{
	float bpmDifference = Bpm::getBpmDifference(sourceBpm, targetBpm);
	return getClosestKeyRelation(sourceBpm, sourceKey, targetBpm, targetKey, bpmDifference);
}

KeyRelation *Key::getClosestKeyRelation(float sourceBpm, Key *sourceKey, float targetBpm, Key *targetKey, float bpmDifference)
{
	if ((sourceKey == nullptr) || (targetKey == nullptr) || !sourceKey->isValid() || !targetKey->isValid())
	{
		return KeyRelation::INVALID_RELATION;
	}
	Key *shiftedSourceKey = sourceKey->getShiftedKeyByBpmDifference(bpmDifference);
	KeyRelation *sourceRelationship = shiftedSourceKey->getKeyRelationTo(targetKey);
	return sourceRelationship;
}

float Key::getRelativeShift(int sourceScaleType, int targetScaleType)
{
	// convert source scale type to ionian:
	float sourceDifference = getShiftToIonian(sourceScaleType);
	float targetDifference = getShiftToIonian(targetScaleType);
	return (sourceDifference - targetDifference);
}

float Key::getShiftToIonian(int scaleType)
{
	float difference = 0.0f;
	if (scaleType == SCALE_AEOLIAN)
	{
		difference = 3.0f;
	}
	else if (scaleType == SCALE_LYDIAN)
	{
		difference = 7.0f;
	}
	else if (scaleType == SCALE_MIXOLYDIAN)
	{
		difference = 5.0f;
	}
	else if (scaleType == SCALE_DORIAN)
	{
		difference = 10.0f;
	}
	else if (scaleType == SCALE_PHRYGIAN)
	{
		difference = 8.0f;
	}
	else if (scaleType == SCALE_LOCRIAN)
	{
		difference = 1.0f;
	}
	return difference;
}

KeyRelation *Key::getKeyRelationTo(Key *targetKey)
{
	if ((targetKey == nullptr) || !targetKey->isValid())
	{
		return KeyRelation::INVALID_RELATION;
	}
	//if (log.isTraceEnabled()) log.trace("getKeyRelationTo(): this=" + getKeyNotationSharp(true) + ", targetKey=" + targetKey.getKeyNotationSharp(true));
	bool isRelative = false;
	float compare_rootValue = rootValue;
	float relative_shift = 0.0f;
	if (scaleType != targetKey->scaleType)
	{
		relative_shift = getRelativeShift(scaleType, targetKey->scaleType);
		compare_rootValue += relative_shift;
		if (compare_rootValue >= 12)
		{
			compare_rootValue -= 12;
		}
		isRelative = true;
	}
	if (relative_shift < 0.0)
	{
		relative_shift += 12;
	}
	// check for tonic 1st
	float actual_rootValue = compare_rootValue;
	float difference = targetKey->getRootValue() - actual_rootValue;
	while (difference >= 6.0)
	{
		difference -= 12.0;
	}
	while (difference < -6.0)
	{
		difference += 12.0;
	}
	if ((difference <= 0.5) && (difference >= -0.5))
	{
		char relationType = KeyRelation::RELATION_TONIC;
		if (isRelative)
		{
			int root_difference = shiftedNotation->getRootNote() - targetKey->getShiftedKeyNotation()->getRootNote();
			if (root_difference < 0)
			{
				root_difference += 12;
			}
			if (root_difference >= 12)
			{
				root_difference -= 12;
			}
			if (root_difference == 0)
			{
				relationType = KeyRelation::RELATION_TONIC_MODAL;
			}
			else if (root_difference == 7)
			{
				relationType = KeyRelation::RELATION_DOMINANT_MODAL;
			}
			else if (root_difference == 5)
			{
				relationType = KeyRelation::RELATION_SUBDOMINANT_MODAL;
			}
			else
			{
				relationType = KeyRelation::RELATION_RELATIVE_TONIC;
			}
		}
		return new KeyRelation(difference, relationType);
	}
	else
	{
		float minimum_difference = difference;
		// check for dominant 2nd
		actual_rootValue = compare_rootValue + 5.0f;
		if (actual_rootValue >= 12)
		{
			actual_rootValue -= 12;
		}
		difference = targetKey->getRootValue() - actual_rootValue;
		while (difference >= 6.0)
		{
			difference -= 12.0;
		}
		while (difference < -6.0)
		{
			difference += 12.0;
		}
		if ((difference <= 0.5) && (difference >= -0.5))
		{
			char relationType = KeyRelation::RELATION_DOMINANT;
			if (isRelative)
			{
				int root_difference = shiftedNotation->getRootNote() - targetKey->getShiftedKeyNotation()->getRootNote();
				if (root_difference < 0)
				{
					root_difference += 12;
				}
				if (root_difference >= 12)
				{
					root_difference -= 12;
				}
				if (root_difference == 0)
				{
					relationType = KeyRelation::RELATION_TONIC_MODAL;
					/*
				} else if (root_difference == 2) {
					if ((getScaleType() == Key.SCALE_PHRYGIAN) &&
							((targetKey.getScaleType() == Key.SCALE_AEOLIAN) || (targetKey.getScaleType() == Key.SCALE_PHRYGIAN)))
						relationType = KeyRelation.RELATION_NONE;
					else if ((getScaleType() == Key.SCALE_MIXOLYDIAN) &&
							((targetKey.getScaleType() == Key.SCALE_IONIAN) || (targetKey.getScaleType() == Key.SCALE_MIXOLYDIAN)))
						relationType = KeyRelation.RELATION_NONE;
					else
						relationType = KeyRelation.RELATION_RELATIVE_DOMINANT;
						*/
				}
				else if (root_difference == 7)
				{
					relationType = KeyRelation::RELATION_DOMINANT_MODAL;
				}
				else if (root_difference == 5)
				{
					relationType = KeyRelation::RELATION_SUBDOMINANT_MODAL;
				}
				else
				{
					relationType = KeyRelation::RELATION_RELATIVE_DOMINANT;
				}
			}
			return new KeyRelation(difference, relationType);
		}
		else
		{
			if (std::abs(difference) < std::abs(minimum_difference))
			{
				minimum_difference = difference;
			}
			// check for subdominant 3rd
			actual_rootValue = compare_rootValue + 7.0f;
			if (actual_rootValue >= 12)
			{
				actual_rootValue -= 12;
			}
			difference = targetKey->getRootValue() - actual_rootValue;
			while (difference >= 6.0)
			{
				difference -= 12.0;
			}
			while (difference < -6.0)
			{
				difference += 12.0;
			}
			if ((difference <= 0.5) && (difference >= -0.5))
			{
				char relationType = KeyRelation::RELATION_SUBDOMINANT;
				if (isRelative)
				{
					int root_difference = shiftedNotation->getRootNote() - targetKey->getShiftedKeyNotation()->getRootNote();
					if (root_difference < 0)
					{
						root_difference += 12;
					}
					if (root_difference >= 12)
					{
						root_difference -= 12;
					}
					if (root_difference == 0)
					{
						relationType = KeyRelation::RELATION_TONIC_MODAL;
					}
					else if (root_difference == 7)
					{
						relationType = KeyRelation::RELATION_DOMINANT_MODAL;
					}
					else if (root_difference == 5)
					{
						relationType = KeyRelation::RELATION_SUBDOMINANT_MODAL;
						/*
					} else if (root_difference == 10) {
						if ((targetKey.getScaleType() == Key.SCALE_PHRYGIAN) &&
								((getScaleType() == Key.SCALE_AEOLIAN) || (getScaleType() == Key.SCALE_PHRYGIAN)))
							relationType = KeyRelation.RELATION_NONE;
						else if ((targetKey.getScaleType() == Key.SCALE_MIXOLYDIAN) &&
								((getScaleType() == Key.SCALE_IONIAN) || (getScaleType() == Key.SCALE_MIXOLYDIAN)))
							relationType = KeyRelation.RELATION_NONE;
						else
							relationType = KeyRelation.RELATION_RELATIVE_SUBDOMINANT;
							*/
					}
					else
					{
						relationType = KeyRelation::RELATION_RELATIVE_SUBDOMINANT;
					}
				}
				return new KeyRelation(difference, relationType);
			}
			else
			{
				if (std::abs(difference) < std::abs(minimum_difference))
				{
					minimum_difference = difference;
				}
				// no key relation...
				return new KeyRelation(minimum_difference, KeyRelation::RELATION_NONE);
			}
		}
	}
}

bool Key::equals(Key *compare_key)
{
	return this->getKeyNotationSharp(true) == compare_key->getKeyNotationSharp(true);
}

// TODO: Commented out because it is not used anywhere yet
//int Key::hashCode()
//{
//	return this->getKeyNotationSharp(true).hashCode();
//}

int Key::compareTo(Key *compareKey)
{
	if (isValid() && compareKey->isValid())
	{
		if (rootValue < compareKey->rootValue)
		{
			return -1;
		}
		else if (rootValue > compareKey->rootValue)
		{
			return 1;
		}
		else
		{
			if (scaleType < compareKey->scaleType)
			{
				return -1;
			}
			else if (scaleType > compareKey->scaleType)
			{
				return 1;
			}
			return 0;
		}
	}
	if (isValid())
	{
		return -1;
	}
	if (compareKey->isValid())
	{
		return 1;
	}
	return 0;
}

void Key::validateRootValue()
{
	rootValue = validateRootValue(rootValue);
}

float Key::validateRootValue(float rootValue)
{
	if (rootValue == -std::numeric_limits<float>::infinity())
	{
		return rootValue;
	}
	while (rootValue >= 11.5)
	{
		rootValue -= 12;
	}
	while (rootValue < -0.5)
	{
		rootValue += 12;
	}
	return rootValue;
}

void Key::appendMode(StringBuilder *result)
{
	result->append(" ");
	result->append(getScaleTypeDescription());
}

int Key::appendShift(StringBuilder *result)
{
	int shift = static_cast<int>(shiftedNotation->getShift() * 100.0);
	if (shift > 0)
	{
		result->append(" +");
		result->append(shift);
	}
	else if (shift < 0)
	{
		result->append(" ");
		result->append(shift);
	}
	return shift;
}

Key *Key::getKey(const std::string &description)
{
	try
	{
		if ((description == "") || boost::equals(boost::trim_copy(description), ("")))
		{
			return NO_KEY;
		}

		float rootValue = Key::ROOT_UNKNOWN;
		int scaleType = Key::SCALE_UNKNOWN;

		//TODO: Ivana created a copy of description
		std::string descriptionCopy = description;

		// parse out the shift from the end:
		bool negative_shift = false;
		float shift = 0.0f;
		int shift_index = descriptionCopy.find("+");
		if (shift_index == -1)
		{
			shift_index = descriptionCopy.find("-");
			negative_shift = true;
		}
		if (shift_index >= 0)
		{
			int start_index = shift_index + 1;
			while ((start_index < descriptionCopy.length()) && !std::isdigit(descriptionCopy[start_index]))
			{
				++start_index;
			}
			int end_index = start_index + 1;
			while ((end_index < descriptionCopy.length()) && std::isdigit(descriptionCopy[end_index]))
			{
				++end_index;
			}
			try
			{
				// the shift should be in cents, 100 cents = 1 semitone
				shift = std::stof(descriptionCopy.substr(start_index, end_index - start_index)) / 100.0f;
				if (negative_shift)
				{
					shift = -shift;
				}
			}
			catch (std::exception &e)
			{
			}
			descriptionCopy = descriptionCopy.substr(0, shift_index);
		}

		descriptionCopy = boost::trim_copy(boost::to_lower_copy(descriptionCopy));

		// look for keycodes:
		int numericIndex = 0;
		while ((numericIndex < descriptionCopy.length()) && std::isdigit(descriptionCopy[numericIndex]))
		{
			++numericIndex;
		}
		if ((numericIndex > 0) && (descriptionCopy.length() > numericIndex))
		{
			int keyCodeNumber = std::stoi(descriptionCopy.substr(0, numericIndex));
			if (keyCodeNumber == 1)
			{
				rootValue = 11.0f; // G#
			}
			else if (keyCodeNumber == 2)
			{
				rootValue = 6.0f; // D#
			}
			else if (keyCodeNumber == 3)
			{
				rootValue = 1.0f; // A#
			}
			else if (keyCodeNumber == 4)
			{
				rootValue = 8.0f; // F
			}
			else if (keyCodeNumber == 5)
			{
				rootValue = 3.0f; // C
			}
			else if (keyCodeNumber == 6)
			{
				rootValue = 10.0f; // G
			}
			else if (keyCodeNumber == 7)
			{
				rootValue = 5.0f; // D
			}
			else if (keyCodeNumber == 8)
			{
				rootValue = 0.0f; // A
			}
			else if (keyCodeNumber == 9)
			{
				rootValue = 7.0f; // E
			}
			else if (keyCodeNumber == 10)
			{
				rootValue = 2.0f; // B
			}
			else if (keyCodeNumber == 11)
			{
				rootValue = 9.0f; // F#
			}
			else if (keyCodeNumber == 12)
			{
				rootValue = 4.0f; // C#
			}
			if (rootValue != ROOT_UNKNOWN)
			{
				wchar_t keyCodeScaleType = descriptionCopy[numericIndex];
				if (keyCodeScaleType == L'a')
				{
					scaleType = SCALE_AEOLIAN;
				}
				else if ((keyCodeScaleType == L'b') || (keyCodeScaleType == L'i'))
				{
					scaleType = SCALE_IONIAN;
					rootValue += 3.0;
				}
				else if (keyCodeScaleType == L'd')
				{
					scaleType = SCALE_DORIAN;
					rootValue += 5.0;
				}
				else if (keyCodeScaleType == L'l')
				{
					scaleType = SCALE_LYDIAN;
					rootValue -= 4.0;
				}
				else if (keyCodeScaleType == L'm')
				{
					scaleType = SCALE_MIXOLYDIAN;
					rootValue -= 2.0;
				}
				else if (keyCodeScaleType == L'p')
				{
					scaleType = SCALE_PHRYGIAN;
					rootValue -= 5.0;
				}
				else if (keyCodeScaleType == L'c')
				{
					scaleType = SCALE_LOCRIAN;
					rootValue += 2.0;
				}
			}
		}

		if (rootValue == ROOT_UNKNOWN)
		{
			// for for standard key notation:
			if (boost::starts_with(descriptionCopy, L"a"))
			{
				rootValue = 0.0f;
			}
			if (boost::starts_with(descriptionCopy, L"b"))
			{
				rootValue = 2.0f;
			}
			if (boost::starts_with(descriptionCopy, L"c"))
			{
				rootValue = 3.0f;
			}
			if (boost::starts_with(descriptionCopy, L"d"))
			{
				rootValue = 5.0f;
			}
			if (boost::starts_with(descriptionCopy, L"e"))
			{
				rootValue = 7.0f;
			}
			if (boost::starts_with(descriptionCopy, L"f"))
			{
				rootValue = 8.0f;
			}
			if (boost::starts_with(descriptionCopy, L"g"))
			{
				rootValue = 10.0f;
			}
			if (rootValue != ROOT_UNKNOWN)
			{
				for (int i = 1; i < descriptionCopy.length(); ++i)
				{
					if (descriptionCopy[i] == L'#')
					{
						rootValue += 1.0;
					}
					if (descriptionCopy[i] == L'b')
					{
						rootValue -= 1.0;
					}
				}
				if (rootValue < 0)
				{
					rootValue += 12;
				}
				// determine the scale type:
				if (boost::contains(descriptionCopy, "m") && !boost::contains(descriptionCopy, "major") && !boost::contains(descriptionCopy, "mix"))
				{
					scaleType = SCALE_AEOLIAN;
				}
				else
				{
					scaleType = SCALE_IONIAN;
				}
			}
		}

		if ((rootValue != ROOT_UNKNOWN) && (shift != 0.0))
		{
			rootValue += shift;
		}
		rootValue = validateRootValue(rootValue);

		// look for non-standard modes:
		if (boost::contains(descriptionCopy, "dor"))
		{
			scaleType = SCALE_DORIAN;
		}
		else if (boost::contains(descriptionCopy, "phr"))
		{
			scaleType = SCALE_PHRYGIAN;
		}
		else if (boost::contains(descriptionCopy, "mix"))
		{
			scaleType = SCALE_MIXOLYDIAN;
		}
		else if (boost::contains(descriptionCopy, "lyd"))
		{
			scaleType = SCALE_LYDIAN;
		}
		else if (boost::contains(descriptionCopy, "loc"))
		{
			scaleType = SCALE_LOCRIAN;
		}

		Key *result = checkFactory(rootValue, scaleType);
		//if (log.isTraceEnabled()) log.trace("getKey(): result=" + result);
		return result;

	}
	catch (std::exception &e)
	{
		std::cout << "Key(): error Exception";
		std::cout << e.what();

		//TODO: Log error
		//log->error(L"Key(): error Exception", e);
	}
	return NO_KEY;
}

Key *Key::getKey(float rootValue, int scaleType)
{
	Key *result = checkFactory(rootValue, scaleType);
	return result;
}

std::unordered_map<std::string, Key*> Key::keyFlyWeights;

std::string Key::calculatePrimaryKey(int shifted_key, int scaleType)
{
	std::string str = std::to_string(shifted_key) + "," + std::to_string(scaleType);
	return str;
}

Key *Key::checkFactory(float rootValue, int scaleType)
{
	std::string primaryKey = calculatePrimaryKey(static_cast<int>(rootValue * 100.0), scaleType);
	Key *result = static_cast<Key*>(keyFlyWeights[primaryKey]);
	if (result == nullptr)
	{
		//TODO: Log
//		if (log->isTraceEnabled())
//		{
//			log->trace(L"checkFactory(): no existing key found");
//		}
		result = new Key(rootValue, scaleType);
		keyFlyWeights[primaryKey] = result;
	}
	return result;
}

float Key::geRrootValue()
{
	return rootValue;
}

void Key::setRootValue(float rootValue)
{
	this->rootValue = rootValue;
}

void Key::setScaleType(int scaleType)
{
	this->scaleType = scaleType;
}

ShiftedKeyNotation *Key::getShiftedNotation()
{
	return shiftedNotation;
}

void Key::setShiftedNotation(ShiftedKeyNotation *shiftedNotation)
{
	this->shiftedNotation = shiftedNotation;
}
