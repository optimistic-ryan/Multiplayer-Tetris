#ifndef TRIENODE_H
#define TRIENODE_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <utility>

class TrieNode {
  bool isWord;                                        // is this particular prefix a word itself?
  std::vector<std::unique_ptr<TrieNode>> letters;     // array of TrieNode pointers
  std::pair<std::vector<std::string>, int> findWords(const TrieNode* node, std::string prefix) const;
  void insertHelp(const std::string &word, int index);

 public:

  // initializes an "empty" node. size = 1 (only root node), words = 0, isWord = false
  // creates array of NUM_CHARS TrieNode pointers, each set to nullptr
  TrieNode();
  ~TrieNode() = default;
  void insert(const std::string &word);

  // returns all of the autocompletions for the specified string
  // if there is more than one, each is separated by a single space, else, an empty string is returned
  std::pair<std::vector<std::string>, int> find(const std::string &word) const;
};

#endif
