#include "game.h"
#include "observer.h"
#include "subject.h"

using namespace std;

Game::Game(int a, std::string seqfile1, std::string seqfile2)
    : alive{a}, prevAlive{a}, seqfile1{seqfile1}, seqfile2{seqfile2},
      initialBoards{a}, currPlayer{0}, restarted{false} {
        
  // initialize players and targets as needed
  for (int i = 0; i < initialBoards; i++) {
    string file;
    enableBonus = false;
      
    // handling provided seqfiles
    if (seqfile1 != "" && i % 2 == 0) {
      file = seqfile1;
    } else if (seqfile2 != "" && i % 2 == 1) {
      file = seqfile2;
    } else {
      file = "sequence";
      if (i % 2 == 0) {
        file += to_string(1);
      } else {
        file += to_string(2);
      }
      file += ".txt";
    }

    players.emplace_back(make_shared<Board>(*this, file));

    targets.emplace_back((i + 1) % initialBoards);
    for (int n = 0; n < alive; n++) {
      maxScores.emplace_back(0);
    }
  }
}

// force the observer to render
void Game::render() {
  shared_ptr<Board> currBoard = players[currPlayer];
  if (Board::start != 0) {
    currBoard->syncBoard();
  }
  Board::start += 1;
  notifyObservers();
}

// interpreting a player's command
void Game::interpret(const string &cmd) {
  shared_ptr<Board> currBoard = players[currPlayer];

  if (cmd == "left") {
    currBoard->move("left", currBoard->getCurrent());
  } else if (cmd == "right") {
    currBoard->move("right", currBoard->getCurrent());
  } else if (cmd == "down") {
    currBoard->move("down", currBoard->getCurrent());
  } else if (cmd == "up") {
    currBoard->move("up", currBoard->getCurrent());
  } else if (cmd == "clockwise") {
    currBoard->move("clockwise", currBoard->getCurrent());
  } else if (cmd == "counterclockwise") {
    currBoard->move("counterclockwise", currBoard->getCurrent());
  } else if (cmd == "consecutiveDrop") {
    currBoard->drop();
  } else if (cmd == "drop") {
    int a = alive;
    currBoard->drop();
    if (a == alive) {
      currBoard->syncBoard();
    }
    currPlayer = targets[currPlayer];
  } else if (cmd == "levelup") {
    currBoard->levelUp();
  } else if (cmd == "nuke") {
    currBoard->clearBoard();
  } else if (cmd == "leveldown") {
    currBoard->levelDown();
  } else if (cmd == "random") {
    currBoard->getLevel()->setRandom(true);
  } else if (cmd == "special") {
    currBoard->special(4);
  } else if (cmd == "I") {
    currBoard->force("I");
  } else if (cmd == "J") {
    currBoard->force("J");
  } else if (cmd == "L") {
    currBoard->force("L");
  } else if (cmd == "O") {
    currBoard->force("O");
  } else if (cmd == "S") {
    currBoard->force("S");
  } else if (cmd == "Z") {
    currBoard->force("Z");
  } else if (cmd == "T") {
    currBoard->force("T");
  } else if (cmd == "restart") {
    restart();
  } else if (cmd == "hold") {
    currBoard->swapHold();
  }
}

void Game::getEffect(const string &effect) {
  shared_ptr<Board> targetBoard = players[targets[currPlayer]];
  if (effect == "blind") {
    targetBoard->setBlind(true);
  } else if (effect == "heavy") {
    targetBoard->setHeavy(true);
  } else if (effect == "force") {
    string block;
    cin >> block;
    targetBoard->setForced(true, block);
  } else if (isdigit(effect[0])) {
    targetBoard->addGarbage(stoi(effect));
  }
}

void Game::getCommand(const string &message) { interpret(message); }

void Game::sequence(const string &filename) {
  shared_ptr<Board> currBoard = players[currPlayer];
  ifstream file{filename};
  string cmd;

  while (file >> cmd) {
    if (cmd == "norandom") {
      if (currBoard->getLevelVal() < 3) {
        continue;
      }
      string f;
      file >> f;
      currBoard->getLevel()->setFile(f);
    } else if (cmd == "sequence") {
      string f;
      file >> f;
      sequence(f);
    } else {
      int multiplier = 0;
      int i = 0;
      bool flag = true;
      while (i < cmd.size() && isdigit(cmd[i])) {
        int increment = cmd[i] - '0';
        if (increment < 0 && i == 0) {
          flag = false;
          break;
        }
        multiplier = multiplier * 10 + increment;
        ++i;
      }

      if (multiplier == 0 && flag) {
        multiplier = 1;
      } else if (!flag) {
        cout << "Unknown Mulitplier: " << cmd << endl;
        return;
      }
      cmd = cmd.substr(i);
      if (cmd == "drop" && multiplier > 1) {
        for (int i = 0; i < multiplier - 1; ++i) {
          interpret("consecutiveDrop");
        }
        interpret("drop");
      } else {
        for (int i = 0; i < multiplier; ++i) {
          interpret(cmd);
        }
      }
    }
    render();
  }
}

void Game::noRandom(const string &filename) {
  shared_ptr<Board> currBoard = players[currPlayer];
  currBoard->getLevel()->setFile(filename);
  currBoard->getLevel()->setRandom(false);
}

void Game::setLevel(int level) {
  for (int i = 0; i < initialBoards; i++) {
    for (int j = 0; j < level; j++) {
      players[i]->levelUp();
      players[i]->syncBoard();
    }
  }
}

void Game::setRestarted(bool val) { restarted = val; }

int Game::getAlive() const { return alive; }

int Game::getPrevAlive() const { return prevAlive; }

void Game::setPrevAlive(int val) { prevAlive = val; }

int Game::getinitialBoards() const { return initialBoards; }

vector<string> Game::getState(int row, int col) const {
  vector<string> state;
  for (int i = 0; i < alive; i++) {
    state.emplace_back(players[i]->getState(row, col));
  }
  return state;
}

bool Game::getRestarted() const { return restarted; }

// find the most recent board to let graphical render faster
std::vector<std::string> Game::getPrevState(int row, int col) const {
  vector<string> prevState;
  for (int i = 0; i < alive; i++) {
    prevState.emplace_back(players[i]->getPrevState(row, col));
  }
  return prevState;
}

std::vector<std::string> Game::getGraphicalState(int row, int col) const {
  vector<string> graphicalState;
  for (int i = 0; i < alive; i++) {
    graphicalState.emplace_back(players[i]->getGraphicalState(row, col));
  }
  return graphicalState;
}

vector<int> Game::getScores() const {
  vector<int> scores;
  for (int i = 0; i < alive; ++i) {
    scores.emplace_back(players[i]->getScore());
  }
  return scores;
}

vector<int> Game::getMaxScores() const { return maxScores; }

vector<int> Game::getLevels() const {
  vector<int> levels;
  for (int i = 0; i < alive; ++i) {
    levels.emplace_back(players[i]->getLevelVal());
  }
  return levels;
}

vector<string> Game::getNext() const {
  vector<string> next;
  for (int i = 0; i < alive; ++i) {
    next.emplace_back(players[i]->getNext());
  }
  return next;
}

vector<string> Game::getHold() const {
  vector<string> next;
  for (int i = 0; i < alive; ++i) {
    next.emplace_back(players[i]->getHold());
  }
  return next;
}

vector<bool> Game::getBlinds() const {
  vector<bool> blinds;
  for (int i = 0; i < alive; ++i) {
    blinds.emplace_back(players[i]->getBlind());
  }
  return blinds;
}

vector<Block *> Game::getBlocks() const {
  vector<Block *> blocks;
  for (int i = 0; i < alive; i++) {
    blocks.emplace_back(players[i]->getBlock());
  }
  return blocks;
}

int Game::getPlayer() const { return currPlayer; }

void Game::updateMaxScores() {
  vector<int> scores = getScores();
  for (int i = 0; i < alive; i++) {
    maxScores[i] = max(maxScores[i], scores[i]);
  }
}

void Game::restart() {
  Board::start = 0;
  restarted = true;
  string file;

  for (int i = alive - 1; i >= 0; i--) {
    players.pop_back();
    targets.pop_back();
  }

  currPlayer = 0;
  alive = initialBoards;
  prevAlive = alive;
  for (int i = 0; i < initialBoards; i++) {
    if (seqfile1 != "" && i % 2 == 0) {
      file = seqfile1;
    } else if (seqfile2 != "" && i % 2 == 1) {
      file = seqfile2;
    } else {
      file = "sequence";
      if (i % 2 == 0) {
        file += to_string(1);
      } else {
        file += to_string(2);
      }
      file += ".txt";
    }
    players.emplace_back(make_shared<Board>(*this, file));
    targets.emplace_back((i + 1) % initialBoards);
  }
}

void Game::updateMaxScore(int score) {
  if (score > maxScores[currPlayer]) {
    maxScores[currPlayer] = score;
  }
}

void Game::setDeath(Board *dead) {
  int remove = -1;
  for (int n = 0; n < alive; n++) {
    if (dead == players[n].get()) {
      remove = n;
      break;
    }
  }

  if (remove == -1) {
    return; // no matching player found, exit the function
  }

  if (remove < players.size()) {
    players.erase(players.begin() + remove);
    targets.erase(targets.begin() + remove);
  }

  alive -= 1;
  if (alive <= 0) {
    return;
  }

  for (int i = 0; i < alive; i++) {
    if (i < targets.size()) {
      targets[i] = (i + 1) % alive;
    }
  }

  if (currPlayer == remove) {
    currPlayer = currPlayer % alive;
  }
  return;
}

bool Game::isBonus() { return enableBonus; }

std::shared_ptr<Board> Game::getBoardPtr() { return players[currPlayer]; }

void Game::setBonus(bool setting) { enableBonus = setting; }
