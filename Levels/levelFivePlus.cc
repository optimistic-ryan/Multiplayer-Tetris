#include "levelFivePlus.h"
using namespace std;

// Level 5+ ctor
LevelFivePlus::LevelFivePlus(int level, string stem, bool random): 
    Level{{1, 1, 1, 1, 2, 2, 1}, 0, level, random, stem}, sinceClear{0} {
    ifstream file{stem};
    gravity = level - 3;
}

// generating the next block
string LevelFivePlus::next() {
    // if random, generating the block randomly
    if (random) {
        vector<int> count;
        int length = freq.size();
        for (int i = 0; i < length; i++) {
            for (int j = 1; j <= freq[i]; j++) {
                count.emplace_back(i);
            }
        }

        length = count.size();

        int rand = std::rand() % length;

        return types[count[rand]];
    }
    // else retrieving the next block from the file
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

int LevelFivePlus::getSinceClear() const {
    return sinceClear;
}

// updateSinceClear method
void LevelFivePlus::updateSinceClear(bool clear) {
    if (clear) {
        sinceClear = 0;
    } else {
        sinceClear += 1;
    }
}
