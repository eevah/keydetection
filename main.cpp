#include <iostream>
//#include <adoctint.h>
#include "KeyDetector.h"
#include "key/Key.h"

int main() {

    //std::string filename("C:\\Users\\Ivana\\ClionProjects\\KeyDetetection\\src\\data\\F-minor.wav");
//    WavFile* pObjWavFile = new WavFile;
//    pObjWavFile->readWavFile(filename);
//    pObjWavFile->displayInformation(filename);
//    pObjWavFile->closeWavFile();

    std::string filename;
    cout << "Enter the path to a WAV file: ";
    cin >> filename;
    //cout << "You entered the number " << input << ".\n";



    std::cout << "Processing file: " << filename << std::endl;
    KeyDetector keyDetector(filename);
    DetectedKey *key = keyDetector.detectKey();
    std::string kstr = key->getStartKey()->toString();
    std::cout << kstr;

//    std::string test = Key::getKey("Gm")->toString();
//    std::string t2 = Key::getKey("Gm")->getKeyNotationSharp();

    return 0;
}

