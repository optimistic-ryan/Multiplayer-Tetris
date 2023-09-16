#include <iostream>
#include <memory>
#include "graphicalobserver.h"

using namespace std;

// graphical observer ctor
GraphicalObserver::GraphicalObserver(Game *subject, int top, int bottom, int left, int right): 
subject{subject}, top{top}, bottom{bottom}, left{left}, right{right}
{
  // attaching the observer to the subject
  subject->attach(this);
  // creating the underlying Xwindow display
  display = make_shared<Xwindow>((right - left + 1)*10, (bottom - top + 1)*10);

  // creating the map between block types and colours  
  map["I"] = Xwindow::Cyan;
  map["O"] = Xwindow::Yellow;
  map["J"] = Xwindow::Blue;
  map["L"] = Xwindow::Orange;
  map["T"] = Xwindow::Magenta;
  map["S"] = Xwindow::Green;
  map["Z"] = Xwindow::Red;
  map[" "] = Xwindow::White;
  map["*"] = Xwindow::Brown;
  map["#"] = Xwindow::Brown;
  map["?"] = Xwindow::Black;


}

// render function, renders a rectangle for the block
void GraphicalObserver::render(string type, int line, int x, int y) {
  int col = map[type];
  // rendering the updated state to the ostream
  getDisplay()->fillRectangle(y, x, DIM, DIM, col);
}

// notify method
void GraphicalObserver::notify() {
  // number of boards to actively display
  int length = subject->getAlive();

  // rendering level
  vector<int> levels = subject->getLevels();

  for (int i = 0; i < length; i++) {
    getDisplay()->drawString(15 + i * 120, 10, "Level:");
    getDisplay()->fillRectangle(60 + i * 120, 0, 20, 10, Xwindow::White); 
    getDisplay()->drawString(60 + i * 120, 10, to_string(levels[i]));
  }

  // rendering score
  vector<int> scores = subject->getScores();

  for (int i = 0; i < length; i++) {
    getDisplay()->drawString(15 + i * 120, 30, "Score:"); 
    getDisplay()->fillRectangle(60 + i * 120, 20, 40, 10, Xwindow::White);
    getDisplay()->drawString(60 + i * 120, 30, to_string(scores[i]));
  }

  // rendering line
  for (int i = 0; i < length; i++) {
    getDisplay()->fillRectangle(i * 120, 50, 110, 5, Xwindow::Black);
  }

  // getting the current player
  int player = subject->getPlayer();

  // resetting the boards if restarting the game
  if (subject->getRestarted()) {
    for (int b = 0; b < length; b++) {
      for (int r = ROWS; r >= 0; r--) {
        for (int c = 0; c < COLS; c++) {
          getDisplay()->fillRectangle(120*b + c*10, (ROWS-r)*10 + 70, 10, 10, Xwindow::White);
        }
      }
    }

    // resetting the next section
    for (int b = 0; b < length; b++) {
      getDisplay()->fillRectangle(120*b, 290, 40, 20, Xwindow::White); //change back later
    }

    // resetting the hold section
    if (subject->isBonus()) {
      for (int b = 0; b < length; b++) {
        getDisplay()->fillRectangle(120*b, 290 + OFFSET, 40, 20, Xwindow::White); //change back later
      }
    }
  } 

  // resetting the boards if a player has died/lost
  int initialBoards = subject->getinitialBoards();
  if (subject->getAlive() != subject->getPrevAlive()) {
    for (int b = 0; b < initialBoards; b++) {
        for (int r = ROWS; r >= 0; r--) {
          for (int c = 0; c < COLS; c++) {
            getDisplay()->fillRectangle(120*b + c*10, (ROWS-r)*10 + 70, 10, 10, Xwindow::White);
          }
        }
      }

      for (int b = 0; b < initialBoards; b++) {
        getDisplay()->fillRectangle(120*b, 290, 40, 20, Xwindow::White); //change back later
      }

      if (subject->isBonus()) {
        for (int b = 0; b < initialBoards; b++) {
          getDisplay()->fillRectangle(120*b, 290 + OFFSET, 40, 20, Xwindow::White); //change back later
      }
    }

    for (int b = 0; b < length; b++) {
      for (int r = ROWS; r >= 0; r--) {
        for (int c = 0; c < COLS; c++) {
          getDisplay()->fillRectangle(120*b + c*10, (ROWS-r)*10 + 70, 10, 10, map[subject->getGraphicalState(r, c)[b]]);
        }
      }
    }
  }
  // else displaying the state of all of the boards which are active
  else {
    for (int b = 0; b < length; b++) {
      for (int r = ROWS; r >= 0; r--) {
        for (int c = 0; c < COLS; c++) {
        if (subject->getGraphicalState(r, c)[b] != subject->getPrevState(r, c)[b]) {
          getDisplay()->fillRectangle(120*b + c*10, (ROWS - r)*10 + 70, 10, 10, map[subject->getGraphicalState(r, c)[b]]);
        }
        }
      }
    }
  }

  // displaying a divider for each board
  for (int i = 0; i < length; i++) {
    getDisplay()->fillRectangle(i * 120, 250, 110, 5, Xwindow::Black);
  }
  
  // rendering the next block
  vector<string> next = subject->getNext();
  vector<string> holds = subject->getHold();

  // rendering the next block if its the players turn
  for (int b = 0; b < length; b++) {
    if (b == player) {
      getDisplay()->fillRectangle(120*b, 290, 40, 20, Xwindow::White); 
    }
    // de-rendering the previous player's block
    if (b == (player - 1) % length || (player == 0 && b == (length - 1))) {
      getDisplay()->fillRectangle(120*b, 290, 40, 20, Xwindow::White);
    }
    // rendering the next block
    getDisplay()->drawString(15 + b * 120, 280, "Next:");
    if (b == player) {
      if (next[b] == "I") {
        for (int i = 0; i < 4; i++) {
          getDisplay()->fillRectangle(120*b + i*10, 290, 10, 10, map["I"]);
        }
      }
      else if (next[b] == "O") {
        getDisplay()->fillRectangle(120*b, 290, 10, 10, map["O"]);
        getDisplay()->fillRectangle(120*b + 10, 290, 10, 10, map["O"]);
        getDisplay()->fillRectangle(120*b, 300, 10, 10, map["O"]);
        getDisplay()->fillRectangle(120*b + 10, 300, 10, 10, map["O"]);
      }
      else if (next[b] == "J") {
        getDisplay()->fillRectangle(120*b, 290, 10, 10, map["J"]);
        getDisplay()->fillRectangle(120*b, 300, 10, 10, map["J"]);
        getDisplay()->fillRectangle(120*b + 10, 300, 10, 10, map["J"]);
        getDisplay()->fillRectangle(120*b + 20, 300, 10, 10, map["J"]);
      }
      else if (next[b] == "L") {
        getDisplay()->fillRectangle(120*b + 20, 290, 10, 10, map["L"]);
        getDisplay()->fillRectangle(120*b, 300, 10, 10, map["L"]);
        getDisplay()->fillRectangle(120*b + 10, 300, 10, 10, map["L"]);
        getDisplay()->fillRectangle(120*b + 20, 300, 10, 10, map["L"]);
      }
      else if (next[b] == "T") {
        getDisplay()->fillRectangle(120*b, 290, 10, 10, map["T"]);
        getDisplay()->fillRectangle(120*b + 10, 290, 10, 10, map["T"]);
        getDisplay()->fillRectangle(120*b + 20, 290, 10, 10, map["T"]);
        getDisplay()->fillRectangle(120*b + 10, 300, 10, 10, map["T"]);
      }
      else if (next[b] == "S") {
        getDisplay()->fillRectangle(120*b + 10, 290, 10, 10, map["S"]);
        getDisplay()->fillRectangle(120*b + 20, 290, 10, 10, map["S"]);
        getDisplay()->fillRectangle(120*b, 300, 10, 10, map["S"]);
        getDisplay()->fillRectangle(120*b + 10, 300, 10, 10, map["S"]);
      }
      else if (next[b] == "Z") {
        getDisplay()->fillRectangle(120*b, 290, 10, 10, map["Z"]);
        getDisplay()->fillRectangle(120*b + 10, 290, 10, 10, map["Z"]);
        getDisplay()->fillRectangle(120*b + 10, 300, 10, 10, map["Z"]);
        getDisplay()->fillRectangle(120*b + 20, 300, 10, 10, map["Z"]);
      }
    }
  }

  // rendering hold block
  if (subject->isBonus()) { 
    for (int b = 0; b < length; b++) {
      if (b == player) {
      getDisplay()->fillRectangle(120*b, 290 + OFFSET, 40, 20, Xwindow::White);
      }
      if (b == (player - 1) % length || (player == 0 && b == (length - 1))) {
        getDisplay()->fillRectangle(120*b, 290 + OFFSET, 40, 20, Xwindow::White);
      }
      getDisplay()->drawString(15 + b * 120, 280 + OFFSET, "Hold:");
      if (b == player) {
        if (holds[b] == "I") {
          for (int i = 0; i < 4; i++) {
            getDisplay()->fillRectangle(120*b + i*10, 290 + OFFSET, 10, 10, map["I"]);
          }
        }
        else if (holds[b] == "O") {
          getDisplay()->fillRectangle(120*b, 290 + OFFSET, 10, 10, map["O"]);
          getDisplay()->fillRectangle(120*b + 10, 290 + OFFSET, 10, 10, map["O"]);
          getDisplay()->fillRectangle(120*b, 300 + OFFSET, 10, 10, map["O"]);
          getDisplay()->fillRectangle(120*b + 10, 300 + OFFSET, 10, 10, map["O"]);
        }
        else if (holds[b] == "J") {
          getDisplay()->fillRectangle(120*b, 290 + OFFSET, 10, 10, map["J"]);
          getDisplay()->fillRectangle(120*b, 300 + OFFSET, 10, 10, map["J"]);
          getDisplay()->fillRectangle(120*b + 10, 300 + OFFSET, 10, 10, map["J"]);
          getDisplay()->fillRectangle(120*b + 20, 300 + OFFSET, 10, 10, map["J"]);
        }
        else if (holds[b] == "L") {
          getDisplay()->fillRectangle(120*b + 20, 290 + OFFSET, 10, 10, map["L"]);
          getDisplay()->fillRectangle(120*b, 300 + OFFSET, 10, 10, map["L"]);
          getDisplay()->fillRectangle(120*b + 10, 300 + OFFSET, 10, 10, map["L"]);
          getDisplay()->fillRectangle(120*b + 20, 300 + OFFSET, 10, 10, map["L"]);
        }
        else if (holds[b] == "T") {
          getDisplay()->fillRectangle(120*b , 290 + OFFSET, 10, 10, map["T"]);
          getDisplay()->fillRectangle(120*b + 10, 290 + OFFSET, 10, 10, map["T"]);
          getDisplay()->fillRectangle(120*b + 20, 290 + OFFSET, 10, 10, map["T"]);
          getDisplay()->fillRectangle(120*b + 10, 300 + OFFSET, 10, 10, map["T"]);
        }
        else if (holds[b] == "S") {
          getDisplay()->fillRectangle(120*b + 10, 290 + OFFSET, 10, 10, map["S"]);
          getDisplay()->fillRectangle(120*b + 20, 290 + OFFSET, 10, 10, map["S"]);
          getDisplay()->fillRectangle(120*b, 300 + OFFSET, 10, 10, map["S"]);
          getDisplay()->fillRectangle(120*b + 10, 300 + OFFSET, 10, 10, map["S"]);
        }
        else if (holds[b] == "Z") {
          getDisplay()->fillRectangle(120*b, 290 + OFFSET, 10, 10, map["Z"]);
          getDisplay()->fillRectangle(120*b + 10, 290 + OFFSET, 10, 10, map["Z"]);
          getDisplay()->fillRectangle(120*b + 10, 300 + OFFSET, 10, 10, map["Z"]);
          getDisplay()->fillRectangle(120*b + 20, 300 + OFFSET, 10, 10, map["Z"]);
        }
      }
    }
  }
  
}

// dtor
GraphicalObserver::~GraphicalObserver() {
  // detaching the observer from the subject
  subject->detach(this);
}
