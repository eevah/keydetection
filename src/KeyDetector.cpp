#include <iostream>
#include <chrono>
#include "KeyDetector.h"
#include "KeyDetectionMatrix.h"
#include "DetectedKey.h"
#include "KeyProbability.h"
using namespace std::chrono;
//						using org::apache::log4j::Logger;
//						using com::mixshare::rapid_evolution::RE3Properties;
//						using com::mixshare::rapid_evolution::RapidEvolution3;
//						using com::mixshare::rapid_evolution::audio::AudioBuffer;
//						using com::mixshare::rapid_evolution::audio::codecs::AudioDecoder;
//						using com::mixshare::rapid_evolution::audio::codecs::AudioDecoderFactory;
//						using com::mixshare::rapid_evolution::audio::codecs::DecoderException;
//						using com::mixshare::rapid_evolution::music::key::Key;
//						using com::mixshare::rapid_evolution::ui::RapidEvolution3UI;
//						using com::mixshare::rapid_evolution::util::io::FileLockManager;
//						using com::mixshare::rapid_evolution::util::timing::Semaphore;
//						using com::mixshare::rapid_evolution::workflow::Task;
//org::apache::log4j::Logger *KeyDetector::log = org::apache::log4j::Logger::getLogger(KeyDetector::typeid);


// TODO: WRITE PROPERITES INTO A SEPARATE FILE
int KeyDetector::KEY_DETECTOR_ANALYZE_CHUNK_SIZE = 8192; // com::mixshare::rapid_evolution::RE3Properties::getInt(L"key_detector_analyze_chunk_size");
double KeyDetector::KEY_DETECTOR_TRACE_INTERVAL_SECONDS = 10; //com::mixshare::rapid_evolution::RE3Properties::getDouble(L"key_detector_trace_interval_seconds");

//TODO: IMPLEMENT SEMAPHORE. THE FOLLOWING LINE SHOULDN'T BE WORKING
//com::mixshare::rapid_evolution::util::timing::Semaphore *KeyDetector::getMatrixSem = new com::mixshare::rapid_evolution::util::timing::Semaphore(1);
std::unordered_map<int, KeyDetectionMatrix*> KeyDetector::matrixMap;

KeyDetector::KeyDetector(std::string &filename) {
    this->filename = filename;
    this->wavDecoder = new WavFile();
}

KeyDetector::~KeyDetector() {
    if (this->wavDecoder != nullptr)
    {
        this->wavDecoder->closeWavFile();
    }
    delete wavDecoder; //TODO: this might not be necessary. Maybe destructor deletes it automatically?
    //TODO: Write code for file lock
    //FileLockManager::endFileRead(filename);
}


KeyDetectionMatrix *KeyDetector::getMatrix(int maxFrequency)
{
    //TODO: FIX THE SEMAPHORE (Implement it in C++)
    KeyDetectionMatrix *result = nullptr;
    try
    {
//        getMatrixSem->acquire();
        result = matrixMap[maxFrequency];
        if (result == nullptr)
        {
            result = new KeyDetectionMatrix(maxFrequency);
            matrixMap[maxFrequency] = result;
        }
    }
    catch (std::exception &e)
    {
    }
    //JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
    // TODO: acquire throws the exception. Replace semephore and make sure to handle exception appropriatelly for C++
//    finally
//    {
//        getMatrixSem->release();
//    }
    return result;
}


DetectedKey *KeyDetector::detectKey()
{
    //TODO: Use proper logging
//    std::string fileStr( filename.begin(), filename.end() );
//    std::cout << "detectKey(): detecting key from file=" << fileStr;
//    if (log->isDebugEnabled())
//    {
//        log->debug(std::wstring(L"detectKey(): detecting key from file=") + filename);
//    }

    DetectedKey *result = new DetectedKey();
//    AudioDecoder *decoder = nullptr;
   // WavFile *wavDecoder = new WavFile();
    KeyProbability *segment_probabilities = nullptr;
    std::vector<double> norm_keycount(12);
    std::vector<double> cwt(12);
    double report_time = KEY_DETECTOR_TRACE_INTERVAL_SECONDS;
    //TODO: Make sure this is a correct way to get current time in milliseconds
    long long startTime = duration_cast< milliseconds >(system_clock::now().time_since_epoch()).count();//System::currentTimeMillis();

    try
    {
        //TODO: Write code for file lock
        //FileLockManager::startFileRead(filename);

        int fileIsOpen = wavDecoder->openWavFile(filename);
        if (fileIsOpen == 1)
        {
            double segmentTime = KEY_DETECTOR_ANALYZE_CHUNK_SIZE / wavDecoder->getSampleRateHz() * 1000;
            segment_probabilities = new KeyProbability(segmentTime);
            int percentAudioToProcess = 100; //RE3Properties::getInt(L"percent_audio_samples_to_process"); // 0 to 100
            int percentCount = 0;
            bool done = false;
            bool half_way = false;
            bool aborted = false;
            while (!done)
            {
                if (percentCount <= percentAudioToProcess)
                {
                    long long frames_read = wavDecoder->readFrames(KEY_DETECTOR_ANALYZE_CHUNK_SIZE, false); //decoder->readFrames(KEY_DETECTOR_ANALYZE_CHUNK_SIZE);
                    if ((frames_read < KEY_DETECTOR_ANALYZE_CHUNK_SIZE) && (frames_read > 0))
                    {
                        //TODO: Use proper logging
                        std::cout << "detectKeyFromFile(): insufficient audio found, looping audio segment to meet minimum length required";
//                        }
//                        if (log->isDebugEnabled())
//                        {
//                            log->debug(L"detectKeyFromFile(): insufficient audio found, looping audio segment to meet minimum length required");
//                        }
                        int i = 0;
                        for (long long j = frames_read; j < KEY_DETECTOR_ANALYZE_CHUNK_SIZE; ++j)
                        {
                            for (int c = 0; c < wavDecoder->getNumChannels(); ++c)
                            {
                                double copySample = wavDecoder->getAudioBuffer().getSampleData()[c][i];
                                wavDecoder->getAudioBuffer().setSampleValue(static_cast<int>(j), c, copySample);
                            }
                            ++i;
                        }
                        wavDecoder->skipFrames(KEY_DETECTOR_ANALYZE_CHUNK_SIZE - frames_read);
                        frames_read = KEY_DETECTOR_ANALYZE_CHUNK_SIZE;
                        done = true;
                    }
                    if (frames_read == KEY_DETECTOR_ANALYZE_CHUNK_SIZE)
                    {


                        AudioBuffer test = wavDecoder->getAudioBuffer();

                        analyzeSegment(norm_keycount, segment_probabilities, cwt);

                        //AudioBuffer audiobuffer, WavFile *decoder, std::vector<double> &norm_keycount, KeyProbability *segment_probabilities, std::vector<double> &cwt)

                        double audiotime = wavDecoder->getSecondsRead();
                        DetectedKey *start_section = nullptr;
                        if (half_way)
                        {
                            start_section = segment_probabilities->getDetectedKey();
                            if (start_section != nullptr)
                            {
                                if (false) //RE3Properties::getBoolean(L"detect_start_and_end_keys"))
                                {
                                    result->setEndKey(start_section->getStartKey());
                                }
                                else
                                {
                                    result->setStartKey(start_section->getStartKey());
                                }
                                result->setAccuracy(start_section->getAccuracyValue());
                            }
                        }
                        else
                        {
                            start_section = segment_probabilities->getDetectedKey((!half_way && (audiotime * 2 > wavDecoder->getTotalSeconds())));
                            if (start_section != nullptr)
                            {
                                Key *k = start_section->getStartKey();
                                double ac = start_section->getAccuracyValue();

                                DetectedKey *test = new DetectedKey();
                                test->setAccuracy(ac);
                                result->setAccuracy(ac);

                                result->setStartKey(k);

                                result->setStartKey(start_section->getStartKey());

                            }
                        }
                        if (!half_way && (audiotime * 2 > wavDecoder->getTotalSeconds())) {
                            half_way = true;
                            segment_probabilities = new KeyProbability(segmentTime);
                        }
                        if (audiotime > report_time)
                        {
                            //TODO: Log properly
                            std::cout << "detectKeyFromFile(): time=" << audiotime << "s, key=" <<  start_section->getStartKey();
//                            if (log->isTraceEnabled())
//                            {
//                                log->trace(std::wstring(L"detectKeyFromFile(): time=") + audiotime + std::wstring(L"s, key=") + start_section->getStartKey());
//                            }
                            report_time += KEY_DETECTOR_TRACE_INTERVAL_SECONDS;
                        }
                    }
                    else if (frames_read == 0)
                    {
                        done = true;
                    }
                }
                else
                {
                    long long frames_skipped = wavDecoder->skipFrames(KEY_DETECTOR_ANALYZE_CHUNK_SIZE);
                    if (frames_skipped == 0)
                    {
                        done = true;
                    }
                }
                ++percentCount;
                if (percentCount > 100)
                {
                    percentCount = 0;
                }

                if (percentCount == 36) {
                    std::cout << "pause\n";
                }



            }
            if (!aborted)
            {
                segment_probabilities->finish();
                if (!segment_probabilities->hasNoData())
                {

//                    DetectedKey end_key = segment_probabilities.getDetectedKey();
//                    Key key = segment_probabilities.getDetectedKey(true).getStartKey();
//                    if (result.getStartKey().equals(""))
//                        result.setStartKey(key);
//                    else
//                        result.setEndKey(key);

                    //TODO: Above is Java code. Make sure that having NULL in c++ code works!
                    DetectedKey *end_key = segment_probabilities->getDetectedKey();
                    Key *key = segment_probabilities->getDetectedKey(true)->getStartKey();
                    if (result->getStartKey() == NULL)
                    {
                        result->setStartKey(key);
                    }
                    else
                    {
                        result->setEndKey(key);
                    }
                    if (result->getAccuracyValue() != 0.0)
                    {
                        result->setAccuracy(std::min(end_key->getAccuracyValue(), result->getAccuracyValue()));
                    }
                    else
                    {
                        result->setAccuracy(end_key->getAccuracyValue());
                    }
                    if (!false) //!RE3Properties::getBoolean(L"detect_start_and_end_keys"))
                    { // use single key
                        result->setStartKey(key);
                        result->setEndKey(Key::NO_KEY);
                        result->setAccuracy(result->getAccuracyValue());
                    }
                }
                else
                {
                    result->setStartKey(Key::NO_KEY);
                    result->setAccuracy(0.01);
                }
//                Date endtime = Date();
                long long endTime = duration_cast< milliseconds >(system_clock::now().time_since_epoch()).count();
                long long seconds = endTime - startTime; //(endtime.getTime() - startTime) / 1000;
                //TODO: Log properly
                std::cout << "detectKey(): detected key=" << result << ", in " << seconds << " seconds";
//                log->debug(std::wstring(L"detectKey(): detected key=") + result + std::wstring(L", in ") + seconds + std::wstring(L" seconds"));
            }
            else
            {
                result = new DetectedKey();
            }
        }
        else
        {
            //TODO: Log properly
            std::cout << "detectKey(): no decoder available for provided file\n";
//            if (log->isDebugEnabled())
//            {
//                log->debug(std::wstring(L"detectKey(): no decoder available for file=") + filename);
//            }
        }
    }
    catch (exception e) {
        std::cout << e.what() << "\n";
    }
//    catch (java::lang::OutOfMemoryError e)
//    {
//        //TODO: Log properly
//        std::cout << "detectKey(): out of memory error detecting key from file=" << fileStr;
////        log->error(std::wstring(L"detectKey(): out of memory error detecting key from file=") + filename);
//        if (RapidEvolution3UI::instance != nullptr)
//        {
//            RapidEvolution3UI::instance::notifyOutOfMemory(std::wstring(L"detecting the key from file=") + filename);
//        }
//    }
//    catch (DecoderException de)
//    {
//        log->error(L"detectKey(): decoder exception");
//    }
//    catch (std::exception &e)
//    {
//        log->error(std::wstring(L"detectKey(): error detecting key from file=") + filename, e);
//    }

    //delete wavDecoder;
    return result;
}

void KeyDetector::analyzeSegment(std::vector<double> &norm_keycount, KeyProbability *segment_probabilities, std::vector<double> &cwt)
{
    try
    {
        AudioBuffer audiobuffer = wavDecoder->getAudioBuffer();
        int num_channels_to_use = 1;
        int maxfrequency = static_cast<int>(wavDecoder->getMaxFrequency());
        double timeinterval = static_cast<double>(KEY_DETECTOR_ANALYZE_CHUNK_SIZE) / wavDecoder->getSampleRateHz();
        for (int channel = 0; channel < std::min(num_channels_to_use, audiobuffer.getNumChannels()); ++channel)
        {
            for (int i = 0; i < norm_keycount.size(); ++i)
            {
                norm_keycount[i] = 0.0;
            }
            //(std::vector<double> wavedata, long long icount, long long amt, double time, int maxfreq, KeyProbability *segment_probabilities, std::vector<double> &norm_keycount, std::vector<double> &cwt)
            std::vector<double> wavedata = audiobuffer.getSampleData(channel);
            countKeyProbabilities(wavedata, 0, KEY_DETECTOR_ANALYZE_CHUNK_SIZE, timeinterval, maxfrequency, segment_probabilities, norm_keycount, cwt);
        }
    }
    catch (std::exception &e)
    {
        //TODO: Log properly
        std::cout << "analyzeSegment(): error" << e.what();
//        log->error(L"analyzeSegment(): error", e);
    }
}

void KeyDetector::countKeyProbabilities(std::vector<double> wavedata, long long icount, long long amt, double time, int maxfreq, KeyProbability *segment_probabilities, std::vector<double> &norm_keycount, std::vector<double> &cwt)
{
    KeyDetectionMatrix *matrix = getMatrix(maxfreq);
    int icountInt = static_cast<int>(icount);
    for (int p = 0; p < matrix->getMaxOctaves(); p++)
    {
        for (int ks = 0; ks < matrix->getShifts(); ks++)
        {
            for (int z = 0; z < 12; ++z)
            {
                cwt[z] = 0.0;
            }
            for (int m = 0; m < amt; ++m)
            {
                for (int z = 0; z < 12; ++z)
                {
                    double x = matrix->getValue(p, ks, m, z);
                    double y = wavedata[m + icountInt];
                    cwt[z] += y * x;
                }
            }
            for (int z = 0; z < 12; ++z)
            {
                norm_keycount[z] += std::abs(cwt[z]);
            }
        }
    }
    segment_probabilities->add(norm_keycount, time);
}
