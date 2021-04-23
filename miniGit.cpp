#include "miniGit.h"
#include<filesystem>
#include<iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

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

miniGit::~miniGit() = default;

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
  if (debug) cout << "DEBUG MSG: Creation of searchPtr successful." << endl;

  // base case - SLL hasn't been started yet
  if (searchPtr == nullptr) {
	if (debug) print("DEBUG MSG: searchPtr was null."); // ===DEBUG MSG===
	auto *toAdd = new singlyNode;
	toAdd->next        = nullptr;
	toAdd->fileName    = filename;
	toAdd->fileVersion = filename + "_v00";
	DLL_head->SLL_head = toAdd;
	print("Success: file added.");
  }

	// otherwise, search the list!
  else {
	// search through SLL
	if (debug) print("DEBUG MSG: searchPtr was not null. Searching SLL list."); // ===DEBUG MSG===
	while (searchPtr->next != nullptr and !file_added) {
	  if (searchPtr->fileName == filename) {
		file_added = true;
		cout << "File " << filename << " already added. The same file cannot be added twice." << endl << endl;
	  }
	  searchPtr = searchPtr->next;
	}

	// add the file as an SLL node
	if (!file_added) {
	  if (debug) print("DEBUG MSG: beginning node creation to add to SLL");
	  auto *toAdd = new singlyNode;
	  toAdd->next        = nullptr;
	  toAdd->fileName    = filename;
	  toAdd->fileVersion = filename + "_v00";
	  if (debug) print("DEBUG MSG: Populated fields, attempting to add to SLL.");
	  if (debug) cout << "DEBUG MSG: Current searchPtr file: " << searchPtr->fileName << endl;
	  searchPtr->next = toAdd;
	  if (debug) print("DEBUG MSG: Success: added new node to SLL.");
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
	  if (prev == nullptr) {
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

void copy(const string &origin_, const string &destination_) {
  ifstream origin(origin_, std::ios::binary);
  ofstream destination(destination_, std::ios::binary);
  destination << origin.rdbuf();
  origin.close();
  destination.close();
}

bool changed(const string &origin_, const string &destination_, bool debug) {
  ifstream      originFile(origin_, std::ios::binary);
  ifstream      destinationFile(destination_, std::ios::binary);
  ostringstream originString;
  ostringstream destinationString;
  originString << originFile.rdbuf();
  destinationString << destinationFile.rdbuf();
  if (debug) {
	cout << "DEBUG MSG: Original: ==========================================" << endl
		 << originString.str() << endl
		 << "==========================================" << endl;
	cout << "Destination: ==========================================" << endl
		 << destinationString.str() << endl
		 << "==========================================" << endl
		 << "File changed? " << not(originString.str() == destinationString.str());
  }
  return not(originString.str() == destinationString.str());
}

void miniGit::commit() {
  // traverse current SLL in its entirety

  // first find current DLL (most recent commit)
  doublyNode *currentCommit = DLL_head;
  while (currentCommit->next != nullptr)
	currentCommit = currentCommit->next;
  singlyNode *searchPtr = currentCommit->SLL_head;
  while (searchPtr != nullptr) {
	if (debug) cout << "DEBUG MSG: current node file: " << searchPtr->fileName << endl;
	string path   = ".minigit/" + searchPtr->fileVersion;
	// check whether the corresponding fileVersion file exists in .minigit directory
	bool   exists = std::filesystem::exists(path);
	// if the fileVersion file does not exist, copy the file from the current directory into the .minigit directory
	if (!exists) {
	  copy(searchPtr->fileName, path);
	  cout << "Commit successful: " << searchPtr->fileName << endl;
	}
	  // if the fileVersion file does exist in .minigit...
	else {
	  // check whether the current directory file has been changed with respect to the fileVersion file
	  if (not changed(searchPtr->fileName, path, debug)) {
		// file is unchanged: do nothing
		cout << "File unchanged: " << searchPtr->fileName << endl;
	  } else {
		// file is changed: copy the file from the current directory to the .minigit directory, and increment the
		// version number

		// this gets the last two characters from the fileVersion file, converts them to an int, increments them, and
		// turns them back into a string... sheesh!
		int versionNumber =
				stoi(searchPtr->fileVersion.substr(searchPtr->fileVersion.length() - 2));
		++versionNumber;
		string versionNumberString;
		// haven't written code for when version exceeds two characters - maybe later
		if (versionNumber > 99) {
		  cout << "Max space exceeded. Commit failed." << endl;
		  return;
		} else if (versionNumber < 10)
		  versionNumberString = "_v0" + to_string(versionNumber);
		else
		  versionNumberString = "_v" + to_string(versionNumber);
		string newVersionPath = ".minigit/" + searchPtr->fileName + versionNumberString;
		copy(searchPtr->fileName, newVersionPath);
		searchPtr->fileVersion = searchPtr->fileName + versionNumberString;
		cout << "File updated: " << searchPtr->fileName << endl;
	  }
	}
	searchPtr = searchPtr->next;
  }

  // once all the files have been scanned, create a new DLL node
  auto *newCommit = new doublyNode;
  currentCommit->next     = newCommit;
  newCommit->previous     = currentCommit;
  newCommit->commitNumber = currentCommit->commitNumber + 1;

  // deep copy SLL from currentCommit to newCommit
  auto *deepCopyNode = currentCommit->SLL_head;
  while(deepCopyNode != nullptr){
    deepCopyNode = deepCopyNode->next;
  }
}

void miniGit::checkout() {
  // Warn the user that they will lose their local changes
  cout << "Checking out a previous commit will overwrite any local changes that have not been commited." << endl;
  cout << "Are you sure you would like to continue? ([y]es/[n]o): " << endl;
  string choice = getChoice();

  if (choice == "y") {
    // Read in commit number to checkout
    cout << "Enter a commit number: ";
    string num;
    getline(cin, num);
    int commit = stoi(num);

    doublyNode* currentCommit = DLL_head;
    doublyNode* checkoutCommit;

    // Search through DLL for checkoutCommit and currentCommit
    while (currentCommit->next != nullptr) {
      // If checkout node is found, set it equal to checkoutCommit
      if (currentCommit->commitNumber == commit) {
        checkoutCommit = currentCommit;
      } else {
        currentCommit = currentCommit->next;
      }
    }

    // deep copy SLL from checkoutCommit to currentCommit
    auto *deepCopyNode = currentCommit->SLL_head;
    while(deepCopyNode != nullptr){
      deepCopyNode = deepCopyNode->next;
    }

    return;
  // Else, return
  } else {
    return;
  }
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
