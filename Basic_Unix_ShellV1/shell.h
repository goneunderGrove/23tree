#include <errno.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h> // for chdir()
#include <vector>

#ifndef SHELL_H
#define SHELL_H

char* get_command(std::string prompt);
void help();
void cd(const char* path);
#endif

