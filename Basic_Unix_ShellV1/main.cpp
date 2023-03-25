#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sstream> // for stringstream
#include <string>
#include <vector>
#include <unistd.h>

#include "shell.h"
using namespace std;

// function declarations
void myEcho(vector<const char*> tokens);
string myChangePrompt(vector<const char*> tokens);
void myExecutable(vector<const char*> tokens);
void mySet(vector<const char*> tokens);

#define MAX_PROMPT 100
#define MAX_COMMAND 1024

int main( int argc, char *argv[] ) {

  std::cout << "#   /$$   /$$ /$$   /$$ /$$$$$$ /$$   /$$        /$$$$$$  /$$   /$$ /$$$$$$$$ /$$       /$$      \n";
  std::cout << "#  | $$  | $$| $$$ | $$|_  $$_/| $$  / $$       /$$__  $$| $$  | $$| $$_____/| $$      | $$      \n";
  std::cout << "#  | $$  | $$| $$$$| $$  | $$  |  $$/ $$/      | $$  \\__/| $$  | $$| $$      | $$      | $$      \n";
  std::cout << "#  | $$  | $$| $$ $$ $$  | $$   \\  $$$$//      |  $$$$$$ | $$$$$$$$| $$$$$   | $$      | $$      \n";
  std::cout << "#  | $$  | $$| $$  $$$$  | $$    >$$  $$        \\____  $$| $$__  $$| $$__/   | $$      | $$      \n";
  std::cout << "#  | $$  | $$| $$\\  $$$  | $$   /$$/\\  $$       /$$  \\ $$| $$  | $$| $$      | $$      | $$      \n";
  std::cout << "#  |  $$$$$$/| $$ \\  $$ /$$$$$$| $$  \\ $$      |  $$$$$$/| $$  | $$| $$$$$$$$| $$$$$$$$| $$$$$$$$  \n";
  std::cout << "#   \\______/ |__/  \\__/|______/|__/  |__/       \\______/ |__/  |__/|________/|________/|________/  \n";

    std::string prompt = "$ ";
    // check to see if user typed more than program name:
    if (argc == 2) {
        // if user typed ./main --help then show help message and exit program:
        if (strcmp("--help", argv[1]) == 0) {
            help(); // display help message
            return (0);
        }
        // if there's a 2nd argument in argv[] and it wasn't "--help" then use it as the starting prompt
        string sTmp(argv[1]); prompt = sTmp + " ";
    }
    char* command = new char[MAX_COMMAND + 1];
    char curDir[MAX_PROMPT];

    while (1) { // start infinite loop
      command = get_command(prompt); // get user command
      string input(command);

      stringstream ss(input);
      string token;
      vector<const char*> tokens;

      while(getline(ss, token, ' ')) { // parse user command into individual tokens
        char* t = new char[ token.length() ];
        strcpy(t, token.c_str());
        tokens.push_back(t);
      }

      // if user just hits enter key (entering no text) then just start while(1) loop again:
      if (tokens.size() == 0) { continue; }

      // figure out which command was typed and do it:

      // help command:
      if (strcmp("help", tokens[0]) == 0) { help(); }

      // set command:
      else if (strcmp("set", tokens[0]) == 0) {
        // if user typed only "set" with nothing else then continue to bottom of loop
        if (tokens.size() < 2) { continue; }
        // (to here we know we have at least 2 tokens)

        // handle special case of setting PROMPT command for our shell
        if (strcmp("PROMPT", tokens[1]) == 0) {
            prompt = myChangePrompt(tokens); // change prompt based on user input
        }
        else {
            mySet(tokens); // perform set command based on user input
        }
      }

      // cd command:
      else if (strcmp("cd", tokens[0]) == 0) {
        if (tokens.size() != 2) {
            cout << "not enough arguments" << endl; // display error message if user input not correct
        }
        else {
            cd(tokens[1]); // change directory based on user input
        }
        if (getcwd(curDir, sizeof(curDir)) != NULL) {
            cout << "current directory = " << curDir << endl; // display current working directory
        }
        else {
            cout << "getcwd() returns error\n"; // display error message if getcwd() fails
        }
      }

      // echo command:
      else if (strcmp("echo", tokens[0]) == 0) {
        myEcho(tokens); // perform echo command based on user input
      }

      // exit/quit command:
      else if (strcmp("quit", tokens[0]) == 0 || strcmp("exit", tokens[0]) == 0) {
  exit(0);
      }

      // not a built-in command for this shell, so try to execute with execvp():
      else {
  myExecutable(tokens);
      }
    }

    return EXIT_SUCCESS;
}
