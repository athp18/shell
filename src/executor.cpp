#include "executor.h"
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <vector>

/**
 * @brief Executes a sequence of commands connected via pipes.
 *
 * This function takes a vector of `Command` objects, each representing a command
 * with its arguments, and executes them in sequence, setting up pipes between
 * them if necessary. It handles the creation of child processes, setting up
 * standard input and output redirection via pipes, and waits for all child
 * processes to complete.
 *
 * **Functionality:**
 * - **Pipes Creation:** Creates `n-1` pipes for `n` commands to facilitate
 *   inter-process communication.
 * - **Process Forking:** Forks a new process for each command in the sequence.
 * - **Input/Output Redirection:**
 *   - For commands that are not the first, redirects `STDIN` to read from the previous pipe.
 *   - For commands that are not the last, redirects `STDOUT` to write to the current pipe.
 * - **Closing File Descriptors:** Closes all unnecessary file descriptors in both
 *   child and parent processes to prevent resource leaks.
 * - **Execution of Commands:** Uses `execvp` to execute each command with its arguments.
 * - **Process Synchronization:** Parent process waits for all child processes to finish execution.
 *
 * @param commands A vector of `Command` objects, each containing the arguments for a command.
 */

void execute_commands(const std::vector<Command>& commands) {
    size_t num_commands = commands.size();
    std::vector<int> pipes;

    // Create pipes
    for (size_t i = 0; i < num_commands - 1; ++i) {
        int fd[2];
        if (pipe(fd) == -1) {
            perror("pipe failed");
            return;
        }
        pipes.push_back(fd[0]); // read end
        pipes.push_back(fd[1]); //write end
    }

    for (size_t i = 0; i < num_commands; ++i) {
        pid_t pid = fork();

        if (pid == 0) {
            // Child process

            // If not the first command, set stdin to the previous pipe's read end
            if (i > 0) {
                if (dup2(pipes[(i - 1) * 2], STDIN_FILENO) == -1) {
                    perror("dup2 failed");
                    exit(EXIT_FAILURE);
                }
            }

            // If this is not the last command, 
            // set stdout to the current pipe's write end
            if (i < num_commands - 1) {
                if (dup2(pipes[i * 2 + 1], STDOUT_FILENO) == -1) {
                    perror("dup2 failed");
                    exit(EXIT_FAILURE);
                }
            }

            // Close all pipe 
            // fds in child
            for (size_t j = 0; j < pipes.size(); ++j) {
                close(pipes[j]);
            }

            // Convert args to char* array
            std::vector<char*> c_args;
            for (auto& arg : commands[i].args) {
                c_args.push_back(const_cast<char*>(arg.c_str()));
            }
            c_args.push_back(nullptr);

            execvp(c_args[0], c_args.data());
            perror("execvp failed");
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            // this mean the fork failed
            perror("fork failed");
            return;
        }
    }

    // Close all pipe
    // fds in parent
    for (size_t i = 0; i < pipes.size(); ++i) {
        close(pipes[i]);
    }

    // Wait for all 
    // child processes
    for (size_t i = 0; i < num_commands; ++i) {
        int status;
        wait(&status);
    }
}