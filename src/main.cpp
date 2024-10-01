#include <iostream>
#include "parser.h"
#include "executor.h"
#include "signals.h"
#include "builtins.h"

#include <readline/readline.h>
#include <readline/history.h>

int main() {
    setup_signal_handlers();

    char* input;
    while (true) {
        input = readline("shell> ");
        if (!input) {
            // end of input
            std::cout << "\n";
            break;
        }

        // add non-empty inputs to history w readline
        if (*input) {
            add_history(input);
        }

        std::string input_str(input);
        free(input); // free memory

        if (input_str.empty()) continue;

        auto commands = parse_input(input_str);
        if (commands.empty()) continue;

        // If there's only one command, check for built-ins
        if (commands.size() == 1 && execute_builtin(commands[0].args)) {
            continue;
        }

        execute_commands(commands);
    }

    return 0;
}
