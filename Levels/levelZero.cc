#include "levelZero.h"
using namespace std;

// Level Zero Ctor
LevelZero::LevelZero(string stem): Level{{0, 0, 0, 0, 0, 0, 0}, 0, 0, false, stem} {
    ifstream file{stem};
    gravity = 0;
}

// Next function produces the next block
string LevelZero::next() {
    string type = "";
    // opening file
    if (!file.is_open()) {
        file.open(stem);
    }
    
    // reading from file
    if (!(file >> type)) {
        file.clear();
        file.seekg(0, std::ios::beg);
        file >> type;
    } 
    return type;
}

// getSinceClear method
int LevelZero::getSinceClear() const {
    return -1;
}

// updateSinceClear method
void LevelZero::updateSinceClear(bool clear) {
    return;
}
