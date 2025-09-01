CC = g++
CCFLAGS = -Wall -Wextra -Wextra -std=c++17
TESTFLAGS = -lgtest -lm -pthread
RM = rm -rf

GCOVR = $(shell which gcovr || echo ~/.local/bin/gcovr)
# pip install gcovr

# имя исполняемого файла
GAME_NAME = snake
# основная директория
MAIN_DIR = ./
# диркетория для сборки
BUILD_DIR = build
# директория установки
INSTALL_DIR = install
# имя директории для цели dist
TAR_DIR = s21_snake-1.0

# имя тестового файла
TESTS_NAME = snake_test
# имя тестового файла c тестами покрытия кода gcovr
TESTS_GCOV_NAME = snake_tests_gcov
# файлы и директории тестов
TEST_DIR = tests
TEST_SRC = $(shell find $(TEST_DIR) -name "*.cpp")
TEST_OBJ = $(TEST_SRC:.cpp=.o)
SNAKE_SRC = $(shell find brick_game/snake -name "*.cpp")
SNAKE_OBJ = $(SNAKE_SRC:.cpp=.o)

.PHONY: all build clean install uninstall dvi dist test

all: install

run:
	@$(INSTALL_DIR)/./$(GAME_NAME)

build:
	@cd qmake && qmake6 . && make
	@clear
	@echo -- Build complete. Build directory: $(BUILD_DIR)

install: build
	@mkdir -p $(INSTALL_DIR)
	@cp -p $(BUILD_DIR)/$(GAME_NAME) $(INSTALL_DIR)
	@echo -- Install complete. Install directory: $(INSTALL_DIR)
	@echo -- Use "make run" to start the game.

uninstall: 
	@$(RM) $(INSTALL_DIR)
	@echo -- Uninstall complete.

dist: build
	@$(RM) $(TAR_DIR)
	@mkdir $(TAR_DIR)
	@cp -p $(BUILD_DIR)/$(GAME_NAME) $(TAR_DIR)
	@tar czf $(TAR_DIR).tar.gz $(TAR_DIR)
	@$(RM) $(TAR_DIR)
	@echo -- Complete. Archiv name $(TAR_DIR).tar.gz

test: clean $(TESTS_NAME)
	@./$(TESTS_NAME)

$(TESTS_NAME): $(TEST_OBJ) $(SNAKE_OBJ)
	@$(CC) $(CCFLAGS) $^ -o $@ $(TESTFLAGS)

gcov_report: clean $(TESTS_GCOV_NAME)
	@./$(TESTS_GCOV_NAME)
	@mkdir report
	@$(GCOVR) -r . --html --html-details -o report/coverage.html --exclude=$(TEST_DIR)
	@make clean_gcov
# @open report/coverage.html

$(TESTS_GCOV_NAME):$(TEST_SRC) $(SNAKE_SRC)
	@$(CC) $(CCFLAGS) -g -fprofile-arcs -ftest-coverage $^ -o $@ $(TESTFLAGS)

clang:
	@clang-format -n --style=google $(shell find $(MAIN_DIR) -name "*.c")
	@clang-format -n --style=google $(shell find $(MAIN_DIR) -name "*.cpp")
	@clang-format -n --style=google $(shell find $(MAIN_DIR) -name "*.ui")

cpp:
	@cppcheck --enable=all --suppress=misprint_gamesingIncludeSystem --check-config .

valgrind: clean $(TESTS_NAME)
	@valgrind --tool=memcheck --leak-check=yes  ./$(TESTS_NAME)

clean: clean_gcov clean_report
	@$(RM) $(GAME_NAME)
	@$(RM) $(BUILD_DIR)
	@$(RM) $(TESTS_NAME)
	@$(RM) qmake/.qmake.stash
	@$(RM) qmake/Makefile
	@$(RM) $(shell find $(DIR) -name "*.o")
	@$(RM) $(shell find $(DIR) -name "*.gz")
	@echo -- Clean complete.

clean_report:
	@$(RM) report

clean_gcov:
	@$(RM) $(TESTS_GCOV_NAME)
	@$(RM) *.gcda
	@$(RM) *.gcno

%.o: %.cpp
	@$(CC) $(CCFLAGS) -c $< -o $@
