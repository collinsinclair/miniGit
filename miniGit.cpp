//
// Created by Collin Sinclair on 4/15/21.
//

#include "miniGit.h"
miniGit::miniGit() {}
miniGit::~miniGit() {

}
void miniGit::add() {
  // prompt user to enter a file name

  // check whether the file with the given name exists in the current directory.
  // If not, keep prompting the user to enter a valid file name.

  // The SLL is checked to see whether the file has already been added.
  // A file by the same name cannot be added twice.

  // A new SLL node gets added containing the name of the input file, name of the repository file,
  // as well as a pointer to the next node.
  // The repository file name should be the combination of the original file name and the version number.
}
void miniGit::remove() {
  // Prompt the user to enter a file name.

  // Check the SLL for whether the file exists in the current version of the repository.

  // If found, delete the SLL node.
}
void miniGit::commit() {
  // The current SLL should be traversed in its entirety, and for every node: see writeup

  // Once all the files have been scanned, the final step of the commit will create a new DLL node of the repo

}
void miniGit::checkout() {

}
