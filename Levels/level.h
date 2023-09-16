#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Level class
class Level {
    protected:
        std::vector<int> freq;
        int gravity;
        int currLevel;
        bool random;
        std::string stem;
        std::ifstream file;
        virtual std::string next() = 0;
        
    public:
        static std::vector<std::string> types;
        Level(std::vector<int> freq, int gravity, int currLevel, bool random, std::string stem = "");
        std::string nextBlock();
        int getLevel() const;
        int getGravity() const;
        void setGravity(int grav);
        bool getRandom() const;
        void setRandom(bool rand);
        void setFile(std::string fileName); 
        virtual ~Level() = default;
        virtual int getSinceClear() const = 0;
        virtual void updateSinceClear(bool clear) = 0;
};

#endif