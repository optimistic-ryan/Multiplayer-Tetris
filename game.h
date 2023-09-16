#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <fstream>

#include "commands.h"
#include "board.h"
#include "subject.h"
#include "Block.h"

class Board;

class Game : public Subject {
  protected:
    int alive;
    int prevAlive;
    std::string seqfile1;
    std::string seqfile2;
    int initialBoards;
    std::vector<std::shared_ptr<Board>> players;
    std::vector<int> targets;
    std::vector<int> maxScores;
    int currPlayer;
    std::ifstream file;  // Sequence File
    std::string stem;
    bool enableBonus;
    bool restarted;
    
  public:
    Game(int a, std::string seqfile1, std::string seqfile2);
    ~Game() = default;
    int getinitialBoards() const override;
    void render();
    void getEffect(const std::string& effect);
    void getCommand(const std::string& message);
    void sequence(const std::string& filename);
    void noRandom(const std::string& filename);
    void restart();
    void updateMaxScores();
    void interpret(const std::string& cmd);
    void setDeath(Board* dead);
    int getAlive() const override;
    int getPrevAlive() const override;
    void setPrevAlive(int val);
    void setSequenceFile(std::string& filename);
    void updateMaxScore(int score);
    void update();
    std::shared_ptr<Board> getBoardPtr();

    //Command Line Interpreter
    void setLevel(int level);
    void setBonus(bool setting);
    void setRestarted(bool val);
    bool getRestarted() const override;
    bool isBonus();
    std::vector<std::string> getState(int row, int col) const override;
    std::vector<std::string> getPrevState(int row, int col) const override;
    std::vector<std::string> getGraphicalState(int row, int col) const override;
    std::vector<int> getScores() const override;
    std::vector<int> getMaxScores() const override;
    std::vector<int> getLevels() const override;    
    std::vector<std::string> getNext() const override;
    std::vector<bool> getBlinds() const override;
    std::vector<Block*> getBlocks() const override;  
    std::vector<std::string> getHold()const override;
    std::vector<std::string> getNames();
    int getPlayer() const override;
};

#endif