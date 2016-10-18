#pragma once

#include <string>
#include <unordered_map>
#include <limits>
#include "../stringbuilder.h"

/// <summary>
/// A key code is a notation based on the circle of fifths, such that harmonically compatible keys are adjacent when
/// sorted numerically.  The letter for the key code represents the scale type.
/// </summary>
class KeyCode //: public Comparable<KeyCode*>, public Serializable
{

private:
	static const long long serialVersionUID = 0LL;

public:
	static KeyCode *NO_KEYCODE;

	////////////
	// FIELDS //
	////////////

private:
	__int8 keyValue = std::numeric_limits<int>::min();
	char scaleType = std::numeric_limits<char>::min();
	__int8 shift = std::numeric_limits<char>::min();
	std::string cachedToString;
	std::string cachedToStringWithDetails;

	//////////////////
	// CONSTRUCTORS //
	//////////////////

	// for serialization only
public:
	KeyCode();

private:
	KeyCode(__int8 keyValue, char scaleType, __int8 shift);

	/////////////
	// GETTERS //
	/////////////

public:
	virtual __int8 getKeyValue();
	virtual __int8 getShift();
	virtual char getScaleType();

	virtual bool isValid();

	virtual bool isMinor();

	/////////////
	// METHODS //
	/////////////

	virtual std::string toString();
	virtual std::string toString(bool showDetails);

	virtual std::string toFileFriendlyString();

	virtual void invalidate();

	virtual int compareTo(KeyCode *oKeyCode);

private:
	std::string calculateKeyCodeString(bool showDetails);

	////////////////////////
	// FLY WEIGHT PATTERN //
	////////////////////////

public:
	static KeyCode *getKeyCode(__int8 keyValue, char scaleType, __int8 shift);

	static void invalidateCache();

private:
	static std::unordered_map<std::string, KeyCode*> keyCodeFlyWeights;

	static std::string calculatePrimaryKey(__int8 keyValue, char scaleType, __int8 shift);

	///////////////////////
	// FOR SERIALIZATION //
	///////////////////////

public:
	virtual std::string getCachedToString();

	virtual void setCachedToString(const std::string &cachedToString);

	virtual std::string getCachedToStringWithDetails();

	virtual void setCachedToStringWithDetails(const std::string &cachedToStringWithDetails);

	virtual void setKeyValue(__int8 keyValue);

	virtual void setScaleType(char scaleType);

	virtual void setShift(__int8 shift);
};
