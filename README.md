![C++ Badge](images/Language-C++-blue.svg) ![csci2270](images/Course-CSCI%202270-%23c5ab69.svg)

# miniGit

A Mini Version Control System

Authors: Collin Sinclair and Linnea Wolniewicz

Spring 2021 term project for CSCI 2270: Data Structures at the University of Colorado Boulder

This is a working miniature version control system. It creates a local repository, `.minigit`, and allows you to
interact directly with your repository through the terminal. You may add and remove files from your current working
directory, commit changes and checkout previous commits.

## Installation

After cloning the repository, compile the program with C++17 or later. (e.g.
type `g++ -std=c++17 driver.cpp miniGit.cpp -o miniGit` into a terminal that is set in the clone directory).

## Use

To run `miniGit`, use `./miniGit` (or any other name you chose at compile time). You will then be greeted by a menu of
options, where you can add or remove files in your current working directory, commit changes locally, and checkout older
file versions from previous commits. If you find a bug, enter debug mode with menu option `8127` for more detailed
information (you can subsequently leave debug mode with menu option `3850`).

### Initialization

When you first start the program with `./miniGit`, you will be prompted to initialize a repository.

- If this is your first time using `miniGit` in this directory, the program will create a hidden sub-folder
  called `.minigit` where it will put versioned files as you update and commit components of your repository.
- If you have used `miniGit` in this directory before, you will be prompted to choose between resetting the repository
  or exiting the program. **Warning:** if you choose to reset the repository, your previous versioned files (everything
  in the `./minigit` directory) will be permanently deleted.

Note: at this stage of development, `miniGit` does not function across uses. Once the program terminates, version
tracking stops and cannot be recovered.

### Add/Remove

Once the repository is initialized, you will be prompted to choose from several menu options.

- Menu option 1, "Add a file", will instruct `miniGit` to begin tracking files in your working directory or deeper. The
  same file cannot be added twice.
- Menu option 2, "Remove a file" will instruct `miniGit` to stop tracking files in your current working directory or
  deeper. Removing a file from `miniGit` will *not* modify or remove it from your working directory - it will simply
  stop being tracked by `miniGit`. A removed file can always be added again.

### Commit

After adding files to `miniGit` or modifying already-added files, you can choose to commit them with menu option 3. Upon
a commit, `miniGit` will check for any changes in your added files. If it finds changes, it will automatically assign an
updated version number to the changed files and save them to the `./minigit` directory. You may access any version of an
added file at any time manually by accessing the `./minigit` directory. Note: you may have to manually remove the
version number (`"_v##"`) from the file extension to open the file properly.

### Checkout

If you'd like to restore the files in your working directory to a previous version, use menu option 4 to check out a
previous commit. This will replace the files in your current working directory with copies of the same files as they
were when you submitted the specified commit. **Warning:** any uncommitted changes will be lost upon checkout - it is a
good idea to always commit your changes before checking out a previous commit if you wish to save your changes.

### Quit

Menu option 5 will exit `miniGit`. This will delete the repository structure and disable you from checking out previous
commits from within the program. Quitting `miniGit` does *not* erase and files in your working directory, nor does it
erase any versioned files from commits you made during use of the program. All version files will still be available in
the `./minigit` directory.

## Future and Feedback

In the future, we will consider adding additional functionality to `miniGit` such as branching, diff and status,
friendly checkouts, and more. If you find any bugs or have suggestions, please submit an
issue [here](https://github.com/collinsinclair/miniGit/issues). We are very proud of this project and hope you enjoy it
as well!
