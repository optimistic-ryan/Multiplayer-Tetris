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
  
  // Helper function to find all the words in a Trie
  std::pair<std::vector<std::string>, int> findWords(const TrieNode* node, std::string prefix) const;
  
  // Helper function to insert word in this node if it does not already exist.
  void insertHelp(const std::string &word, int index);

 public:
  // Initializes an "empty" node. size = 1 (only root node), words = 0, isWord = false.
  // Creates array of NUM_CHARS TrieNode pointers, each set to nullptr.
  TrieNode();
  
  ~TrieNode() = default;

  // Inserts word in this node if it does not already exist.
  void insert(const std::string &word);

  // Returns all of the autocompletions for the specified string.
  // If there is more than one, each is separated by a single space.
  // If there are none, an empty string is returned.
  std::pair<std::vector<std::string>, int> find(const std::string &word) const;
};

#endif
