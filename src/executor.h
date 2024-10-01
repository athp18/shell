#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "parser.h"
#include <string>
#include <vector>

void execute_commands(const std::vector<Command> &commands);

#endif