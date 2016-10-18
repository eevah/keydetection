#pragma once

#include <string>
#include <limits>

class KeyRelation //: public Comparable<KeyRelation*>, public Serializable
{

private:
	static const long long serialVersionUID = 0LL;

	///////////////
	// CONSTANTS //
	///////////////

public:
	static char RELATION_TONIC;
	static char RELATION_TONIC_MODAL;
	static char RELATION_DOMINANT;
	static char RELATION_DOMINANT_MODAL;
	static char RELATION_SUBDOMINANT;
	static char RELATION_SUBDOMINANT_MODAL;
	static char RELATION_RELATIVE_TONIC;
	static char RELATION_RELATIVE_DOMINANT;
	static char RELATION_RELATIVE_SUBDOMINANT;
	static char RELATION_NONE;

	static KeyRelation *INVALID_RELATION;

	////////////
	// FIELDS //
	////////////

private:
	float difference = -std::numeric_limits<float>::infinity();
	char relationship = RELATION_NONE;

	//////////////////
	// CONSTRUCTORS //
	//////////////////

public:
	KeyRelation();
	KeyRelation(float difference, char relationship);

	/////////////
	// GETTERS //
	/////////////

	virtual float getDifference();
	virtual char getRelationship();

	virtual bool hasDifference();

	virtual bool isCompatible();
	virtual bool isCompatible(bool strict);
	static bool isCompatible(char relationship, bool strict);

	virtual bool isValid();

	/////////////
	// SETTERS //
	/////////////

	virtual void setDifference(float difference);
	virtual void setRelationship(char relationship);

	/////////////
	// METHODS //
	/////////////

	virtual int compareTo(KeyRelation *oRelation);

	virtual std::wstring toString();
	static std::wstring toString(char relationship);

};
