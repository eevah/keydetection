#pragma once

#include <string>
#include <unordered_map>


/// <summary>
/// Utilizes the fly-weight pattern due to finite range...  this class must remain immutable!
/// </summary>
class Accuracy //: public Serializable, public Comparable<Accuracy*>
{

private:
	static const long long serialVersionUID = 0LL;
	////////////
	// FIELDS //
	////////////

	char accuracy = 0; // 0 to 100 (representing a %percentage%)

	//////////////////
	// CONSTRUCTORS //
	//////////////////

	// for serialization
public:
	Accuracy();

	/// <param name="accuracy"> value between 0 and 100 </param>
private:
	Accuracy(char accuracy);

	/////////////
	// GETTERS //
	/////////////

public:
	virtual char getAccuracy();

	virtual float getAccuracyNormalized();

	/////////////
	// SETTERS //
	/////////////

	// for serialization
	virtual void setAccuracy(char accuracy);

	/////////////
	// METHODS //
	/////////////

	virtual std::wstring toString();

	virtual int compareTo(Accuracy *a);

//	virtual bool equals(void *o);

	virtual int hashCode();

	////////////////////////
	// FLY WEIGHT PATTERN //
	////////////////////////

	static Accuracy *getAccuracy(char accuracyValue);
	static Accuracy *getAccuracy(int accuracyValue);

private:
	static std::unordered_map<std::wstring, Accuracy*> accuracyFlyWeights;

	static std::wstring calculatePrimaryKey(char accuracyValue);

	static Accuracy *checkFactory(char accuracyValue);

};

