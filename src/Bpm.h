#pragma once

#include <string>
#include <cmath>
#include <boost/optional.hpp>




/// <summary>
/// BPM = beats per minute
/// This class includes helper methods for computing the difference between BPM values.
/// </summary>
class Bpm //: public Comparable<Bpm*>, public Serializable
{

private:
	static const long long serialVersionUID = 0LL;

public:
	static Bpm *NO_BPM;

	////////////
	// FIELDS //
	////////////

	float bpmValue = 0;

	/////////////////
	// CONSTRUCTOR //
	/////////////////

	// for serialization
	Bpm();

	Bpm(float bpmValue);
	Bpm(double bpmValue);
	Bpm(boost::optional<float> bpmValue);

	/////////////
	// GETTERS //
	/////////////

	virtual float getBpmValue();

	virtual boost::optional<float> getDifference(Bpm *value);
	virtual boost::optional<float> getDifference(float value);

	virtual bool isValid();

	/// <summary>
	/// This method will determine the percentage difference between two BPM values.
	/// Since some BPMs are equivalent (i.e. 50bpm == 100bpm), the space covering
	/// all the powers of 2 must be searched for the lowest possible difference.
	///
	/// For example:
	///   where sourceBpm=50 and targetBpm=105, the BPM difference is +5(%)
	/// </summary>
	static boost::optional<double> getBpmDifference(double sourceBpm, double targetBpm);
	static float getBpmDifference(float sourceBpm, float targetBpm);

	/////////////
	// SETTERS //
	/////////////

	virtual void setBpmValue(float bpmValue);

	/////////////
	// METHODS //
	/////////////

	virtual float getSimilarityWith(Bpm *otherBpm);
	static float getSimilarity(float bpmValue1, float bpmValue2);

	virtual std::wstring toString();

	virtual std::wstring toString(bool rounded);

	virtual int compareTo(Bpm *b);

	//virtual bool equals(void *o);

	virtual int hashCode();

};
