#include "parser.h"
#include <algorithm>
#include <sstream>

/**
 * @brief Parses the user input into a sequence of commands with their
 * arguments.
 *
 * The `parse_input` function takes a raw input string from the user and
 * processes it to extract individual commands and their corresponding
 * arguments. It supports piped commands by splitting the input based on the `|`
 * character, allowing for the execution of commands connected via pipes (e.g.,
 * `ls -l | grep txt`).
 *
 * **Functionality:**
 * - **Input Splitting:**
 *   - Splits the input string into segments using the pipe `|` character as a
 * delimiter.
 *   - Each segment represents a command in the pipeline.
 * - **Argument Parsing:**
 *   - For each segment, splits it further into individual arguments based on
 * whitespace.
 *   - Populates a `Command` object with the parsed arguments.
 * - **Command Collection:**
 *   - Collects all `Command` objects into a vector, preserving the order of
 * commands.
 *
 * @param input The raw input string entered by the user.
 * @return A vector of `Command` objects, each containing the arguments for a
 * command.
 */

std::vector<Command> parse_input(const std::string &input) {
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