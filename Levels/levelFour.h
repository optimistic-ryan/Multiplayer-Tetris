#ifndef LEVELFOUR_H
#define LEVELFOUR_H

#include <string>
#include "level.h"

class LevelFour : public Level {
        int sinceClear;
        std::string next() override;
    public:
        LevelFour(std::string stem="", bool random=true);
        int getSinceClear() const override;
        void updateSinceClear(bool clear) override;
};

#endif 

