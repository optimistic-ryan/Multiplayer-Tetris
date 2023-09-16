#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <utility>
#include <vector>

class Block {
    protected:
      std::vector<std::pair<int, int>> pixels; // the collection of the block pixels
      std::string type; 
      std::pair<int, int> pivot;
      int levelPlaced;
      int orientation;
      std::vector<std::vector<std::pair<int,int>>> rotations;
      std::pair<int,int> nullPixel; // an empty pixel
      void update(); // update the pixels
      
    public:
      Block(std::string type, int level);
      Block (const Block &other);
      void left(); // left 1
      void right(); // right 1
      void up(); // up 1
      void down(); // down 1
      void rotatec(); // rotate clockwise
      void rotatecc(); // counter c

      
      std::string blockType(); // return type of block
      bool empty(); // check if a block is completely cleared
      int getLevel(); // return level of the block get dropped
      void clearLine(int line); // clear line and move down pixels above the line
      void setPixel(int x, int y);
      std::vector<std::pair<int, int>> getPixels();
      std::pair<int, int> getPivot();
    
      
};      

#endif