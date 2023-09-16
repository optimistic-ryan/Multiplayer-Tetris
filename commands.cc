#include <sstream>

#include "commands.h"

using namespace std;

Commands::Commands(Game &g) : g{g}, trie{make_unique<TrieNode>()} {
  trie->insert("left");
  trie->insert("right");
  trie->insert("down");
  trie->insert("clockwise");
  trie->insert("counterclockwise");
  trie->insert("drop");
  trie->insert("levelup");
  trie->insert("leveldown");
  trie->insert("norandom");
  trie->insert("random");
  trie->insert("sequence");
  trie->insert("I");
  trie->insert("J");
  trie->insert("L");
  trie->insert("Z");
  trie->insert("S");
  trie->insert("O");
  trie->insert("T");
  trie->insert("restart");

  if (g.isBonus()) {
    trie->insert("up");
    trie->insert("special");
    trie->insert("nuke");
    trie->insert("hold");
  }
}

void Commands::sendCommand(const string &message) { g.getCommand(message); }

void Commands::processCommands() {
  g.setPrevAlive(g.getAlive());
  string command;
  cin >> command;
  // Parse the multiplier prefix if present
  int multiplier = 0;
  int i = 0;
  bool flag = true;
  while (i < command.size() && isdigit(command[i])) {
    int increment = command[i] - '0';
    if (increment <= 0 && i == 0) {
      flag = false;
      break;
    }
    multiplier = multiplier * 10 + increment;
    ++i;
  }

  if (multiplier == 0 && flag) {
    multiplier = 1;
  } else if (!flag) {
    cout << "Unknown Mulitplier: " << command << endl;
    processCommands();
    return;
  }

  command = command.substr(i);
  // Find possible matches for the command in the trie
  auto matches = trie->find(command);

  // If there are multiple matches or no matches, it's an ambiguous or unknown
  // command
  if (matches.second != 1) {
    cout << "Unknown or ambiguous command: " << command << endl;
    processCommands();
    return;
  }

  // Execute the command.
  string matchedCommand = matches.first[0];

  if (matchedCommand != "restart") {
    g.setRestarted(false);
  }

  if (matchedCommand == "drop" && multiplier > 1) {
    for (int i = 0; i < multiplier - 1; ++i) {
      g.getCommand("consecutiveDrop");
    }
    g.getCommand("drop");
  } else {
    for (int i = 0; i < multiplier; ++i) {
      if (matchedCommand == "clockwise") {
        g.getCommand("clockwise");
      } else if (matchedCommand == "counterclockwise") {
        g.getCommand("counterclockwise");
      } else if (matchedCommand == "left") {
        g.getCommand("left");
      } else if (matchedCommand == "right") {
        g.getCommand("right");
      } else if (matchedCommand == "down") {
        g.getCommand("down");
      } else if (matchedCommand == "up") {
        g.getCommand("up");
      } else if (matchedCommand == "drop") {
        g.getCommand("drop");
      } else if (matchedCommand == "levelup") {
        g.getCommand("levelup");
      } else if (matchedCommand == "leveldown") {
        g.getCommand("leveldown");
      } else if (matchedCommand == "random") {
        g.getCommand("random");
      } else if (matchedCommand == "nuke") {
        g.getCommand("nuke");
      } else if (matchedCommand == "norandom") {
        string filename;
        if (cin >> filename) {
          g.noRandom(filename);
        } else {
          cout << "No filename specified for norandom command." << endl;
        }

      } else if (matchedCommand == "sequence") {
        string filename;
        if (cin >> filename) {
          g.sequence(filename);
        } else {
          cout << "No filename specified for sequence command." << endl;
        }

      } else if (matchedCommand == "special") {
        g.getCommand("special");
      } else if (matchedCommand == "I") {
        g.getCommand("I");
      } else if (matchedCommand == "J") {
        g.getCommand("J");
      } else if (matchedCommand == "L") {
        g.getCommand("L");
      } else if (matchedCommand == "O") {
        g.getCommand("O");
      } else if (matchedCommand == "S") {
        g.getCommand("S");
      } else if (matchedCommand == "Z") {
        g.getCommand("Z");
      } else if (matchedCommand == "T") {
        g.getCommand("T");
      } else if (matchedCommand == "restart") {
        g.restart();
      } else if (matchedCommand == "hold") {
        g.getCommand("hold");
      }
    }
  }
}
