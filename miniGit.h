#pragma once

#include <iostream>
#include <filesystem>
using namespace std;

struct singlyNode {
  string     fileName; // Name of local file
  string     fileVersion; // Name of file in .minigit folder
  singlyNode *next;
};

struct doublyNode {
  int        commitNumber;
  singlyNode *SLL_head;
  doublyNode *previous;
  doublyNode *next;
};

class miniGit {
 public:
  miniGit();
  virtual ~miniGit();
  void add();
  void remove();
  void commit();
  void checkout();

 private:
  doublyNode *DLL_head; // Pointer to the DLL_head of the doubly linked list
};

