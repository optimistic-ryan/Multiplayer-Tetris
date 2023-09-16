#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <memory>
#include <vector>

#include "game.h"
#include "Block.h"
#include "Levels/level.h"
#include "Levels/levelZero.h"
#include "Levels/levelOne.h"
#include "Levels/levelTwo.h"
#include "Levels/levelThree.h"
#include "Levels/levelFour.h"
#include "Levels/levelFivePlus.h"

class Game;

class Board {
  public:
    inline static int start = 0;
  protected:
    Game& g;
    std::vector<std::vector<char>> board;
    std::vector<std::vector<std::string>> graphicalBoard;
    std::vector<std::vector<std::string>> prev;
    int score;
    int seed;
    std::string stem;
    std::shared_ptr<Level> currLevel;
    std::vector<std::shared_ptr<Block>> dropped;
    std::shared_ptr<Block> current;
    bool heavy;   
    bool blind;   
    bool forced;
    std::string forcedString;
    std::string next;
    std::string hold;
    int heaviness;

  public:
    Board(Game& g, std::string stem);
    ~Board() = default;
    void move(std::string cmd, Block* b);
    void drop();
    void clearLines(bool fromStar);
    void clearBlocks(int row);   
    void clearBoard();
    void swapHold();
    void levelUp();
    void levelDown();
    void special(int count);
    void sendEffect(const std::string& effect);
    void force(std::string b);
    void dropStar();
    void setBlind(bool b);
    bool getBlind();
    void setHeavy(bool b);
    void addGarbage(int lines);
    void setForced(bool b, std::string block);
    void syncBoard();
    int getScore() const;
    int getLevelVal() const; 
    Block *getBlock() const;  
    Block* getCurrent() const;
    Level* getLevel() const;
    std::string getNext() const;
    std::string getHold();
    std::string getState(int row, int col) const;
    std::string getPrevState(int row, int col) const;
    std::string getGraphicalState(int row, int cal) const;
    
  private:
    std::string nextBlock();
    bool checkCollide(int x1, int x2, int x3, int x4, int y1, int y2, int y3, int y4);
    bool allClear();
    bool checkDeath();
    void shiftDown(int row);
    void shiftUp();
    friend std::ostream &operator<<(std::ostream &out, const Board&b);
    
};

#endif