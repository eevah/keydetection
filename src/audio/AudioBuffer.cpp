//
// Created by Ivana on 10/5/2016.
//

#include "AudioBuffer.h"

vector<vector<double>> samples;

AudioBuffer::AudioBuffer(int size, int num_channels) {
    samples.resize(num_channels, vector<double>(size));
}

int AudioBuffer::getNumChannels() {
    return samples.size();
}

vector<double> AudioBuffer::getSampleData(int channel) {
    return samples[channel];
}

vector<vector<double>> AudioBuffer::getSampleData() {
    return samples;
}

int AudioBuffer::getSize() {
    return samples[0].size();
}

void AudioBuffer::setSampleValue(int index, int channel, double value) {
    samples[channel][index] = value;
}