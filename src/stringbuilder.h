#pragma once

//----------------------------------------------------------------------------------------
//	Copyright © 2007 - 2016 Tangible Software Solutions Inc.
//	This class can be used by anyone provided that the copyright notice remains intact.
//
//	This class is used to replace the Java StringBuilder in native C++.
//----------------------------------------------------------------------------------------
#include <string>
#include <sstream>

class StringBuilder
{
private:
	std::string privateString;

public:
	StringBuilder()
	{
	}

	StringBuilder(const std::string &initialString)
	{
		privateString = initialString;
	}

	StringBuilder(std::size_t capacity)
	{
		ensureCapacity(capacity);
	}

	wchar_t charAt(std::size_t index)
	{
		return privateString[index];
	}

	StringBuilder *append(const std::string &toAppend)
	{
		privateString += toAppend;
		return this;
	}

	template<typename T>
	StringBuilder *append(const T &toAppend)
	{
		privateString += toString(toAppend);
		return this;
	}

	StringBuilder *insert(std::size_t position, const std::string &toInsert)
	{
		privateString.insert(position, toInsert);
		return this;
	}

	template<typename T>
	StringBuilder *insert(std::size_t position, const T &toInsert)
	{
		privateString.insert(position, toString(toInsert));
		return this;
	}

	std::string toString()
	{
		return privateString;
	}

	std::size_t length()
	{
		return privateString.length();
	}

	void setLength(std::size_t newLength)
	{
		privateString.resize(newLength);
	}

	std::size_t capacity()
	{
		return privateString.capacity();
	}

	void ensureCapacity(std::size_t minimumCapacity)
	{
		privateString.reserve(minimumCapacity);
	}

	StringBuilder *remove(std::size_t start, std::size_t end)
	{
		privateString.erase(start, end - start);
		return this;
	}

	StringBuilder *replace(std::size_t start, std::size_t end, const std::string &newString)
	{
		privateString.replace(start, end - start, newString);
		return this;
	}

private:
	template<typename T>
	static std::string toString(const T &subject)
	{
		std::ostringstream ss;
		ss << subject;

		std::string t1 = ss.str();

		std::ostringstream ss1;
		ss1 << subject;

		std::string t2 = ss1.str();

		return ss.str();
	}
};