# Output File
OUTPUT_DIR =	.
NAME = 				$(OUTPUT_DIR)/PmergeMe

# Directories
INCLUDES_DIR =	.
SOURCES_DIR =		.
OBJECTS_DIR =		objs
TEST_DIR =		tests

# Files
SOURCES =		PmergeMe.cpp Jacobsthal.cpp CountableInt.cpp main.cpp
INCLUDES =	$(patsubst $(SOURCES_DIR)/%.cpp, $(INCLUDES_DIR)/%.hpp, $(SOURCES))
OBJECTS =		$(SOURCES:%.cpp=$(OBJECTS_DIR)/%.o)

# Compiler & Flags
CXX =			c++
CXXFLAGS =		-Wall -Wextra -Werror -std=c++98
CPPFLAGS =		-I $(INCLUDES_DIR)
MEMORYFLAGS = -fsanitize=address -g3

#-----------------------------------------------
# Colors
RESET = \033[0m
BOLD = \033[1m
# Regular Colors
GREEN = \033[32m
CYAN = \033[36m
GRAY = \033[90m
# Bold Colors
B_GREEN = \033[1;32m
B_BLUE = \033[1;34m
B_CYAN = \033[1;36m

#-----------------------------------------------
# Rules
all:	$(NAME)

# Link Targets
$(NAME): $(OBJECTS)
	@printf "\r$(GREEN)[%2d/%2d]$(RESET) All files compiled! Linking $(CYAN)$(NAME)$(RESET)\033[K\n" \
		"$$(find $(OBJECTS_DIR) -name '*.o' | wc -l)" "$$(echo $(SOURCES) | wc -w)"
	@$(CXX) $(CPPFLAGS) $^ -o $@
	@echo "$(B_GREEN)SUCCESS:$(RESET) $(NAME) linked successfully"
	@chmod 755 $(NAME)
	@echo "$(B_CYAN)READY:$(RESET) $(NAME) is ready to run"

# Compile Targets
$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.cpp | $(OBJECTS_DIR)
	@printf "\r$(GREEN)[%2d/%2d]$(RESET) Compiling $(CYAN)%s$(RESET)\033[K" \
		"$$(find $(OBJECTS_DIR) -type f | wc -l)" "$$(echo $(SOURCES) $(TEST_SOURCES) | tr ' ' '\n' | sort -u | wc -l)" "$<"
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJECTS_DIR):
	@mkdir -p $(OBJECTS_DIR)

# Clean Targets
clean:
	@rm -rf $(OBJECTS) $(TEST_OBJECTS)
	@rm -rfd $(OBJECTS_DIR)
	@echo "$(GRAY)CLEAN: $(NAME) object files cleaned$(RESET)"

fclean:	clean
	@rm -rf $(NAME) $(TEST_NAME)
	@echo "$(GRAY)FCLEAN: $(NAME) executable files cleaned$(RESET)"

re:		fclean all

update:	fclean
	make

# Phony
.PHONY = all clean fclean re update test performance correctness

#-----------------------------------------------
# Test Targets

TEST_SIZE = 10

ifeq ($(shell uname), Linux)
	TEST_COMMAND = shuf -i 1-$(TEST_SIZE) -n $(TEST_SIZE) | tr "\n" " "
else ifeq ($(shell uname), Darwin)
	TEST_COMMAND = jot -r $(TEST_SIZE) 1 $(TEST_SIZE) | tr '\n' ' '
endif

test:	$(NAME)
	@echo $$( $(TEST_COMMAND) )
	@$(NAME) $$( $(TEST_COMMAND) )
	@echo ""
	@./tests/maxComp.sh $(TEST_SIZE)

#-----------------------------------------------
debug:
	@echo "$(B_BLUE)Debug Information:$(RESET)"
	@echo "$(CYAN)SOURCES:$(RESET) $(SOURCES)"
	@echo "$(CYAN)TEST_SOURCES:$(RESET) $(TEST_SOURCES)"
	@echo "$(CYAN)INCLUDES:$(RESET) $(INCLUDES)"
	@echo "$(CYAN)OBJECTS:$(RESET) $(OBJECTS)"
	@echo "$(CYAN)TEST_OBJECTS:$(RESET) $(TEST_OBJECTS)"
	@echo "$(CYAN)OBJECTS_DIR:$(RESET) $(OBJECTS_DIR)"
	@echo "$(CYAN)CXX:$(RESET) $(CXX)"
	@echo "$(CYAN)CXXFLAGS:$(RESET) $(CXXFLAGS)"
	@echo "$(CYAN)CPPFLAGS:$(RESET) $(CPPFLAGS)"
	@echo "$(CYAN)NAME:$(RESET) $(NAME)"
	@echo "$(CYAN)TEST_NAME:$(RESET) $(TEST_NAME)"
	@echo "$(CYAN)OUTPUT_DIR:$(RESET) $(OUTPUT_DIR)"

.PHONY: debug
