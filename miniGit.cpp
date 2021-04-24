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

void copy(const string &origin_, const string &destination_) {
  ifstream origin(origin_, std::ios::binary);
  ofstream destination(destination_, std::ios::binary);
  destination << origin.rdbuf();
  origin.close();
  destination.close();
}

bool changed(const string &origin_, const string &destination_, bool debug) {
  ifstream originFile(origin_, std::ios::binary);
  ifstream destinationFile(destination_, std::ios::binary);
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
		 << "DEBUG MSG: File changed? " << not(originString.str() == destinationString.str()) << endl;
  }
  return not(originString.str() == destinationString.str());
}

singlyNode *copySLLNode(singlyNode *node, bool debug) {
  if (node == nullptr)
	return nullptr;
  else {
	if (debug) print("DEBUG MSG: Copying node.");
	auto *SLLNode = new singlyNode;
	SLLNode->fileName = node->fileName;
	SLLNode->fileVersion = node->fileVersion;
	SLLNode->next = copySLLNode(node->next, debug);
	return SLLNode;
  }
}

void printSLL(singlyNode *node) {
  cout << "===== CURRENT SLL =====" << endl;
  while (node != nullptr) {
	cout << "FILENAME: " << node->fileName << endl;
	cout << "FILE VERSION: " << node->fileVersion << endl;
	node = node->next;
  }
  cout << "=======================" << endl;
}

void printStructure(doublyNode *node) {
  cout << "+++++===== CURRENT STRUCTURE =====+++++" << endl;
  while (node != nullptr) {
	cout << "Commit Number: " << node->commitNumber << endl;
	printSLL(node->SLL_head);
	node = node->next;
  }
  cout << "+++++=====%%%%%%%%%%%%%%%%%%%=====+++++" << endl;
}
//------------------------------

miniGit::miniGit() {
  auto *default_DLL_head = new doublyNode;
  default_DLL_head->commitNumber = 0;
  default_DLL_head->SLL_head = nullptr;
  default_DLL_head->next = nullptr;
  default_DLL_head->previous = nullptr;
  DLL_head = default_DLL_head;
  debug = false;
}

miniGit::~miniGit() = default;

void miniGit::add() {
  // prompt user to enter a file name
  cout << "Enter a file name: ";
  string filename;
  getline(cin, filename);

  // check that it exists
  while (!std::filesystem::exists(filename)) {
	cout << "File not found. Enter a valid filename: ";
	getline(cin, filename);
  }

  // see if file has already been added
  auto *currentDLL = DLL_head;
  while (currentDLL->next != nullptr)
	currentDLL = currentDLL->next;
  bool file_added = false;
  singlyNode *searchPtr = currentDLL->SLL_head;
  singlyNode *prev;
  if (debug) cout << "DEBUG MSG: Creation of searchPtr successful." << endl;

  // base case - SLL hasn't been started yet
  if (searchPtr == nullptr) {
	if (debug) print("DEBUG MSG: searchPtr was null."); // ===DEBUG MSG===
	auto *toAdd = new singlyNode;
	toAdd->next = nullptr;
	toAdd->fileName = filename;
	toAdd->fileVersion = filename + "_v00";
	currentDLL->SLL_head = toAdd;
	print("Success: file added.");
  }

	// otherwise, search the list!
  else {
	if (debug)
	  print("DEBUG MSG: searchPtr was not null. Searching SLL list."); // ===DEBUG MSG===

	// check for existence of node with filename
	while (searchPtr != nullptr and !file_added) {
	  if (searchPtr->fileName == filename) {
		if (debug) print("DEBUG MSG: Search filename: " + searchPtr->fileName);
		file_added = true;
		cout << "File " << filename << " already added. The same file cannot be added twice." << endl << endl;
	  }
	  prev = searchPtr;
	  searchPtr = searchPtr->next;
	}

	if (searchPtr == nullptr)
	  searchPtr = prev;

	// add the file as an SLL node
	if (!file_added) {
	  if (debug)
		print("DEBUG MSG: beginning node creation to add to SLL");
	  auto *toAdd = new singlyNode;
	  toAdd->next = nullptr;
	  toAdd->fileName = filename;
	  toAdd->fileVersion = filename + "_v00";
	  if (debug)
		print("DEBUG MSG: Populated fields, attempting to add to SLL.");
	  if (debug)
		cout << "DEBUG MSG: Current searchPtr file: " << searchPtr->fileName << endl;
	  searchPtr->next = toAdd;
	  if (debug)
		print("DEBUG MSG: Success: added new node to SLL.");
	  print("Success: file added.\n");
	}
  }

  if (debug) printStructure(DLL_head);
}

void miniGit::remove() {
  // Read in filename to be removed
  cout << "Enter a file name: ";
  string filename;
  getline(cin, filename);

  // first find current DLL (most recent commit)
  doublyNode *currentCommitDLL = DLL_head;
  if (debug) print("DEBUG MSG: Beginning search for current DLL.");
  while (currentCommitDLL->next != nullptr) {
	if (debug) cout << "DEBUG MSG: Current commit number: " << currentCommitDLL->commitNumber << endl;
	currentCommitDLL = currentCommitDLL->next;
	if (debug) cout << "DEBUG MSG: New commit number: " << currentCommitDLL->commitNumber << endl;
  }
  if (debug) print("DEBUG MSG: Search for current DLL complete.");

// Empty list
  if (currentCommitDLL == nullptr)
	return;

  singlyNode *curr = currentCommitDLL->SLL_head;
  singlyNode *prev = nullptr;

  // Search for filename in the linked list; if found, delete it
  while (curr != nullptr) {
	if (curr->fileName == filename) {
	  // Delete head node
	  if (prev == nullptr) {
		currentCommitDLL->SLL_head = (currentCommitDLL->SLL_head)->next;
		delete curr;
		cout << "Success: file deleted." << endl;
		return;
		// Delete middle or end node
	  } else {
		prev->next = curr->next;
		delete curr;
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
}

void miniGit::commit() {
  if (debug) print("DEBUG MSG: commit() called.");
  // first find current DLL (most recent commit)
  doublyNode *currentCommitDLL = DLL_head;
  if (debug) print("DEBUG MSG: Beginning search for current DLL.");
  while (currentCommitDLL->next != nullptr) {
	if (debug) cout << "DEBUG MSG: Current commit number: " << currentCommitDLL->commitNumber << endl;
	currentCommitDLL = currentCommitDLL->next;
	if (debug) cout << "DEBUG MSG: New commit number: " << currentCommitDLL->commitNumber << endl;
  }
  if (debug) print("DEBUG MSG: Search for current DLL complete.");

  // traverse current SLL in its entirety
  singlyNode *searchPtr = currentCommitDLL->SLL_head;
  while (searchPtr != nullptr) {
	string path = ".minigit/" + searchPtr->fileVersion;
	// check whether the corresponding fileVersion file exists in .minigit directory
	bool exists = std::filesystem::exists(path);
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
  currentCommitDLL->next = newCommit;
  newCommit->next = nullptr;
  newCommit->previous = currentCommitDLL;
  newCommit->commitNumber = currentCommitDLL->commitNumber + 1;
  newCommit->SLL_head = nullptr;
  cout << "Commit # " << currentCommitDLL->commitNumber << " is finished." << endl;
  // deep copy SLL from currentCommitDLL to newCommit
  newCommit->SLL_head = copySLLNode(currentCommitDLL->SLL_head, debug);

  if (debug) printStructure(DLL_head);
}

void miniGit::checkout() {
  // Warn the user that they will lose their local changes
  cout << "Checking out a previous commit will overwrite any local changes that have not been committed." << endl;
  cout << "Are you sure you would like to continue? ([y]es/[n]o): " << endl;
  string choice = getChoice();

  if (choice == "y") {
	// Read in commit number to checkout
	cout << "Enter a commit number: ";
	string num;
	getline(cin, num);
	int commit = stoi(num);
	printStructure(DLL_head);

	doublyNode *currentCommit = DLL_head;
	doublyNode *checkoutCommit;

	// Search through DLL for checkoutCommit and currentCommit
	while (currentCommit->next != nullptr) {
	  // If checkout node is found, set it equal to checkoutCommit
	  if (currentCommit->commitNumber == commit) {
		checkoutCommit = currentCommit;
	  }
	  currentCommit = currentCommit->next;
	}

	// Copy checkoutCommit SLL to currentCommit SLL
	singlyNode *curr = currentCommit->SLL_head;
	singlyNode *checkout = checkoutCommit->SLL_head;
	bool inCurrentExactly = false;
	bool inCurrentOldVersion = false;

	// Loop through checkoutCommit SLL
	while (checkout != nullptr) {
	  // For each checkout SLL node, loop through currentCommit SLL
	  while (curr != nullptr) {
		// If checkout is contained in currentCommit SLL, break out of the loop
		if (debug)
		  cout << "DEBUG MSG: checkout file version, current file version, checkout file name, current filename = "
			   << checkout->fileVersion << " , " << curr->fileVersion << "  , " << checkout->fileName << " , "
			   << curr->fileName << endl;
		if ((checkout->fileVersion == curr->fileVersion) && (checkout->fileName == curr->fileName)) {
		  inCurrentExactly = true;
		  if (debug) cout << "DEBUG MSG: inCurrentExactly: " << inCurrentExactly << endl;
		  break;
		} else if (checkout->fileName == curr->fileName) {
		  curr->fileVersion = checkout->fileVersion;
		  copy(".miniGit/" + checkout->fileVersion, checkout->fileName);
		  inCurrentOldVersion = true;
		  if (debug) cout << "DEBUG MSG: inCurrentOldVersion: " << inCurrentOldVersion << endl;
		  break;
		}
		curr = curr->next;
	  }

	  if (debug)
		cout << "DEBUG MSG: For file " << checkout->fileName << ", currentExactly, currentOld = " << inCurrentExactly
			 << " , " << inCurrentOldVersion << endl;


	  // If checkout isn't contained in currentCommit SLL, make tmp the new head
	  if (!inCurrentOldVersion && !inCurrentExactly) {
		auto *toAdd = new singlyNode;
		toAdd->fileName = checkout->fileName;
		toAdd->fileVersion = checkout->fileVersion;
		toAdd->next = currentCommit->SLL_head;
		copy(".miniGit/" + toAdd->fileVersion, toAdd->fileName);
		currentCommit->SLL_head = toAdd;
		cout << "Previous file (" << currentCommit->SLL_head->fileName << " from commit # " << commit
			 << " added to current repository." << endl;
	  }
	  printStructure(DLL_head);

	  checkout = checkout->next;
	  curr = currentCommit->SLL_head;
	  inCurrentExactly = false;
	  inCurrentOldVersion = false;
	}
	cout << "Checkout successful." << endl;
	return;
	// Else, return
  } else {
	cout << "No checkout made." << endl;
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
