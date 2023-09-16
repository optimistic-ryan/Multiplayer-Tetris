#include <string>

#include "board.h"

using namespace std;

// Board constructor
Board::Board(Game &g, string stem)
    : g{g}, board{18, vector<char>(11, ' ')}, graphicalBoard(18, std::vector<std::string>(11, " ")), 
      prev(18, std::vector<std::string>(11, " ")), score{0}, stem{stem}, currLevel{make_unique<LevelZero>(stem)},
      current{nullptr}, heavy{false}, blind{false} {
  current = make_unique<Block>(currLevel->nextBlock(), 0);
  next = currLevel->nextBlock();
  hold = "nothing";
  heaviness = 0;
  syncBoard();
}

// drop a star block in the middle every 5 rounds the player doesn't clear line
void Board::dropStar() {
  std::shared_ptr<Block> star = make_shared<Block>("*", currLevel->getLevel());
  for (int i = 0; i < 18; ++i) {
    move("down", star.get());
  }

  dropped.emplace_back(star);
  int c = star->getPixels()[0].first;
  int r = star->getPixels()[0].second;
  board[r][c] = '*';
  clearLines(true);
  g.updateMaxScores();
  g.updateMaxScore(score);
}

//-----------------------block/board behaviors-----------------------

// move takes in command and checks if we can move the block  using checkCollide
void Board::move(string cmd, Block *b) {
  int gravity = currLevel->getGravity() + heaviness;

  int x1, x2, x3, x4, y1, y2, y3, y4;
  x1 = b->getPixels()[0].first;
  x2 = b->getPixels()[1].first;
  x3 = b->getPixels()[2].first;
  x4 = b->getPixels()[3].first;
  y1 = b->getPixels()[0].second;
  y2 = b->getPixels()[1].second;
  y3 = b->getPixels()[2].second;
  y4 = b->getPixels()[3].second;

  if (cmd == "left") {
    x1 -= 1;
    x2 -= 1;
    x3 -= 1;
    x4 -= 1;

    if (Board::checkCollide(x1, x2, x3, x4, y1, y2, y3, y4)) {
      return;
    } else {
      b->left();
      for (int i = 0; i < gravity; ++i) {
        move("down", b);
      }
    }
  } else if (cmd == "right") {

    x1 += 1;
    x2 += 1;
    x3 += 1;
    x4 += 1;

    if (Board::checkCollide(x1, x2, x3, x4, y1, y2, y3, y4)) {
      return;
    } else {
      b->right();
      for (int i = 0; i < gravity; ++i) {
        move("down", b);
      }
    }

  } else if (cmd == "down") {
    y1 -= 1;
    y2 -= 1;
    y3 -= 1;
    y4 -= 1;

    if (Board::checkCollide(x1, x2, x3, x4, y1, y2, y3, y4)) {
      return;
    } else {
      b->down();
    }

  } else if (cmd == "clockwise") {
    b->rotatec();
    x1 = b->getPixels()[0].first;
    x2 = b->getPixels()[1].first;
    x3 = b->getPixels()[2].first;
    x4 = b->getPixels()[3].first;
    y1 = b->getPixels()[0].second;
    y2 = b->getPixels()[1].second;
    y3 = b->getPixels()[2].second;
    y4 = b->getPixels()[3].second;
    if (Board::checkCollide(x1, x2, x3, x4, y1, y2, y3, y4)) {
      b->rotatecc();
      return;
    } else {
      for (int i = 0; i < gravity; ++i) {
        move("down", b);
      }
      return;
    }
  } else if (cmd == "counterclockwise") {
    b->rotatecc();
    x1 = b->getPixels()[0].first;
    x2 = b->getPixels()[1].first;
    x3 = b->getPixels()[2].first;
    x4 = b->getPixels()[3].first;
    y1 = b->getPixels()[0].second;
    y2 = b->getPixels()[1].second;
    y3 = b->getPixels()[2].second;
    y4 = b->getPixels()[3].second;

    if (Board::checkCollide(x1, x2, x3, x4, y1, y2, y3, y4)) {
      b->rotatec();
      return;
    } else {
      for (int i = 0; i < gravity; ++i) {
        move("down", b);
      }
      return;
    }
  }
}

// drop the current block, check for collision and check death for next round
void Board::drop() {
  if (checkDeath()) {
    g.setDeath(this);
    return;
  }

  for (int i = 0; i < 15; ++i) {
    move("down", current.get());
  }

  string t = current->blockType();

  int x1 = current->getPixels()[0].first;
  int x2 = current->getPixels()[1].first;
  int x3 = current->getPixels()[2].first;
  int x4 = current->getPixels()[3].first;
  int y1 = current->getPixels()[0].second;
  int y2 = current->getPixels()[1].second;
  int y3 = current->getPixels()[2].second;
  int y4 = current->getPixels()[3].second;

  if (t == "I") {
    board[y1][x1] = 'I';
    board[y2][x2] = 'I';
    board[y3][x3] = 'I';
    board[y4][x4] = 'I';
  } else if (t == "J") {
    board[y1][x1] = 'J';
    board[y2][x2] = 'J';
    board[y3][x3] = 'J';
    board[y4][x4] = 'J';
  } else if (t == "L") {
    board[y1][x1] = 'L';
    board[y2][x2] = 'L';
    board[y3][x3] = 'L';
    board[y4][x4] = 'L';
  } else if (t == "O") {
    board[y1][x1] = 'O';
    board[y2][x2] = 'O';
    board[y3][x3] = 'O';
    board[y4][x4] = 'O';
  } else if (t == "S") {
    board[y1][x1] = 'S';
    board[y2][x2] = 'S';
    board[y3][x3] = 'S';
    board[y4][x4] = 'S';
  } else if (t == "Z") {
    board[y1][x1] = 'Z';
    board[y2][x2] = 'Z';
    board[y3][x3] = 'Z';
    board[y4][x4] = 'Z';
  } else if (t == "T") {
    board[y1][x1] = 'T';
    board[y2][x2] = 'T';
    board[y3][x3] = 'T';
    board[y4][x4] = 'T';
  }

  dropped.emplace_back(current);
  clearLines(false);
  current = make_shared<Block>(next, currLevel->getLevel());
  next = currLevel->nextBlock();

  if (blind) {
    blind = false;
  }
  if (g.isBonus()) {
    if (allClear()) {
      score += 1000;
    }
  }

  g.updateMaxScores();

  if (checkDeath()) {
    g.setDeath(this);
    return;
  }
}

Block *Board::getBlock() const { return current.get(); }
// swap the current block with the block on hold (bonus feature)
string Board::getHold() { return hold; }

// iterate through the board to check if any lines need to be cleared
void Board::clearLines(bool fromStar) {
  int count = 0;
  vector<int> cleared;

  for (int r = 14; r >= 0; --r) {
    bool clear = true;
    for (int c = 0; c < 11; ++c) {
      if (board[r][c] == ' ') {
        clear = false;
        break;
      }
    }

    if (clear) {
      count++;
      shiftDown(r);
      clearBlocks(r);
    }
  }

  if (count != 0) {
    score += (currLevel->getLevel() + count) * (currLevel->getLevel() + count) ;
  }

  g.updateMaxScore(score);

  if (count >= 2) {
    special(count);
  }

  if (fromStar) {
    return;
  }

  if (currLevel->getLevel() >= 4) {
    if (count == 0) {
      if (currLevel->getSinceClear() % 5 == 4) {
        dropStar();
        currLevel->updateSinceClear(false);
      } else {
        currLevel->updateSinceClear(false);
      }
    } else {
      currLevel->updateSinceClear(true);
    }
  }
}

// iterate through all the dropped blocks and eliminate the pixels that are to be cleared
void Board::clearBlocks(int row) {
  for (auto &b : dropped) {
    b->clearLine(row);
  }

  for (int i = 0; i < dropped.size();) {
    if (dropped[i]->empty()) {
      score += (dropped[i]->getLevel() + 1) * (dropped[i]->getLevel() + 1);
      dropped.erase(dropped.begin() + i);
    } else {
      ++i;
    }
  }
}

// clear the entire board
void Board::clearBoard() {
  for (int n = 15; n >= 0; n--) {
    shiftDown(n);
    clearBlocks(n);
  }
}

Block *Board::getCurrent() const { return current.get(); }

// swap the current block with the block on hold (bonus feature)
void Board::swapHold() {
  string now;
  if (hold == "nothing") {
    hold = current->blockType();
    now = next;
    next = currLevel->nextBlock();
  } else {
    now = hold;
    hold = current->blockType();
  }

  current = make_unique<Block>(now, currLevel->getLevel());

  if (checkDeath()) {
    g.setDeath(this);
    return;
  }

  g.render();
}

string Board::getNext() const { return next; }

int Board::getScore() const { return score; }

//-----------------------levels-----------------------
int Board::getLevelVal() const { return currLevel->getLevel(); }

void Board::levelUp() {
  int newLevel = currLevel->getLevel() + 1;
  if (newLevel == 1) {
    currLevel = make_unique<LevelOne>();
    current = make_unique<Block>(currLevel->nextBlock(), newLevel);
    next = currLevel->nextBlock();
  } else if (newLevel == 2) {
    currLevel = make_unique<LevelTwo>();
    current = make_unique<Block>(currLevel->nextBlock(), newLevel);
    next = currLevel->nextBlock();
  } else if (newLevel == 3) {
    currLevel = make_unique<LevelThree>();
    current = make_unique<Block>(currLevel->nextBlock(), newLevel);
    next = currLevel->nextBlock();
  } else if (newLevel == 4) {
    currLevel = make_unique<LevelFour>();
    current = make_unique<Block>(currLevel->nextBlock(), newLevel);
    next = currLevel->nextBlock();
  } else if (g.isBonus() && newLevel >= 5) {
    currLevel = make_unique<LevelFivePlus>(newLevel);
    current = make_unique<Block>(currLevel->nextBlock(), newLevel);
    next = currLevel->nextBlock();
  }
}

void Board::levelDown() {
  int newLevel = currLevel->getLevel() - 1;
  if (newLevel == 0) {
    currLevel = make_unique<LevelZero>(stem);
    current = make_unique<Block>(currLevel->nextBlock(), newLevel);
    next = currLevel->nextBlock();
  } else if (newLevel == 1) {
    currLevel = make_unique<LevelOne>();
    current = make_unique<Block>(currLevel->nextBlock(), newLevel);
    next = currLevel->nextBlock();
  } else if (newLevel == 2) {
    currLevel = make_unique<LevelTwo>();
    current = make_unique<Block>(currLevel->nextBlock(), newLevel);
    next = currLevel->nextBlock();
  } else if (newLevel == 3) {
    currLevel = make_unique<LevelThree>();
    current = make_unique<Block>(currLevel->nextBlock(), newLevel);
    next = currLevel->nextBlock();
  } else if (newLevel == 4) {
    currLevel = make_unique<LevelFour>();
    current = make_unique<Block>(currLevel->nextBlock(), newLevel);
    next = currLevel->nextBlock();
  } else if (g.isBonus() && newLevel >= 5) {
    currLevel = make_unique<LevelFivePlus>(newLevel);
    current = make_unique<Block>(currLevel->nextBlock(), newLevel);
    next = currLevel->nextBlock();
  }
}

Level *Board::getLevel() const { return currLevel.get(); }

//-----------------------special actions-----------------------
// ask a player to chose special action for the target
void Board::special(int count) {
  g.render();

  if (g.isBonus()) {
    std::cout << "Choose a special action: blind, heavy, force, or garbage."
              << endl;
  } else {
    std::cout << "Choose a special action: blind, heavy, or force." << endl;
  }

  string effect;

  while (true) {
    cin >> effect;
    if (effect == "blind") {
      g.getEffect("blind");
      break;
    } else if (effect == "heavy") {
      g.getEffect("heavy");
      break;
    } else if (effect == "force") {
      std::cout << "Choose a block: I, J, L, O, S, Z, T" << endl;
      g.getEffect("force");
      break;
    } else if (g.isBonus() && effect == "garbage") {
      g.getEffect(to_string(count));
      break;
    }
  }
}

// send chosen effect to opponent
void Board::sendEffect(const string &effect) { g.getEffect(effect); }

// force a block to the target
void Board::setForced(bool b, string block) {
  if (b == true) {
    forced = true;
    forcedString = block;
    current = make_shared<Block>(forcedString, currLevel->getLevel());

    if (checkDeath()) {
      g.setDeath(this);
      return;
    }
  } else {
    forced = false;
    forcedString = "";
  }
}

void Board::setBlind(bool val) { blind = val; }

bool Board::getBlind() { return blind; }

void Board::setHeavy(bool val) {
  heavy = val;
  if (val) {
    currLevel->setGravity(currLevel->getGravity());
    heaviness += 2;
  }
}

// special action that sends garbage lines to the bottom of target's board
// the lines sent depends on how many lines this board clears (bonus feature)
void Board::addGarbage(int lines) {
  srand((unsigned)time(NULL));
  // Get a random number
  int gap = rand() % 11;

  for (int r = 18 - lines; r < 18; ++r) {
    for (int c = 0; c < 11; ++c) {

      if (board[r][c] != ' ') {
        g.setDeath(this);
      }
    }
  }

  for (auto &b : dropped) {
    b->up();
  }

  for (int i = 0; i < lines; ++i) {
    shiftUp();
  }

  for (int l = 0; l < lines; l++) {
    for (int n = 0; n < 11; n++) {
      if (n == gap) {
        continue;
      }
      std::shared_ptr<Block> g = make_shared<Block>("#", currLevel->getLevel());
      g->setPixel(n, l);
      board[l][n] = '#';
    }
  }
  //syncBoard();
}


void Board::force(string b) {
  if (b == "I") {
    current = make_unique<Block>("I", currLevel->getLevel());
  } else if (b == "J") {
    current = make_unique<Block>("J", currLevel->getLevel());
  } else if (b == "L") {
    current = make_unique<Block>("L", currLevel->getLevel());
  } else if (b == "O") {
    current = make_unique<Block>("O", currLevel->getLevel());
  } else if (b == "S") {
    current = make_unique<Block>("S", currLevel->getLevel());
  } else if (b == "Z") {
    current = make_unique<Block>("Z", currLevel->getLevel());
  } else if (b == "T") {
    current = make_unique<Block>("T", currLevel->getLevel());
  }
}

//-----------------------rendering-----------------------
ostream &operator<<(ostream &out, const Board &b) {
  for (int c = 0; c < 11; ++c) {
    cout << "-";
  }
  cout << endl;
  for (int r = 17; r >= 0; --r) {
    for (int c = 0; c < 11; ++c) {
      cout << b.board[r][c];
    }
    cout << endl;
  }
  for (int c = 0; c < 11; ++c) {
    cout << "-";
  }
}


string Board::getState(int row, int col) const {
  return string(1, board[row][col]);
}

string Board::getGraphicalState(int row, int col) const {
  return graphicalBoard[row][col];
}

string Board::getPrevState(int row, int col) const { return prev[row][col]; }

string Board::nextBlock() { return next; }
// check if the given four cordinates collide with the existing block in the
// board
bool Board::checkCollide(int x1, int x2, int x3, int x4, int y1, int y2, int y3,
                         int y4) {

  if (x1 < 0 || x2 < 0 || x3 < 0 || x4 < 0 || x1 > 10 || x2 > 10 || x3 > 10 ||
      x4 > 10) {
    return true;
  } else if (y1 < 0 || y2 < 0 || y3 < 0 || y4 < 0 || y1 > 17 || y2 > 17 ||
             y3 > 17 || y4 > 17) {
    return true;
  } else if (board[y1][x1] != ' ' || board[y2][x2] != ' ' ||
             board[y3][x3] != ' ' || board[y4][x4] != ' ') {
    return true;
  } else {
    return false;
  }
}

void Board::shiftDown(int row) {
  for (int r = row; r < 17; ++r) {
    for (int c = 0; c < 11; ++c) {
      board[r][c] = board[r + 1][c];
    }
  }
}

void Board::shiftUp() {
  for (int r = 17; r > 0; --r) {
    for (int c = 0; c < 11; ++c) {
      board[r][c] = board[r - 1][c];
    }
  }
  int r = 0;
  for (int c = 0; c < 11; ++c) {
    board[r][c] = ' ';
  }
}

// check if the board is has all cleared and add additional score
bool Board::allClear() {
  for (int r = 17; r >= 0; --r) {
    for (int c = 0; c < 11; ++c) {
      if (board[r][c] != ' ') {
        return false;
      }
    }
  }
  return true;
}

void Board::syncBoard() {
  prev = graphicalBoard;

  for (int r = 0; r < 18; r++) {
    for (int c = 0; c < 11; c++) {
      graphicalBoard[r][c] = board[r][c];
    }
  }
  int x1, x2, x3, x4, y1, y2, y3, y4;
  x1 = current->getPixels()[0].first;
  x2 = current->getPixels()[1].first;
  x3 = current->getPixels()[2].first;
  x4 = current->getPixels()[3].first;
  y1 = current->getPixels()[0].second;
  y2 = current->getPixels()[1].second;
  y3 = current->getPixels()[2].second;
  y4 = current->getPixels()[3].second;
  if(!(y1 == -1 || x1 == -1)){
    graphicalBoard[y1][x1] = current->blockType();
  }
  if(!(y2 == -1 || x2 == -1)){
    graphicalBoard[y2][x2] = current->blockType();
  }if(!(y3 == -1 || x3 == -1)){
    graphicalBoard[y3][x3] = current->blockType();
  }if(!(y4 == -1 || x4 == -1)){
    graphicalBoard[y4][x4] = current->blockType();
  }

  if (blind) {
    for (int r = 3; r <= 12; r++) {
      for (int c = 3; c <= 9; c++) {
        graphicalBoard[r][c] = "?";
      }
    }
  }
}

// check if the block spawn point is blocked, and if so, set board to dead
bool Board::checkDeath() {
  int x1 = current->getPixels()[0].first;
  int x2 = current->getPixels()[1].first;
  int x3 = current->getPixels()[2].first;
  int x4 = current->getPixels()[3].first;
  int y1 = current->getPixels()[0].second;
  int y2 = current->getPixels()[1].second;
  int y3 = current->getPixels()[2].second;
  int y4 = current->getPixels()[3].second;

  if (checkCollide(x1, x2, x3, x4, y1, y2, y3, y4)) {
    return true;
  }

  return false;
}
