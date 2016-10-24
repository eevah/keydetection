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

#include "WavFile.h"
#include "WavDefinition.h"
#include <string.h>
#include <stdlib.h>

using namespace std;

//TODO: Problem with using EXIT_SUCCESS and EXIT_FAILURE from cstdlib
#define THIS_EXIT_SUCCESS    1
#define THIS_EXIT_FAILURE    0



WavFile::WavFile() {
}

WavFile::~WavFile()
{
}


long int WavFile::getNumSamples()
{
    return nSamples;
}

int WavFile::getNumChannels()
{
    return nChannel;
}

double WavFile::getNumFrames()
{
    return nFrames;
}

int WavFile::getBitsPerSample()
{
    return bitsPerSample;
}

double WavFile::getSampleRateHz()
{
    return sampleRate;
}

double WavFile::getMaxFrequency() {
    return sampleRate / 2;
}

double WavFile::getTotalSeconds() {
    return totalSeconds;
}

double WavFile::getSecondsRead() {
    return ((double)framesProcessed) / sampleRate;
}

AudioBuffer WavFile::getAudioBuffer() {
    return *audioBuffer;
}

void WavFile::openFile(std::string fileName) {
    pFile = fopen(fileName.c_str(), "rb");
    if(pFile == NULL)
    {
        std::cerr << "Can't open wav file.\n";
        //TODO: Not good to just exit here. Throw an exception
        exit(-1);
    }
}

int WavFile::readWavFile(string filename)
{
    int i;
    unsigned int stat;
    char outBuffer[80];

    WAV_HDR* pWavHeader;
    CHUNK_HDR* pChunkHeader;

    short int* pU;
    unsigned char* pC;
    int sFlag;
    long int rMore;

    numInSamples = 0;
    nSamples = 0;
    nFrames = 0;
    framesProcessed = 0;

    pWavHeader = new WAV_HDR;
    pChunkHeader = new CHUNK_HDR;

    openFile(filename);

    /* read riff/wav header */
    stat = fread((void*) pWavHeader, sizeof(WAV_HDR), (size_t)1, pFile);
    if(stat != 1)
    {
        printf("Header missing. May be format is not OK!\n"); // This is tested.
        exit(-1);
    }

    /* check format of header */
    for(i = 0; i < 4; i++)
    {
        outBuffer[i] = pWavHeader->rID[i];
    }
    outBuffer[4] = 0;

    //If file starts with RIFF, then it is little endian
    //http://stackoverflow.com/questions/1111539/is-the-endianness-of-format-params-guaranteed-in-riff-wav-files
    if(strcmp(outBuffer, "RIFF") != 0) // tested.
    {
        printf("\nBad RIFF format. I am not cool enough to support everything");
        exit(-1);
    }

    for(i = 0; i < 4; i++)
        outBuffer[i] = pWavHeader->wID[i];
    outBuffer[4] = 0;


    if(strcmp(outBuffer, "WAVE") != 0) // tested.
    {
        printf( "\n%s" , outBuffer );
        printf("\nBad WAVE format \n");
        exit(-1);
    }

    for(i = 0; i < 4; i++)
    {
        outBuffer[i] = pWavHeader->fId[i];
    }
    outBuffer[4] = '\0';

    if(strcmp(outBuffer, "fmt ") != 0) // not with "fmt" since 4th pos is blank
    {
        printf("\nBad fmt format");
        exit(-1);
    }

    if(pWavHeader->wFormatTag != 1)
    {
        printf("\n Bad wav wFormatTag");
        exit(-1);
    }

    if( (pWavHeader->numBitsPerSample != 16) && (pWavHeader->numBitsPerSample != 8))
    {
        printf("\nBad wav bits per sample");
        exit(-1);
    }

    /*
     * Skip over any remaining portion of wav header.
     */
    rMore = pWavHeader->pcmHeaderLength - (sizeof(WAV_HDR) - 20);
    if( 0 != fseek(pFile, rMore, SEEK_CUR))
    {
        printf("Can't seek.");
        exit(-1);
    }

    /*
     * read chunk untill a data chunk is found.
     */
    sFlag = 1;
    while(sFlag != 0)
    {
        // check attempts.
        if(sFlag > 10)
        {
            printf("\nToo many chunks");
            exit(-1);
        }

        // read chunk header
        stat = fread((void*)pChunkHeader, sizeof(CHUNK_HDR), (size_t)1, pFile);
        if( 1 != stat)
        {
            printf("\n I just can't read data. Sorry!");
            exit(-1);
        }

        // check chunk type.
        for(i =0; i < 4; i++)
        {
            outBuffer[i] = pChunkHeader->dId[i];
        }
        outBuffer[4] = 0;
        if(strcmp(outBuffer, "data") == 0)
        {
            break;
        }

        // skip over chunk.
        sFlag++;
        stat = fseek(pFile, pChunkHeader->dLen, SEEK_CUR);
        if(stat != 0)
        {
            printf("Can't seek.");
            exit(-1);
        }

    }

    // Number of samples equals length of data in bytes divided by number of bytes per sample
    nSamples = pChunkHeader->dLen / (pWavHeader->numBitsPerSample / 8);


    sampleRate = (double) (pWavHeader->nSamplesPerSec);
    bitsPerSample = pWavHeader->numBitsPerSample;
    nChannel = pWavHeader->numChannels;
    nFrames = nSamples / nChannel;

    bytesPerSample = bitsPerSample / 8;
    bytesPerFrame = nChannel * bytesPerSample; // TODO: double check


    totalSeconds = nSamples / nChannel / sampleRate;

    audioBuffer = new AudioBuffer(default_frame_buffer_size, nChannel);
    internalBuffer.resize(default_frame_buffer_size * bytesPerFrame);


    // ----------------------//
    // Write header to new file
    outFile = fopen((filename + "-modified.wav").c_str(), "wb");
   // outputFile.open(filename + "-modified1.wav", ios::out|ios::binary);

  //  outputFile.write((char*)&pWavHeader, sizeof(WAV_HDR));/// write the header to output file
    fwrite((void*)pWavHeader, sizeof(WAV_HDR), (size_t)1, outFile);
    //----------------------//
   // outputFile.write((char*)&pChunkHeader, sizeof(CHUNK_HDR));/// write the header to output file
    fwrite((void*)pChunkHeader, sizeof(CHUNK_HDR), (size_t)1, outFile);


    /* reset and delete */
    numInSamples = 0;

    if(pWavHeader != NULL) delete pWavHeader;
    if(pChunkHeader != NULL) delete pChunkHeader;


    //TODO: Sort out where to close the file!
    //Deconstructor may be closing it automatically
    //fclose(pFile);

    if (validateData() == 1)
        return THIS_EXIT_SUCCESS;
    else
        return THIS_EXIT_FAILURE;
}

int WavFile::displayInformation(std::string filename)
{
    printf("\n-----------------------------------------------------");
    printf("\nLoaded wav file : %s", filename);
    printf("\nSample rate: %1.01f (Hz)", sampleRate);
    printf("\nNumber of samples = %ld", nSamples);
    printf("\nBits per sample = %d", bitsPerSample);
    printf("\nNumber of channels = %d", nChannel);
    printf("\nNumber of frames = %ld", nSamples / nChannel);
    printf("\nDuration = %d", totalSeconds);
    printf("\n----------------------------------------------------\n");

    return THIS_EXIT_SUCCESS;
}

void WavFile::closeWavFile() {
    fclose(pFile);
   // outputFile.close();
}

int WavFile::validateData() {
    bool sizeIsCorrect = true;
    // make sure that the bytes-per-sample is completely divisible by num.of channels
    long bytes_in_each_channel = bytesPerSample / nChannel;
    if ((bytes_in_each_channel  * nChannel) != bytesPerSample) {
        printf("Error: %ld x %ud <> %ld\n", bytes_in_each_channel, nChannel, bytesPerSample);
        sizeIsCorrect = false;
    }

    if (sizeIsCorrect) {
        // the valid amplitude range for values based on the bits per sample
        switch (bitsPerSample) {
            case 8:
                low_limit = -128;
                high_limit = 127;
                break;
            case 16:
                low_limit = -32768;
                high_limit = 32767;
                break;
            case 32:
                low_limit = -2147483648;
                high_limit = 2147483647;
                break;
        }
        return 1;
    }
    else {
        return 0;
    }
}

int WavFile::readAndWrite(long numFrames) {

    long x = bytesPerFrame * numFrames;
    long y = internalBuffer.size();
    int length = std::min(x, y);
    int bytes_read = 0;
    char* chunk = new char[length];
    int this_bytes_read = fread(chunk, sizeof(char), length, pFile);

    while ((this_bytes_read != 0) && (bytes_read < length)) {

        for (int i = 0; i < this_bytes_read; i++) {
            internalBuffer[bytes_read] = chunk[i];

            //Writing every second sample (in each channel)
            //if (i % 4 == 0 || i % 4 == 1) {
                fwrite((char*)&chunk[i], sizeof(char), (size_t)1, outFile);
            //}
            bytes_read++;
        }
        delete[] chunk;
        chunk = new char[length - bytes_read];
        this_bytes_read = fread(chunk, sizeof(char), length - bytes_read, pFile);//decodedInputStream.read(internal_buffer, bytes_read, length - bytes_read);
    }
    return bytes_read / bytesPerFrame;

}

long WavFile::readFrames(long numFrames, bool normalized) {

    int frames_read = 0;
    const bool isBigEndian = false; // We are only reading files that start with RIFF for now, and they are little endian
    try {

        long x = bytesPerFrame * numFrames;
        long y = internalBuffer.size();
        int length = std::min(x, y);
        int bytes_read = 0;
        char* chunk = new char[length];
        int this_bytes_read = fread(chunk, sizeof(char), length, pFile);

        //TODO: This copying is taking too much time! Fix it. May not be copying but the printing to console that was there.
        //TODO: Make sure that this loop is doing what's expected
        while ((this_bytes_read != 0) && (bytes_read < length)) {

            for (int i = 0; i < this_bytes_read; i++) {
                internalBuffer[bytes_read] = chunk[i];
                bytes_read++;
            }
            delete[] chunk;
            chunk = new char[length - bytes_read];
            this_bytes_read = fread(chunk, sizeof(char), length - bytes_read, pFile);//decodedInputStream.read(internal_buffer, bytes_read, length - bytes_read);
        }

        // TODO: Next for testing
        delete[] chunk;
        int count = 0;
        while (count < bytes_read) {
            for (int channel = 0; channel < nChannel; ++channel) {
                double sample = normalized ?
                                ByteToSampleReader::getSampleFromBytesNormalized(internalBuffer, count, bytesPerSample, isBigEndian)
                                           : ByteToSampleReader::getSampleFromBytes(internalBuffer, count, bytesPerSample, isBigEndian);
                audioBuffer->setSampleValue(frames_read, channel, sample);
                count += bytesPerSample;
            }
            ++frames_read;
        }
    } catch(exception e) {
        std::cout << e.what() << '\n';
    }

    framesProcessed += frames_read;
    return frames_read;
}

long WavFile::skipFrames(long numFrames) {
    long frames_skipped = 0;
    try {

        long x = bytesPerFrame * numFrames;
        long y = internalBuffer.size();
        int length = std::min(x, y);
        char* chunk = new char[length];
        long bytes_skipped = 0;
        long this_bytes_skipped = 0;

        this_bytes_skipped = fread(chunk, sizeof(char), length, pFile);

        //TODO: This copying is taking too much time! Fix it.
        //TODO: changed (this_bytes_skipped != -1) to (this_bytes_skipped != 0)
        while ((this_bytes_skipped != 0) && (bytes_skipped < length)) {

            for (int i = 0; i < this_bytes_skipped; i++) {
                std::cout << "bytes_skipped = " << bytes_skipped << '\n';
                std::cout << "chunk[i] = " << chunk[i] << '\n';
                internalBuffer[bytes_skipped] = chunk[i];
                bytes_skipped++;
            }

            delete[] chunk;
            chunk = new char[length - bytes_skipped];
            this_bytes_skipped = fread(chunk, sizeof(char), length - bytes_skipped, pFile);//decodedInputStream.read(internal_buffer, bytes_read, length - bytes_read);
        }

        frames_skipped = bytes_skipped / bytesPerFrame;



    } catch (exception e) {
        std::cout << "readSamples(): error Exception " << e.what() << "\n";
//        log.error("readSamples(): error Exception", e);
    }

    framesProcessed += frames_skipped;
    return frames_skipped;
}