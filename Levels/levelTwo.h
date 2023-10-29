#ifndef LEVELTWO_H
#define LEVELTWO_H

#include <string>
#include "level.h"

class LevelTwo : public Level {
        std::string next() override;
    public:
        LevelTwo();
        int getSinceClear() const;
        void updateSinceClear(bool clear);
};

#endif 
