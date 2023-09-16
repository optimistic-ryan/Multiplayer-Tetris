#ifndef LEVELFIVEPLUS7_H
#define LEVELFIVEPLUS_H

#include <string>
#include "level.h"

class LevelFivePlus : public Level {
        int sinceClear;
        std::string next() override;
    public:
        LevelFivePlus(int level, std::string stem="", bool random=true);
        int getSinceClear() const override;
        void updateSinceClear(bool clear) override;
};

#endif 

