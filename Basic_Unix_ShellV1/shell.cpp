#include "shell.h"
#include <readline/readline.h>
#include <vector>
#include <sys/wait.h>
#include <map>

using namespace std;

// global map variable to keep track of shell variables entered by set command
map<string, string> shellVars;

// get_command()
char* get_command(std::string prompt) {

  char* command = (char*) "";

  while (strcmp(command, "") == 0) {
    command = readline(prompt.c_str());
  }
  return command;
}

// help()
void help() {
    const char helpMsg[] =
  "\nHello!!! Welcome to the help menu!\n"
  "The following are a list of commands: \n"
  "\n**********************************************\n"
  "\n* man fork - displays manual for fork, for example"
  "\n* set PROMPT X- change the prompt icon ($ by default)"
  "\n* cd X- change directory to X "
  "\n* ls - list sources (files and folders in that directory)"
  "\n* make - will run the make file"
  "\n* echo X - prints X to the screen"
  "\n* who - users logged into the nextwork"
  "\n* whoami - display username"
  "\n* help - What is being displayed right now!!!\n"
  "\n**********************************************\n"
    ;
    std::cout << helpMsg;
}

// mySet()
void mySet(vector<const char*> tokens) {
    // if user enters something like "set SOMETHING", with nothing to set it to, just exit function
    if (tokens.size() < 3) { return; }
    string sVar(tokens[1]);
    string sValue(tokens[2]);
    // shellVars.insert({ sVar, sValue });
    shellVars[sVar] = sValue;
}

// myChangePrompt()
string myChangePrompt(vector<const char*> tokens) {
  string prompt = "";
  for (unsigned int i = 2; i < tokens.size(); i++) {
    prompt += tokens[i];
    if (i < tokens.size()) { prompt += " "; }
  }

// strip out any " (quote) characters in PROMPT string user entered (like project example)
  char* tmp0 = new char[ prompt.length()+1];
  char* tmp1 = new char[ prompt.length()+1];
  char* tmp11 = tmp1; // start of tmp1 character array
  strcpy(tmp0, prompt.c_str());
  while (*tmp0) { if (*tmp0 != '"') { *tmp1++ = *tmp0; } tmp0++; }
  *tmp1 = 0; // can't forget the terminating null!!!
  string sTmp(tmp11);
  prompt = sTmp;

  return (prompt);
}

// myExecutable()
void myExecutable(vector<const char*> tokens) {
  // execvp() wants its 2nd argument to be an array of char* (not a vector of char*)
  // so, create array of char* from our tokens vector:
  char* args[tokens.size() + 1]; int nTok = 0;
  for (unsigned int i = 0; i < tokens.size(); i++) {
    char* tok = new char[ sizeof(tokens[i]) ];
    strcpy(tok, tokens[i]);
    args[i] = tok;
    nTok++;
  }

  args[nTok] = NULL; // execvp() wants the the last element of the char*[] to be NULL
  // try to execute unrecognized user input:
  std::cout << "trying to execute: " << tokens[0] << "\n";
  cout << "============================================\n";

  pid_t pid = fork();
  if (pid < 0) { cout << "pid error" << endl; return; }
  // else if (pid == 0) {execlp("/bin/ls", "ls", NULL); }
  // else if (pid == 0) {execlp("/usr/bin/vim", "vim", "junk98", NULL); }
  else if (pid == 0) {
    // execvp(tokens[0], args);
    int ret = execvp(tokens[0], args);
    if (ret < 0) { cout << "execvp() returns error\n"; exit(1); }
  }
  else {
    wait(NULL);
    cout << "============================================\n";
    cout << "child complete\n";
  }
}

// myEcho()
void myEcho(vector<const char*> tokens) {

  if (tokens.size() > 1) {  // if user just typed "echo" we're done, except for sending the endline (falls thru to end of this function)
    // here we're checking to see if user wants to echo a shell variable
    // see if first character of what user wants to echo is a '$'
    if (*(tokens[1]) == '$') {
  // first character of token[1] IS a $, so treat this as trying to echo a shell variable
  // have to turn what user wants to echo into a string
  // so we can use it with map<string,string> variable we have
  string sVar(tokens[1]+1);

  // this is the way to use built-in map function
  // to find if we have inserted this shell variable with set
  auto it = shellVars.find(sVar);

  // if we did find this (it's token[1] where token[0]="echo")
  // then this is the way to ouput what that shell variable was set to
  // so then we're done so we return from this function
  if (it != shellVars.end()) { cout << it->second << endl; return; }
    }
  }

  // if we didn't already return from the shell variable stuff above, then just echo what user typed
  // which is all the tokens after token[0], which was "echo"
  for (unsigned int i = 1; i < tokens.size(); i++) { cout << tokens[i] << " "; }

  // always output at least a newline:
  std::cout << endl;
}

// cd()
void cd(const char* path) {
  errno = 0;
        // we'll need a char* for chdir(), or path.c_str()
  // std::cout << "cd " << path << std::endl;
  errno = chdir(path);
  if (errno != 0) { std::cout << "directory doesn't exist\n"; }
}

