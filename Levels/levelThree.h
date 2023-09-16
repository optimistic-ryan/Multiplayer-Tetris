#ifndef LEVELTHREE_H
#define LEVELTHREE_H

#include <string>
#include <fstream>
#include "level.h"

class LevelThree : public Level {
        std::string next() override;
    public:
        LevelThree(std::string stem="", bool random=true);
        int getSinceClear() const override;
        void updateSinceClear(bool clear) override;
};

#endif 
