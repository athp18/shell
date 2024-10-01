#include "signals.h"
#include <iostream>
#include <readline/readline.h>
#include <signal.h>

/**
 * @brief Signal handler function for handling interrupt signals (e.g., Ctrl+C).
 *
 * The `handle_signal` function is called when a signal is received.
 * Specifically, it handles the `SIGINT` signal, which is typically generated
 * when the user presses `Ctrl+C` in the terminal. This function ensures that
 * the shell does not exit abruptly upon receiving `SIGINT`. Instead, it resets
 * the input line and redisplays the prompt, allowing the user to continue using
 * the shell.
 *
 * **Functionality:**
 * - Moves the cursor to a new line to avoid overwriting the current input.
 * - Resets the Readline internal state for the new line.
 * - Clears the current input line buffer.
 * - Redisplays the prompt and the (now empty) input line.
 *
 * @param signal The signal number received (e.g., `SIGINT`).
 */

void handle_signal(int signal) {
  if (signal == SIGINT) {
    // move to a new line
    std::cout << "\n";
    // reset prompt
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
  }
}

void setup_signal_handlers() {
  // tell readline to handle stuff itself
  rl_catch_signals = 0;
  signal(SIGINT, handle_signal);
}
