#include "levelFour.h"
using namespace std;

// Level 4 ctor
LevelFour::LevelFour(string stem, bool random): Level{{1, 1, 1, 1, 2, 2, 1}, 0, 4, random, stem}, sinceClear{0} {
    ifstream file{stem};
    gravity = 1;
}

// next block generator
string LevelFour::next() {
    // if random, generating the next block randomly
    if (random) {
        vector<int> count;
        int length = freq.size();
        for (int i = 0; i < length; i++) {
            for (int j = 1; j <= freq[i]; j++) {
                count.emplace_back(i);
            }
        }

        length = count.size();

        int r = std::rand();
        r = r % length;

        return types[count[r]];
    }
    // else reading from the file
    else {
        string type = "";
        if (!file.is_open()) {
            file.open(stem);
        }
        
        if (!(file >> type)) {
            file.clear();
            file.seekg(0, std::ios::beg);
            file >> type;
        } 
        return type;
    }
}

// getSinceClear function
int LevelFour::getSinceClear() const {
    return sinceClear;
}

// updateSinceClear function
void LevelFour::updateSinceClear(bool clear) {
    if (clear) {
        sinceClear = 0;
    } else {
        sinceClear += 1;
    }
}
