#include "Block.h"
#include <iostream>

using namespace std;
Block::Block(std::string type, int level) : type{type}, levelPlaced{level} {

  pivot = {0, 14};
  nullPixel = {-1, -1};
  orientation = 0;
  pixels = {nullPixel, nullPixel, nullPixel, nullPixel};
  if (type == "I") {
    rotations = {{{0, 0}, {1, 0}, {2, 0}, {3, 0}},
                 {{0, 0}, {0, 1}, {0, 2}, {0, 3}},
                 {{0, 0 }, {1, 0}, {2, 0}, {3, 0}},
                 {{0, 0}, {0, 1}, {0, 2}, {0, 3}}};
    update();
  } else if (type == "J") {
    rotations = {{{0, 0}, {0, 1}, {1, 0}, {2, 0}},
                 {{0, 0}, {0, 1}, {0, 2}, {1, 2}},
                 {{0, 1}, {1, 1}, {2, 1}, {2, 0}},
                 {{0, 0}, {1, 0}, {1, 1}, {1, 2}}};
    update();
  } else if (type == "L") {
    rotations = {{{0, 0}, {1, 0}, {2, 0}, {2, 1}},
                 {{0, 0}, {0, 1}, {1, 0}, {0, 2}},
                 {{0, 0}, {0, 1}, {1, 1}, {2, 1}},
                 {{1, 0}, {1, 1}, {1, 2}, {0, 2}}};
    update();
  } else if (type == "O") {
    rotations = {{{0, 0}, {1, 0}, {0, 1}, {1, 1}},
                 {{0, 0}, {1, 0}, {0, 1}, {1, 1}},
                 {{0, 0}, {1, 0}, {0, 1}, {1, 1}},
                 {{0, 0}, {1, 0}, {0, 1}, {1, 1}}};
    update();
  } else if (type == "S") {
    rotations = {{{0, 0}, {1, 0}, {1, 1}, {2, 1}},
                 {{1, 0}, {1, 1}, {0, 1}, {0, 2}},
                 {{0, 0}, {1, 0}, {1, 1}, {2, 1}},
                 {{1, 0}, {1, 1}, {0, 1}, {0, 2}}};
    update();
  } else if (type == "T") {
    rotations = {{{0, 1}, {1, 1}, {2, 1}, {1, 0}},
                 {{0, 1}, {1, 0}, {1, 1}, {1, 2}},
                 {{0, 0}, {1, 0}, {2, 0}, {1, 1}},
                 {{0, 0}, {0, 1}, {0, 2}, {1, 1}}};
    update();
  } else if (type == "Z") {
    rotations = {{{1, 0}, {0, 1}, {1, 1}, {2, 0}},
                 {{0, 0}, {0, 1}, {1, 1}, {1, 2}},
                 {{1, 0}, {0, 1}, {1, 1}, {2, 0}},
                 {{0, 0}, {0, 1}, {1, 1}, {1, 2}}};
    update();
  } else if (type == "#") {
    rotations = {{{0, 0}, {0, 0}, {0, 0}, {0, 0}},
                 {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
                 {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
                 {{0, 0}, {0, 0}, {0, 0}, {0, 0}}};
    update();
  }
  if (type == "*") {
    pivot.first = 5;
    pivot.second = 14;
    rotations = {{{0, 0}, {0, 0}, {0, 0}, {0, 0}},
                 {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
                 {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
                 {{0, 0}, {0, 0}, {0, 0}, {0, 0}}};

    pixels[0].first = 5;
    pixels[0].second = 14;
    pixels[1].first = 5;
    pixels[1].second = 14;
    pixels[2].first = 5;
    pixels[2].second = 14;
    pixels[3].first = 5;
    pixels[3].second = 14;
  }
}

Block::Block(const Block &other) {
  pivot = other.pivot;
  orientation = other.orientation;
  pixels = other.pixels;
}

void Block::left() {
  pivot.first--;
  Block::update();
}

void Block::right() {
  pivot.first++;
  Block::update();
}

void Block::down() {
  pivot.second--;
  Block::update();
}
void Block::up() {
  pivot.second++;
  Block::update();
}

// rotate the current block clockwise
void Block::rotatec() {
  orientation++;
  orientation = orientation % 4;
  Block::update();
}
// rotate the current block counterclockwise
void Block::rotatecc() {
  if (orientation == 0) {
    orientation = 3;

  } else {
    orientation--;
  }
  Block::update();
}

std::string Block::blockType() { return type; }

// check if all pixels are empty
bool Block::empty() {
  for (int n = 0; n < 4; n++) {
    if (pixels[n] != nullPixel) {
      return false;
    }
  }
  return true;
}

// return the level in which the block was placed
int Block::getLevel() { return levelPlaced; }

// update the block's 4 cordinates based on the orientation and the pivot
void Block::update() {
  for (int n = 0; n < 4; n++) {
    pixels[n].first = pivot.first + rotations[orientation][n].first;
    pixels[n].second = pivot.second + rotations[orientation][n].second;
  }
}

std::vector<std::pair<int, int>> Block::getPixels() { return pixels; }

std::pair<int, int> Block::getPivot() { return pivot; }

// clear the cordinates of the block that is on the given line and move down the coordinates above
void Block::clearLine(int line) {
  for (int n = 0; n < 4; n++) {
    if (pixels[n].second == line) {
      pixels[n] = nullPixel;
    } else {
      if (pixels[n].second > line) {
        // if the pixels is above the cleared line, move it done
        pixels[n].second--;
      }
    }
  }
}

void Block::setPixel(int x, int y) {
  pivot.first = x;
  pivot.second = y;
  update();
}
