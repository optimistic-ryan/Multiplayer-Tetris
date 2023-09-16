#include "textobserver.h"
#include <vector>

using namespace std;

// ctor
TextObserver::TextObserver(Game *subject): subject{subject} 
{
  // attaching the observer to the subject
  subject->attach(this);
}

// render function for rendering blocks in the next section
string TextObserver::render(string type, int line) {
  // rendering the updated state to the ostream
  if (type == "I" && line == 0) {
    return "IIII       ";
  } else if (type == "O") {
    return "OO         ";
  } else if (type == "T") {
    if (line == 0) {
      return "TTT        ";
    } else if (line == 1) {
      return " T         ";
    }
  } else if (type == "S") {
    if (line == 0) {
      return " SS        ";
    } else if (line == 1) {
      return "SS         ";
    }
  } else if (type == "Z") {
    if (line == 0) {
      return "ZZ         ";
    } else if (line == 1) {
      return " ZZ        ";
    }
  } else if (type == "J") {
    if (line == 0) {
      return "J          ";
    } else if (line == 1) {
      return "JJJ        ";
    }
  } else if (type == "L") {
    if (line == 0) {
      return "  L        ";
    } else if (line == 1) {
      return "LLL        ";
    }
  }else{
    return "           ";
  }
  return "\n";
}

// notify method
void TextObserver::notify() {
  // spacing between the boards
  string spacing = "     ";

  int length = subject->getAlive();

  // rendering level
  vector<int> levels = subject->getLevels();

  out << endl;

  // displaying the level
  for (int i = 0; i < length; i++) {
    out << "Level:" << setw(5) << levels[i];
    if (i != length - 1) {
      out << spacing;
    }
  }
  out << endl;

  // displaying the score
  vector<int> scores = subject->getScores();

  for (int i = 0; i < length; i++) {
    out << "Score:" << setw(5) << scores[i];
    if (i != length - 1) {
      out << spacing;
    }
  }
  out << endl;

  // rendering a divider for each board
  for (int i = 0; i < length; i++) {
    for (int j = 0; j < COLS; j++) {
      out << "-";
    }
    if (i != length - 1) {
      out << spacing;
    }
  }
  out << endl;

  // displaying each player's board
  vector<Block*> blocks = subject->getBlocks();
  vector<bool> blinds = subject->getBlinds();

  for (int r = ROWS; r >= 0; r--) {
    for (int b = 0; b < length; b++) {
      for (int c = 0; c < COLS; c++) {
        // displaying ? if blind
        if (blinds[b] && r >= 3 && r <= 12 && c >= 3 && c <= 9) {
          out << "?";
        }
        // checking if the current block has a pixel at the position
        else if ((blocks[b]->getPixels())[0].first == c && blocks[b]->getPixels()[0].second == r) {
          out << blocks[b]->blockType();
        }
        else if (blocks[b]->getPixels()[1].first == c && blocks[b]->getPixels()[1].second == r) {
          out << blocks[b]->blockType();
        }
        else if (blocks[b]->getPixels()[2].first == c && blocks[b]->getPixels()[2].second == r) {
          out << blocks[b]->blockType();
        }
        else if (blocks[b]->getPixels()[3].first == c && blocks[b]->getPixels()[3].second == r) {
          out << blocks[b]->blockType();
        }
        // displaying empty spaces for the top three rows
        else if (r >= 15) {
          out << " ";
        }
        // displaying the state for the board
        else {
          out << subject->getState(r, c)[b];
        }
      }
      
      if (b != length - 1) {
        out << spacing;
      }
    }
    out << endl;
  }

  // rendering line
  for (int i = 0; i < length; i++) {
    for (int j = 0; j < COLS; j++) {
      out << "-";
    }
    if (i != length - 1) {
      out << spacing;
    }
  }
  out << endl;

  // rendering next block
  vector<string> next = subject->getNext();
  // rendering holds block
  vector<string> holds = subject->getHold();
  int player = subject->getPlayer();
  string next_space = "           ";
  
  // Displaying the next block
  for (int i = 0; i < length; i++) {
    out << "Next:" << setw(COLS);
    if (i != length - 1) {
      out << "        ";
    }
  }
  out << endl;
  
  // displaying the first line of the next block
  for (int i = 0; i < length; i++) {
    if (i == player) {
      out << render(next[i], 0);
    } else {
      out << next_space;
    }
    out << spacing;
  }
  out << endl;

  // displaying the second line of the next block
  for (int i = 0; i < length; i++) {
    if (i == player) {
      out << render(next[i], 1);
    } else {
      out << next_space;
    }
    out << spacing;
  }
  out << endl;

// if bonus is enable, displaying the hold blocks
if (subject->isBonus()) {
  for (int i = 0; i < length; i++) {
    out << "Hold:" << setw(COLS);
    if (i != length - 1) {
      out << "        ";
    }
  }
  out << endl;
  
  // displaying the first line of the hold block
  for (int i = 0; i < length; i++) {
    if (i == player) {
      out << render(holds[i], 0);
    } else {
      out << next_space;
    }
    out << spacing;
  }
  out << endl;

  // displaying the second line of the hold block
  for (int i = 0; i < length; i++) {
    if (i == player) {
      out << render(holds[i], 1);
    } else {
      out << next_space;
    }
    out << spacing;
  }
  out << endl;
}
    
  for (int b = 0; b < length; b++) {
    for (int c = 0; c < COLS; c++) {
      if (c == 0 && b == player) {
        out << "^";
      } else {
        out << " ";
      }
    }
    out << spacing;
  }
  out << endl;


}

// dtor
TextObserver::~TextObserver() {
  // detaching the observer from the subject
  subject->detach(this);
}
