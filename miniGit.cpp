#include "miniGit.h"
#include<filesystem>
#include<iostream>
#include <cstdlib>

// ---------- HELPERS ----------
string getChoice() {
  string choice;
  getline(cin, choice);
  while (!(choice == "y" or choice == "n")) {
	cout << R"(Invalid choice. Type "y" for yes or "n" for no: )";
	getline(cin, choice);
  }
  return choice;
}

void print(const string &content) {
  cout << content << endl;
}
//------------------------------

miniGit::miniGit() {
  auto *default_DLL_head = new doublyNode;
  default_DLL_head->commitNumber = 0;
  default_DLL_head->SLL_head     = nullptr;
  default_DLL_head->next         = nullptr;
  default_DLL_head->previous     = nullptr;
  DLL_head = default_DLL_head;
  debug    = false;
}

miniGit::~miniGit() {}

void miniGit::add() {
  // prompt user to enter a file name
  cout << "Enter a file name: ";
  string filename;
  getline(cin, filename);

  // check that is exists
  while (!std::filesystem::exists(filename)) {
	cout << "File not found. Enter a valid filename: ";
	getline(cin, filename);
  }

  // see if file has already been added
  bool       file_added = false;
  singlyNode *searchPtr = DLL_head->SLL_head;

  // base case - SLL hasn't been started yet
  if (searchPtr == nullptr) {
	if (debug) print("DEBUG MSG: searchPtr was null.\n"); // ===DEBUG MSG===
	auto *toAdd = new singlyNode;
	toAdd->next        = nullptr;
	toAdd->fileName    = filename;
	toAdd->fileVersion = filename + "_v00";
	DLL_head->SLL_head = toAdd;
	print("Success: file added.\n");
	if (debug) cout << "DEBUG MSG: Filename: " << toAdd->fileName << endl << endl; // ===DEBUG MSG===
  }

	// otherwise, search the list!
  else {
	// search through SLL
	if (debug) print("DEBUG MSG: searchPtr was not null. Searching SLL list.\n"); // ===DEBUG MSG===
	while (searchPtr != nullptr and !file_added) {
	  if (debug) cout << "DEBUG MSG: " << searchPtr->fileName << endl << endl; // ===DEBUG MSG===
	  if (searchPtr->fileName == filename) {
		file_added = true;
		cout << "File " << filename << " already added. The same file cannot be added twice." << endl << endl;
	  }
	  searchPtr = searchPtr->next;
	}

	// add the file as an SLL node
	if (!file_added) {
	  auto *toAdd = new singlyNode;
	  toAdd->next        = nullptr;
	  toAdd->fileName    = filename;
	  toAdd->fileVersion = filename + "_v00";
	  searchPtr->next    = toAdd;
	  print("Success: file added.\n");
	}
  }
}

void miniGit::remove() {
  // Empty list
  if (DLL_head == nullptr) return;

  // Read in filename to be removed
  cout << "Enter a file name: ";
  string filename;
  getline(cin, filename);

  singlyNode *curr = DLL_head->SLL_head;
  singlyNode *prev = nullptr;

  // Search for filename in the linked list; if found, delete it
  while (curr != nullptr) {
    if (curr->fileName == filename) {
      // Delete head node
      if (prev == 0) {
        DLL_head->SLL_head = (DLL_head->SLL_head)->next;
        delete curr;
        curr = nullptr;
        cout << "Success: file deleted." << endl;
        return;
      // Delete middle or end node
      } else {
        prev->next = curr->next;
        delete curr;
        curr = nullptr;
        cout << "Success: file deleted." << endl;
        return;
      }
      // Move to next node
    } else {
      prev = curr;
      curr = curr->next;
    }
  }
  cout << "File does not exist." << endl;
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

void miniGit::init() {
  // check if directory is a repo already
  bool is_repo = std::filesystem::exists(".minigit");

  // if cwd is a repo, ask user if they want to overwrite
  // TODO right now, I'm only giving the option to overwrite or quit, but perhaps we could
  // add a "load repo" functionality later? tbd
  if (is_repo) {
	cout << "Current directory is already a repository. Overwrite? ([y]es/[n]o): ";
	string choice = getChoice();
	if (choice == "y") {
	  std::filesystem::remove_all(".minigit");
	  std::filesystem::create_directory(".minigit");
	} else
	  std::exit(0); // terminates program normally
  }

	// if there isn't a repo in cwd, ask user if they want to make one
  else {
	cout << "Initialize an empty repository in the current directory? ([y]es/[n]o): ";
	string choice = getChoice();
	if (choice == "y") {
	  std::filesystem::remove_all(".minigit");
	  std::filesystem::create_directory(".minigit");
	} else
	  std::exit(0); // terminates program normally
  }
}
void miniGit::setDebug(bool setting) {
  debug = setting;
}
