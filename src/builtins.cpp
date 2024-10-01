#include "builtins.h"
#include <unistd.h>
#include <iostream>

bool execute_builtin(const std::vector<std::string>& args) {
    if (args[0] == "cd") {
        if (args.size() < 2) {
            std::cerr << "cd: expected argument\n";
        } else {
            if (chdir(args[1].c_str()) != 0) {
                perror("cd failed");
            }
        }
        return true;
    } else if (args[0] == "exit") {
        exit(0);
    }
    return false;
}