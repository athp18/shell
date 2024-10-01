CXX = g++
BREW_PREFIX := $(shell brew --prefix readline)
CXXFLAGS = -std=c++11 -Wall -I$(BREW_PREFIX)/include
LDFLAGS = -L$(BREW_PREFIX)/lib

# let's hardcode src directory for now
SRC_DIR = src
OBJS = $(SRC_DIR)/main.o $(SRC_DIR)/parser.o $(SRC_DIR)/executor.o $(SRC_DIR)/builtins.o $(SRC_DIR)/signals.o

# Target executable
shell: $(OBJS)
	$(CXX) $(CXXFLAGS) -o shell $(OBJS) $(LDFLAGS) -lreadline

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f shell $(SRC_DIR)/*.o