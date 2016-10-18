#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <stdexcept>
#include "DetectedKey.h"
#include "KeyDetectionMatrix.h"
#include "KeyProbability.h"
#include "util/Semaphore.h"
#include "util/Task.h"
#include "audio/WavFile.h"

class KeyDetector
{

private:
	//static Logger *log;

public:
	static int KEY_DETECTOR_ANALYZE_CHUNK_SIZE; // defult is 8192 (0.19 seconds), harmonics produce negligible effects on this sampling size
private:
	static double KEY_DETECTOR_TRACE_INTERVAL_SECONDS;

    std::string filename;
	WavFile *wavDecoder;
//	static Semaphore *getMatrixSem;
	static std::unordered_map<int, KeyDetectionMatrix*> matrixMap;
public:

    KeyDetector(std::string &filename);
    ~KeyDetector();

	static KeyDetectionMatrix *getMatrix(int maxFrequency);

	DetectedKey *detectKey(); //TODO: This was static
	static DetectedKey *detectKey(const std::wstring &filename, Task *task);

private:
	void analyzeSegment(std::vector<double> &norm_keycount, KeyProbability *segment_probabilities, std::vector<double> &cwt); //TODO: this was static

	static void countKeyProbabilities(std::vector<double> wavedata, long long icount, long long amt, double time, int maxfreq, KeyProbability *segment_probabilities, std::vector<double> &norm_keycount, std::vector<double> &cwt);

};

