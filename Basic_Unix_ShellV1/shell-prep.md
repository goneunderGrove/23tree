## Introduction
The code is a basic Unix shell program that allows the user to enter commands to execute. It starts by defining functions for different commands, such as "myEcho" for printing input text, "myChangePrompt" for changing the command prompt, "mySet" for setting environment variables, and "myExecutable" for executing other commands using execvp(). The main function prompts the user for input, then tokenizes and parses the input to determine which command to execute. It also handles special cases, such as the "cd" command for changing the current working directory and the "help" command for displaying a help message. The program runs in an infinite loop until the user types "exit" or "quit".

# Starting a shell program

We want to:

1. take user input and execute multiple commands
2. provide help
3. provide a way to exit the program
4. implement `cd`  (using the **chdir()** system call)
5. implement a way to execute other programs by creating new processes

## Create a new project on thomas.butler.edu

If you've not used git before...

```bash
git config --global user.name "Firstname Lastname"
git config --global user.email "username@butler.edu"
```

and create a project directory...

```bash
mkdir -p ~/projects/os && cd ~/projects/os
git init .
```

## Start with shell.h

**shell.h**

```cpp
#include <errno.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h> // for chdir()

#ifndef SHELL_H
#define SHELL_H

char* get_command(std::string prompt);
void help();
void cd(std::string path);

#endif
```

## Begin the implementation in shell.cpp

**shell.cpp**

```cpp

#include "shell.h"

char* get_command(std::string prompt) {
  char* command;
  int n=0;
  errno = 0;

  while (1) {
    std::cout<< prompt << ": " << std::endl;
    fflush(stdout); // a newline normally flushes the stream

    n = scanf("%64m[^\n]", &command);
    getchar(); // newline remains in the stdin stream

    if (n == 1) {
      return command;
    }
    if (errno != 0) {
      perror("scanf");
    }
  }
  return "";
}

void help() {
    std::cout << "Some help." << std::endl;
}

void cd(std::string path) {
        // we'll need a char* for chdir(), or path.c_str()
	std::cout << "cd " << path << std::endl;
}

```

## update main.cpp

**main.cpp**

```cpp
#include <iostream>
#include <cstdlib>
#include <cstring>

#include "shell.h"

int main( int argc, char *argv[] ) {

    std::string prompt = "$";
    char* command;

    while (1) {
      command = get_command(prompt);

      if (strcmp("help", command) == 0) { help(); }
      else if (strcmp("quit", command) == 0 ||
               strcmp("exit", command) == 0) { exit(0); }
      else {
          std::cout << "READ: " << command << std::endl;
      }

      free(command);
    }

    return EXIT_SUCCESS;
}

```

## Create our Makefile

**Makefile**

```make
CPP      = g++
CPPFLAGS = -Wall -g
LDFLAGS  =
OBJFILES = main.o shell.o
TARGET   = main

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CPP) $(CPPFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~
```

## Make an initial git commit

create **.gitignore** to tell git to ignore files matching these patterns

```
a.out
main
*.o
```

Now, add our modified files and commit them

```
git add -A
git commit -m 'initial commit'
```

Finally, if you didn't already, rename the current branch **main**

```
git branch -m master main
```

We'll worry about pushing this to github later.

## revisiting fgets() and reading input

Reading line based input with scanf is a little tricky.  
Using fgets to read line-based input is better, but if 
we're updating code anyway another alternative is to use libreadline.

First, update the **Makefile** to read:

```make
LDFLAGS = -lreadline
```

then, update the **get_command()** function in **shell.c**

```cpp
#include <readline/readline.h>

char* command = (char*) "";

while (strcmp(command, "") == 0) { 
  command = readline(prompt.c_str());
}

return command;
```

## Implement `cd` using the chdir() syscall

- chdir() requires a char* path (the directory to change to)
- chdir() returns an integer (0 == success)
- see `man chdir` for more details

Update **shell.cpp** to complete the cd() function

```cpp
void cd(char* path) {
	errno = 0;

	// complete if/else here
}

```

## testing our function

In **main.cpp**, add a couple hard-coded calls to cd():

```cpp
cd("/nope"); // doesn't exists
cd("/tmp"); // should normally exist

```

## verifying our program uses a system call with `strace`

`strace` is the system call tracer.  We can use it to confirm that chdir() is called, e.g.

`strace -e trace=chdir ./main`

using `strace ./main` will, by default, show _all_ of the system calls a program makes.

Give it a try; Is it what you expected?

## stage and commit to github

This is a good time to commit work to the git repository if you haven't already.

```
git add main.cpp shell.h shell.cpp Makefile
git commit -m 'shell loop and input'
git push origin main
```
