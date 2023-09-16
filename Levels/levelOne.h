#ifndef LEVELONE_H
#define LEVELONE_H

#include <string>
#include "level.h"

class LevelOne : public Level {
        std::string next() override;
    public:
        LevelOne();
        int getSinceClear() const override;
        void updateSinceClear(bool clear) override;
};

#endif 
