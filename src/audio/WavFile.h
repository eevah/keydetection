//
// Created by Ivana on 10/1/2016.
//

#ifndef AUDIOREADER_WAV_FILE_H
#define AUDIOREADER_WAV_FILE_H

#endif //AUDIOREADER_WAV_FILE_H

/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * project_hindi
 * Copyright (C) Dilawar Singh 2010 <dilawar@ee.iitb.ac.in>
 *
 * project_hindi is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * project_hindi is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _WAV_FILE_H_
#define _WAV_FILE_H_
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include "ByteToSampleReader.h"
#include "AudioBuffer.h"
#include <fstream>

#ifndef  CONST84
#define CONST84       /* -----  not CONST84  ----- */
#endif     /* -----  not CONST84  ----- */

class WavFile
{
private:
    bool isExist;
    bool isOpen;
    bool isClose;
    char* fileName;
public:

    /* ====================  LIFECYCLE     ======================================= */
    WavFile ();                             /* constructor      */
    //WavFile ( char* fileName );   /* copy constructor */
    ~WavFile ();                            /* destructor       */

    long int getNumSamples();
    int getNumChannels();
    double getNumFrames();
    int getBitsPerSample();
    double getSampleRateHz();
    double getTotalSeconds();
    double getSecondsRead();
    double getMaxFrequency();
    AudioBuffer getAudioBuffer();
    int displayInformation(std::string fileName);
    int ifMoreDataAvailable();

    /* ====================  DATA MEMBERS  ======================================= */
protected:
    double sampleRate;
    int bitsPerSample;
    int nChannel;

    int bytesPerSample;
    int bytesPerFrame;

    int numInSamples;
    long int nSamples;
    long int nFrames;
    long totalSeconds;
    long framesProcessed;

    FILE *pFile;
    FILE *outFile;
    //fstream outputFile;

    long low_limit = 0l;
    long high_limit = 0l;

    std::vector<char> internalBuffer;
    int default_frame_buffer_size=32768;

    AudioBuffer *audioBuffer;

public:
    int readWavFile(std::string filename);
    int readAndWrite(long numFrames);
    void openFile(std::string filename);
    int writeDataToFile( char* outfile );
    int validateData();

    long readFrames(long numFrames, bool normalized);
    long skipFrames(long numFrames);
    void closeWavFile();


};

#endif // _WAV_FILE_H_