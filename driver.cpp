//
// Created by Collin Sinclair on 4/15/21.
//

#include <iostream>
using namespace std;



void printMenu(); // prints user options
void print(const string &content);

int main() {
  bool quit = false;
  while (!quit) {
	int    option;
	string inputLine;

	printMenu();

	getline(cin, inputLine);

	if (inputLine.length() != 1 or inputLine[0] < '0' or inputLine[1] > '5') {
	  cerr << "Invalid option : " << inputLine << endl;
	  continue;
	}

	option = stoi(inputLine);

	switch (option) {

	  case 1: {
		break;
	  }
	  case 2: {
		break;
	  }
	  case 3: {
		break;
	  }
	  case 4: {
		break;
	  }

	  case 5: {
		quit = true;
		break;
	  }
	}
  }

  cout << "Goodbye!" << endl;

  return 0;
}

void printMenu() {
  print("======Main Menu======");
  print("1. Add file");
  print("2. Remove file");
  print("3. Commit");
  print("4. Checkout");
  print("5. Quit");
}

void print(const string &content) {
  cout << content << endl;
}