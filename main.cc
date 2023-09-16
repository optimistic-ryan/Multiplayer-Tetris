#include <iostream>
#include <memory>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <cstdlib>

#include "game.h"
#include "textobserver.h"

#include "graphicalobserver.h"
#include "window.h"

using namespace std;

int main(int argc, char* argv[]) {
    
    // creating the variables handled by the command line
    int level = 0;
    string seqfile1 = "";
    string seqfile2 = "";
    bool textOnly = false;
    int seed = time(0);
    bool bonus = false;
    
    // processing the command line args
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];

        // changing the startlevel
        if (arg == "startlevel") {
            if (i + 1 < argc) {
                istringstream iss{argv[i + 1]};
                iss >> level;
                i += 1;
            }
        }

        // processing the scriptfiles
        else if (arg == "scriptfile1") {
            if (i + 1 < argc) {
                seqfile1 = argv[i + 1];
                i += 1;
            }
        }
        else if (arg == "scriptfile2") {
            if (i + 1 < argc) {
                seqfile2 = argv[i + 1];
                i += 1;
            }
        }

        // processing the seed
        else if (arg == "seed") {
            if (i + 1 < argc) {
                istringstream iss{argv[i + 1]};
                iss >> seed;
                i += 1;
            }
        }

        // orocessing the text only var
        else if (arg == "text") {
            textOnly = true;
        } else if (arg == "enablebonus") {
            bonus = true;
        }
    }

    // default number of players
    int alive = 2;
    // reading in the number of players if bonus is enabled
    if (bonus) {
        while(1) {
            cout << "How many players? " << endl;
            string s;
            if (!(cin >> s)) {
                cin.clear();
                cin.ignore();
                cout << "Inalid input - please enter a number > 1: " << endl;
            }
            else {
                istringstream iss{s};
                if (iss >> alive) {
                    cout<<"reading in alive:"<<alive<<endl;
                    if (alive >= 2) {
                        if (alive >= 7) {
                            alive = 6;
                        }
                        break;
                    }
            
                }
                cout << "Invalid input - please enter a number > 1:";
            }
        }
    }

    // setting the ssed
    std::srand(seed);
    Game g{alive, seqfile1, seqfile2};  // creating game
    // setting the bonus and level variables
    g.setBonus(bonus);
    g.setLevel(level);


    Commands cmd{g};  // creating commands handler
    // making the text and graphical observerers
    shared_ptr<TextObserver> text = make_shared<TextObserver>(&g);
    shared_ptr<GraphicalObserver> graphical = nullptr;
    if (!textOnly) {
        graphical = make_shared<GraphicalObserver>(&g, 0, 100, 0, 100);
    }

    // playing the game
    while(g.getAlive() > 1) {
        g.render();
        cmd.processCommands();
    }

}