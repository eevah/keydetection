#pragma once

#define _USE_MATH_DEFINES
#include <vector>
#include <math.h>

class KeyDetectionMatrix
{

	////////////
	// FIELDS //
	////////////

private:
	//TODO: Create properties file
	double startscale = 0.25; //RE3Properties::getDouble(L"key_detector_matrix_start_scale");
	int maxoctaves = 8; //RE3Properties::getInt(L"key_detector_matrix_max_octaves");
	int shifts = 1; //RE3Properties::getInt(L"key_detector_matrix_shifts");
	int maxFrequency = 0;
	std::vector<std::vector<std::vector<std::vector<double>>>> vmatrix;

	/////////////////
	// CONSTRUCTOR //
	/////////////////

public:
	KeyDetectionMatrix(int maxFrequency);

	/////////////
	// GETTERS //
	/////////////

	virtual int getMaxOctaves();

	virtual double getValue(int p, int ks, int m, int z);

	virtual int getShifts();

};

