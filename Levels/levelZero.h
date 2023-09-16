#ifndef LEVELZERO_H
#define LEVELZERO_H

#include <fstream>
#include <string>
#include "level.h"

// Level Zero Class
class LevelZero : public Level {
        std::string next() override;
    public:
        LevelZero(std::string stem = "");
        int getSinceClear() const override;
        void updateSinceClear(bool clear) override;
};

#endif 
