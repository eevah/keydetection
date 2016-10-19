#include <iostream>
//#include <adoctint.h>
#include "KeyDetector.h"
#include "key/Key.h"

#include <libsndfile/sndfile.h>

int main() {
//    std::cout << "Hello, World!" << std::endl;
//    std::string filename("C:\\Users\\Ivana\\ClionProjects\\KeyDetetection\\src\\data\\pianoG.wav");
//    KeyDetector keyDetector(filename);
//    DetectedKey *key = keyDetector.detectKey();
//
//    Key *trueKey = Key::getKey("G");
//    if (key->getStartKey()->equals(trueKey)){
//        std::cout << "Success";
//    }
//    else {
//        std::cout << "Failure";
//    }
//    std::string kstr = key->getStartKey()->toString();
    SNDFILE		*infile = NULL ;



    SF_INFO info = {0};
    SNDFILE *sf = NULL;

    std::string filename = "C:\\Users\\Ivana\\ClionProjects\\KeyDetetection\\src\\data\\pianoG.wav";
    const char *charName = filename.c_str();
    sf_open(charName, SFM_READ, &info);
    if((sf = sf_open(charName, SFM_READ, &info)) == NULL)
    {
        std::cout << "ERROR\n";
        return 0;
    }

    std::cout << "Sample rate: " << info.samplerate << "\n";
    std::cout << "Channels: " << info.channels << "\n";


//    typedef struct
//    {    sf_count_t  frames ;     /* Used to be called samples. */
//        int         samplerate ;
//        int         channels ;
//        int         format ;
//        int         sections ;
//        int         seekable ;
//    } SF_INFO ;
    // Buffer Size
  // m_bufferSize = info.frames * info.channels * sizeof(int);

    return 0;
}

