//
// Created by Ivana on 10/21/2016.
//
#include <gtest/gtest.h>
#include "../../src/audio/WavFile.h"

TEST(readWavTest, test_eq) {

    std::string filename("C:\\Users\\Ivana\\ClionProjects\\KeyDetetection\\src\\data\\F minor.wav");
    WavFile* pObjWavFile = new WavFile;

    pObjWavFile->readWavFile(filename);
    pObjWavFile->displayInformation(filename);

    int KEY_DETECTOR_ANALYZE_CHUNK_SIZE = 8192;

    int percentAudioToProcess = 100;
    int percentProcessed = 0;
    bool done = false;
    while (!done)
    {
        long long frames_read = 0;
        if (percentProcessed <= percentAudioToProcess)
        {
            frames_read = pObjWavFile->readAndWrite(KEY_DETECTOR_ANALYZE_CHUNK_SIZE);
            if ((frames_read < KEY_DETECTOR_ANALYZE_CHUNK_SIZE) && (frames_read > 0))
            {
                done = true;
            }
            if (frames_read == KEY_DETECTOR_ANALYZE_CHUNK_SIZE)
            {
                // Do something
            }
            else if (frames_read == 0)
            {
                done = true;
            }
        }
        else
        {

        }
        percentProcessed += round((frames_read / pObjWavFile->getNumFrames()) * 100);
        std::cout << "Processed frames in this loop:" << frames_read << "\n";
        std::cout << "Processed " << percentProcessed << "% of total\n";

    }
    pObjWavFile->closeWavFile();
}