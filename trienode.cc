#include "trienode.h"

#include <iostream>

using namespace std;

const int NUM_CHARS = 52;

TrieNode::TrieNode(): isWord{false}, letters(NUM_CHARS) {}

// helper function
void TrieNode::insertHelp(const string &word, int index) {
  if (index == word.length()) {
    isWord = true;  // we're at the end of the word
    return;
  }

  int letterIndex = tolower(word[index]) - 'a';  // convert to lowercase
  if (word[index] >= 'A' && word[index] <= 'Z') {
    letterIndex = word[index] - 'A' + 26;  // if uppercase, adjust index
  }

  if (!letters[letterIndex]) {
    letters[letterIndex] = std::make_unique<TrieNode>();
  }

  letters[letterIndex]->insertHelp(word, index + 1);  // Recursive call
}

// insert function
void TrieNode::insert(const string &word) {
  insertHelp(word, 0);
}

pair<vector<string>, int> TrieNode::find(const string &word) const {
  const TrieNode *node = this;
  if (!node) { 
    return {{}, 0};
  }
  for (char c : word) {
    if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z')) {
      return {{}, 0};
    }
    int index = tolower(c) - 'a';  // convert to lowercase
    if (c >= 'A' && c <= 'Z') {
      index = c - 'A' + 26;  // if uppercase, adjust index
    }
    if (!node->letters[index]) {
      return {{}, 0};  
    }
    node = node->letters[index].get();
  }
  return findWords(node, word);
}

// recursive helper function to find all the words in a Trie
pair<vector<string>, int> TrieNode::findWords(const TrieNode* node, string prefix) const {
  vector<string> foundWords;
  if (!node) {  
    return {foundWords, 0};
  }
  if (node->isWord) {
    foundWords.emplace_back(prefix);
  }
  for (int i = 0; i < NUM_CHARS; ++i) {
    if (node->letters[i]) {
      char c = 'a' + i;
      string newPrefix = prefix + c;
      auto result = findWords(node->letters[i].get(), newPrefix);
      foundWords.insert(foundWords.end(), result.first.begin(), result.first.end());
    }
  }
  return {foundWords, static_cast<int>(foundWords.size())};
}
