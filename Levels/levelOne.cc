#include "levelOne.h"
using namespace std;

LevelOne::LevelOne(): Level{{2, 2, 2, 2, 1, 1, 2}, 0, true, 1} {}

string LevelOne::next() {
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

int LevelOne::getSinceClear() const {
    return - 1;
}
void LevelOne::updateSinceClear(bool clear) {
    return;
}
