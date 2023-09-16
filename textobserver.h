#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H

#include <iostream>
#include <iomanip>

#include "observer.h"
#include "game.h"

// text observer class
class TextObserver : public Observer {
      // pointer to the Studio subject
      Game *subject;
      // ostream for rendering to stdout
      std::ostream &out = std::cout;

      std::string render(std::string type, int line);

      std::vector<std::string> names;

      void printSpace(int n);

    public:
    // ctor, dtor, and notify methods
    TextObserver(Game *subject);
    void notify();
    ~TextObserver();
};

#endif
