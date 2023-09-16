#include "level.h"
using namespace std;

// Level ctor
Level::Level(std::vector<int> freq, int gravity, int currLevel, bool random, string stem): 
    freq{freq}, gravity{gravity}, currLevel{currLevel}, random{random}, stem{stem} {}

// nextBlock functions polymorphicall retrieves the next block
string Level::nextBlock() {
    return next();
}

// accessor for level field
int Level::getLevel() const {
    return currLevel;
}

// mutator for gravity field
void Level::setGravity(int grav) {
    gravity = grav;
}

// accessor for gravity field
int Level::getGravity() const {
    return gravity;
}

// accessor for random field
bool Level::getRandom() const {
    return random;
}

// mutator for random field
void Level::setRandom(bool rand) {
    if (currLevel >= 3)
    random = rand;
}

// mutator for file field
void Level::setFile(string fileName) {
    stem = fileName;
    setRandom(false);
}

// vector of string types
vector<string> Level::types{"I", "J", "L", "O", "S", "Z", "T"};