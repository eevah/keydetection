#include <iostream>
//#include <adoctint.h>
#include "KeyDetector.h"
#include "key/Key.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
//    std::string filename("C:\\Users\\Ivana\\ClionProjects\\KeyDetetection\\data\\F minor.wav");
//    KeyDetector keyDetector(filename);
//    DetectedKey *key = keyDetector.detectKey();
//    std::string kstr = key->getStartKey()->toString();

    std::string test = Key::getKey("Gm")->toString();
    std::string t2 = Key::getKey("Gm")->getKeyNotationSharp();

    return 0;
}

