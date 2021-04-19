#pragma once

#include <iostream>
using namespace std;

struct singlyNode {
  string     fileName; // Name of local file
  string     fileVersion; // Name of file in .minigit folder
  singlyNode *next;
};

struct doublyNode {
  int        commitNumber;
  singlyNode *head;
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
  doublyNode* head; // Pointer to the head of the doubly linked list
};

