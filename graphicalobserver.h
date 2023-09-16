#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <unordered_map>
#include "observer.h"
#include "window.h"
#include "subject.h"
#include "game.h"

const int DIM = 25;
const int OFFSET = 50;

// graphical observer class
class GraphicalObserver : public Observer {
    // pointer to Studio subject
    Game *subject;
    // position fields
    int top, bottom, left, right;
    // pointer to underlying display
    std::shared_ptr<Xwindow> display;

    void render(std::string type, int x, int y, int line);

    std::unordered_map<std::string, int> map;

  public:
  // ctor, dtor, notify, and getDisplay methods
    Xwindow *getDisplay() {return display.get();}
    GraphicalObserver(Game *subject, int top, int bottom, int left, int right);
    void notify();
    ~GraphicalObserver();
};

#endif
