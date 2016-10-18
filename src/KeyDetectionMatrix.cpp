//#define _USE_MATH_DEFINES
//#include <math.h>
#include "KeyDetectionMatrix.h"
#include "KeyDetector.h"
#include "RectangularVectors.h"


//TODO: Figure out why M_PI from math.h is not accessible
#define M_PI		3.14159265358979323846
KeyDetectionMatrix::KeyDetectionMatrix(int maxFrequency)
{

	this->maxFrequency = maxFrequency;
	double waveletwidth = 1.0;//RE3Properties::getDouble(L"key_detector_matrix_wavelet_width");
	int numpoints = KeyDetector::KEY_DETECTOR_ANALYZE_CHUNK_SIZE;
	double timeinterval = (static_cast<double>(KeyDetector::KEY_DETECTOR_ANALYZE_CHUNK_SIZE)) / maxFrequency;
	double coeff1 = timeinterval / numpoints;
	double coeff2 = 1.0 / waveletwidth;
	std::vector<double> basefrequency(12);
	basefrequency[0] = 55.0; // a
	basefrequency[1] = 58.27046875; // a#
	basefrequency[2] = 61.73546875; // b
	basefrequency[3] = 65.40640625; // c
	basefrequency[4] = 69.295625; // c#
	basefrequency[5] = 73.41625; // d
	basefrequency[6] = 77.78125; // d#
	basefrequency[7] = 82.406875; // e
	basefrequency[8] = 87.3071875; // f
	basefrequency[9] = 92.49875; // f#
	basefrequency[10] = 97.99875; // g
	basefrequency[11] = 103.82625; // g#
	std::vector<double> frequencyparam(12);
	for (int p = 0; p < 12; ++p)
	{
		basefrequency[p] *= startscale;
		frequencyparam[p] = basefrequency[p] * waveletwidth;
	}
//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: vmatrix = new double[maxoctaves][1][KeyDetector.KEY_DETECTOR_ANALYZE_CHUNK_SIZE][12];
	vmatrix = RectangularVectors::ReturnRectangularDoubleVector(maxoctaves, 1, KeyDetector::KEY_DETECTOR_ANALYZE_CHUNK_SIZE, 12);
	for (int s = 0; s < maxoctaves; ++s)
	{
		double st = std::pow(2, -s);
		int n = 0;
		for (double ks = 0.5; ks <= 0.5; ks += 0.3)
		{
			double k = ks * numpoints;
			for (int m = 0; m < KeyDetector::KEY_DETECTOR_ANALYZE_CHUNK_SIZE; ++m)
			{
				double x = ((static_cast<double>(m)) - k) / st * coeff1;
				double v1 = x / waveletwidth;
				for (int z = 0; z < 12; ++z)
				{
					vmatrix[s][n][m][z] = coeff2 * std::exp(-M_PI * v1 * v1) * std::cos(2.0 * M_PI * frequencyparam[z] * v1) * coeff1 / std::sqrt(st);
				}
			}
			++n;
		}
	}
}

int KeyDetectionMatrix::getMaxOctaves()
{
	return maxoctaves;
}

double KeyDetectionMatrix::getValue(int p, int ks, int m, int z)
{
	return vmatrix[p][ks][m][z];
}

int KeyDetectionMatrix::getShifts()
{
	return shifts;
}
