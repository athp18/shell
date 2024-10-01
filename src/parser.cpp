#include "parser.h"
#include <sstream>
#include <algorithm>

std::vector<Command> parse_input(const std::string& input) {
    std::vector<Command> commands;

    // split the input by '|'
    // this is useful for concatenating inputs
    std::istringstream stream(input);
    std::string segment;
    while (std::getline(stream, segment, '|')) {
        Command cmd;
        std::istringstream cmd_stream(segment);
        std::string arg;
        while (cmd_stream >> arg) {
            cmd.args.push_back(arg);
        }
        commands.push_back(cmd);
    }

    return commands;
}