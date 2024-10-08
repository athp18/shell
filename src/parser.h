#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

struct Command {
  std::vector<std::string> args;
};

std::vector<Command> parse_input(const std::string &input);

#endif