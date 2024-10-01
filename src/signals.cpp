// signals.cpp
#include "signals.h"
#include <signal.h>
#include <iostream>
#include <readline/readline.h>

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