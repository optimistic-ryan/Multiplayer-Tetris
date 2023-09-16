#include "levelThree.h"

using namespace std;

// Level 3 ctor
LevelThree::LevelThree(string stem, bool random): Level{{1, 1, 1, 1, 2, 2, 1}, 0, 3, random} {
    ifstream file{stem};
    gravity = 1;
}

// next block generator
string LevelThree::next() {

    // randomly generating blocks if random
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
    // else reading from file
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

int LevelThree::getSinceClear() const {
    return -1;
}
void LevelThree::updateSinceClear(bool clear) {
    return;
}
