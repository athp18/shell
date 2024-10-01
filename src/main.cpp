#include <iostream>
#include "parser.h"
#include "executor.h"
#include "signals.h"
#include "builtins.h"

#include <readline/readline.h>
#include <readline/history.h>

/**
 * @brief Entry point of the shell program.
 *
 * The `main` function initializes the shell environment, sets up signal handlers,
 * and enters the main loop to continuously read and execute user commands.
 *
 * **Functionality:**
 * - **Signal Handling Setup:** Calls `setup_signal_handlers()` to handle signals like `SIGINT`.
 * - **Readline Integration:** Uses the `readline` library to read user input with line editing and history support.
 * - **Command History:** Adds non-empty inputs to the history for future recall.
 * - **Input Parsing:** Parses the user input into commands and arguments using `parse_input()`.
 * - **Built-in Commands Execution:**
 *   - Checks if the command is a built-in (e.g., `cd`, `exit`) and executes it via `execute_builtin()`.
 * - **External Commands Execution:**
 *   - If not a built-in, executes the command(s) using `execute_commands()`.
 * - **Loop Continuation and Termination:**
 *   - Continues the loop until an exit condition is met (e.g., user types `exit` or sends EOF).
 *
 * **Usage:**
 * Compile the shell program and run the executable. The shell will display a prompt (`shell> `),
 * and you can enter commands just like in a standard shell.
 *
 * @return Returns 0 upon successful execution.
 */

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
