#ifndef COMMANDS_H
#define COMMANDS_H

#include <iostream>

#include "trienode.h"
#include "game.h"

class Game;

class Commands {
    Game& g;
    std::unique_ptr<TrieNode> trie;
    
  public:
    Commands(Game& g);
    ~Commands() = default;
    void processCommands();
    void sendCommand(const std::string& message);
};

#endif
