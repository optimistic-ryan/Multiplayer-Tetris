#ifndef _OBSERVER_H_
#define _OBSERVER_H_

const int ROWS = 17;
const int COLS = 11;

// observer class
class Observer {
 public:
 // notify and dtor methods
  virtual void notify() = 0;
  virtual ~Observer() = default;
};
#endif
