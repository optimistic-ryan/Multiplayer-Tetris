#include "levelTwo.h"

using namespace std;

// Level Two ctor
LevelTwo::LevelTwo(): Level{{1, 1, 1, 1, 1, 1, 1}, 0, 2, true} {
    gravity = 0;
}

// next block generator
string LevelTwo::next() {

    // randomly generating blocks
    vector<int> count;
    int length = freq.size();
    for (int i = 0; i < length; i++) {
        for (int j = 1; j <= freq[i]; j++) {
            count.emplace_back(i);
        }
    }

    length = count.size();
    int rand = std::rand() % length;

    // returning the approp. block
    return types[count[rand]];
}

int LevelTwo::getSinceClear() const {
    return -1;
}
void LevelTwo::updateSinceClear(bool clear) {
    return;
}
