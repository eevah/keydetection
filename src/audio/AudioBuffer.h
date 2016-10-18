//
// Created by Ivana on 10/5/2016.
//

#include <vector>

#ifndef KEYDETETECTION_AUDIOBUFFER_H
#define KEYDETETECTION_AUDIOBUFFER_H

using namespace std;

class AudioBuffer {

private:
    vector<vector<double>> samples;

        /////////////////
        // CONSTRUCTOR //
        /////////////////

public:
    AudioBuffer(int size, int num_channels);

    int getNumChannels();
    vector<double> getSampleData(int channel);
    vector<vector<double>> getSampleData();
    int getSize();

    void setSampleValue(int index, int channel, double value);
};


#endif //KEYDETETECTION_AUDIOBUFFER_H
