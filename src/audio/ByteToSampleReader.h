#pragma once

#include <vector>
#include "TConversionTool.h"

class ByteToSampleReader
{

public:
	ByteToSampleReader();

	static double getSampleFromBytesNormalized(std::vector<char> &buffer, int offset, int bytespersample, bool bigendian);

	static double getSampleFromBytesFactored(std::vector<char> &buffer, int offset, int bytespersample, bool bigendian, double factor);

	static double getSampleFromBytes(std::vector<char> &buffer, int offset, int bytespersample, bool bigendian);

	static void setBytesFromSample(double sample, std::vector<char> &buffer, int offset, int bytespersample, bool bigendian);

	static void setBytesFromNormalizedSample(double sample, std::vector<char> &buffer, int offset, int bytespersample, bool bigendian);
};
