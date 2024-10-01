#include "builtins.h"
#include <unistd.h>
#include <iostream>

/**
 * @brief Executes built-in shell commands if they match.
 *
 * This function checks if the first argument corresponds to a built-in command
 * and executes it if found. Currently supports 'cd' and 'exit' commands.
 *
 * - **cd**: Changes the current working directory.
 *   - Usage: `cd <directory>`
 *   - If no directory is provided, it outputs an error message.
 * - **exit**: Exits the shell.
 *
 * @param args A vector of strings containing the command and its arguments.
 * @return True if a built-in command was executed, false otherwise.
 */

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