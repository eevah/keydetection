#pragma once

#include <string>
#include <cmath>



class ShiftedKeyNotation //: public Serializable
{

private:
	static const long long serialVersionUID = 0LL;

	////////////
	// FIELDS //
	////////////

	char rootNote = 0;
	float shift = 0;

	//////////////////
	// CONSTRUCTORS //
	//////////////////

public:
	ShiftedKeyNotation();

	ShiftedKeyNotation(float root_value);

	ShiftedKeyNotation(char rootNote, float shift);

	/////////////
	// GETTERS //
	/////////////

	virtual char getRootNote();
	virtual float getShift();
	virtual int getShiftInCents();

	virtual char getRoot_note();

	/////////////
	// SETTERS //
	/////////////

	virtual void setRootNote(char rootNote);
	virtual void setShift(float shift);

};
