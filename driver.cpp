#include <iostream>
#include <vector>
#include "miniGit.hpp"
using namespace std;

void printMenu(); // prints user options
void print(const string &content);

int main() {

  miniGit::init();
  miniGit repo;

  bool quit = false;
  while (!quit) {
	int option;
	string inputLine;
	bool validChoice = false;

	printMenu();

	getline(cin, inputLine);

	while (!validChoice) {
	  try {
		option = stoi(inputLine);
		validChoice = true;

		// clear console for cleaner UX
		for (int i = 0; i < 100; ++i)
		  std::cout << "\n";
	  }

	  catch (...) {
		std::cerr << "Invalid choice. Enter a number: ";
		getline(cin, inputLine);
	  }
	}

	switch (option) {

	  case 1: {
		cout << "=== Add a file ===" << endl
			 << endl;
		repo.add();
		break;
	  }
	  case 2: {
		cout << "=== Remove a file ===" << endl
			 << endl;
		repo.remove();
		break;
	  }
	  case 3: {
		repo.commit();
		break;
	  }
	  case 4: {
		repo.checkout();
		break;
	  }

	  case 5: {
		quit = true;
		break;
	  }

	  case 8127: {
		repo.setDebug(true);
		print("Debug mode enabled.");
		break;
	  }

	  case 3850: {
		repo.setDebug(false);
		print("Debug mode disabled.");
		break;
	  }

	  default: {
		std::cerr << "Invalid choice. Enter a number specified by menu." << endl;
	  }
	}
  }

  cout << "Goodbye!" << endl;

  return 0;
}

void printMenu() {
  cout << endl;
  print("          miniGit         ");
  print("+================+=======+");
  print("|     To...      | Enter |");
  print("|----------------|-------|");
  print("| Add a file     |   1   |");
  print("| Remove a file  |   2   |");
  print("| Commit changes |   3   |");
  print("| Checkout       |   4   |");
  print("| Quit           |   5   |");
  print("+================+=======+");
  cout << "\nEnter a number: ";
}

//           miniGit
// +================+=======+
// |     To...      | Enter |
// |----------------|-------|
// | Add a file     |   1   |
// | Remove a file  |   2   |
// | Commit changes |   3   |
// | Checkout       |   4   |
// | Quit           |   5   |
// +================+=======+