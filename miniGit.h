//
// Created by Collin Sinclair on 4/15/21.
//

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

};

