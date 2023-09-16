#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <string>

class Observer;
class Block;

class Subject {
  std::vector<Observer*> observers;
 public:
  void attach(Observer *o);
  void detach(Observer *o);
  void notifyObservers();
  virtual std::vector<std::string> getGraphicalState(int row, int col) const = 0;
  virtual std::vector<std::string> getPrevState(int row, int col) const = 0;
  virtual std::vector<std::string> getState(int row, int col) const = 0;
  virtual std::vector<int> getScores() const = 0;
  virtual std::vector<int> getMaxScores() const = 0;
  virtual std::vector<int> getLevels() const = 0;
  virtual std::vector<std::string> getNext() const = 0;
  virtual std::vector<std::string> getHold() const = 0;
  virtual std::vector<bool> getBlinds() const = 0;
  virtual std::vector<Block*> getBlocks() const = 0;  //UNCOMMENTED 
  virtual bool getRestarted() const = 0;
  virtual int getPlayer() const = 0;
  virtual int getinitialBoards() const = 0;
  virtual int getAlive() const = 0;
  virtual int getPrevAlive() const = 0;
  virtual ~Subject() = default;
};

#endif
