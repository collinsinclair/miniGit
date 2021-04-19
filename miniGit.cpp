#include "miniGit.h"
miniGit::miniGit() {}
miniGit::~miniGit() {}

// TODO Collin
void miniGit::add() {
  // prompt user to enter a file name
  cout << "Enter a file name: ";
  string filename;
  getline(cin, filename);

  // TODO check whether the file with the given name exists in the current directory.
  // TODO If not, keep prompting the user to enter a valid file name.

  // TODO The SLL is checked to see whether the file has already been added.
  // A file by the same name cannot be added twice.

  // TODO A new SLL node gets added containing the name of the input file, name of the repository file,
  // as well as a pointer to the next node.
  // The repository file name should be the combination of the original file name and the version number.
}

// TODO Linnea
void miniGit::remove() {
  // Empty list
  if (head == nullptr) return; 
  
  // Read in filename to be removed
  cout << "Enter a file name: ";
  string filename;
  cin >> filename;

  singlyNode* curr = head->head;
  singlyNode* prev = nullptr;

  // Search for filename in the linked list; if found, delete it
  while (curr != nullptr) {
    if (curr->fileName == filename) {
      prev->next = curr->next;
      delete curr;
      curr = nullptr;
    } else {
      prev = curr;
      curr = curr->next;
    }
  }

  return;
}

void miniGit::commit() {
  // TODO The current SLL should be traversed in its entirety, and for every node: see writeup

  // TODO Once all the files have been scanned, the final step of the commit will create a new DLL node of the repo

}

void miniGit::checkout() {
  // TODO issue a warning to the user that they will loose their local changes if they checkout a different version before making a commit with their current local changes

  // TODO This step will require a search through the DLL for a node with matching commit number

  // TODO must disallow add, remove, and commit operations when the current version is different from the most recent commit (the last DLL node)
}