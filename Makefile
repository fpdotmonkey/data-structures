CXX=g++
LINT=clang-tidy
SOURCE_DIRECTORY:=source
BUILD_DIRECTORY:=build

CPPFLAGS:=\
  -MMD \
  -MP \
  #

CXXFLAGS:=\
  -x c++ \
  -std=gnu++14 \
  -O0 -g3 \
  -I./$(SOURCE_DIRECTORY) \
  -Wall -Wextra -Wpedantic -Werror \
  --coverage \
  #

LDFLAGS:=\
  -pthread \
  #

LDLIBS:=\
  -lgtest \
  -lgtest_main \
  -fprofile-arcs \
  #

LINTFLAGS:=\
  --quiet \
  -- \
  $(LDFLAGS) \
  $(LDLIBS) \
  $(CXXFLAGS) \
  #

SOURCES=$(wildcard $(SOURCE_DIRECTORY)/*.cxx)
OBJECTS=$(patsubst \
  $(SOURCE_DIRECTORY)/%.cxx, $(BUILD_DIRECTORY)/%.o, $(SOURCES))
DEPENDENCIES=$(OBJECTS:.o=.d)
TEST_TARGET:=$(BUILD_DIRECTORY)/data-structures-tests

.PHONY: all
all: memcheck

.PHONY: memcheck
memcheck: test
	@if ! valgrind --version 2>/dev/null 1>/dev/null; then \
	  echo "valgrind is needed for memcheck"; \
	  exit 1; \
	fi
	valgrind --leak-check=yes $(TEST_TARGET)

.PHONY: test
test: build
	if ! ./$(TEST_TARGET); then exit 2; fi

.PHONY: build
build: $(TEST_TARGET)

.PHONY: coverage
coverage: test
	mkdir --parents $(BUILD_DIRECTORY)/gcov $(BUILD_DIRECTORY)/lcov
	gcov \
		--relative-only \
		--branch-probabilities $(SOURCES) \
		--object-directory $(OBJECTS)
	mv *.gcov $(BUILD_DIRECTORY)/gcov
	@if ! lcov --version >/dev/null; then \
		echo "install lcov to see a visual coverage report"; \
		exit 0; \
	fi
	lcov \
		--capture \
		--directory $(BUILD_DIRECTORY) \
		--output-file $(BUILD_DIRECTORY)/lcov/main_coverage.info
	genhtml \
		$(BUILD_DIRECTORY)/lcov/main_coverage.info \
		--output-directory $(BUILD_DIRECTORY)/lcov/
	@echo
	@echo "View the coverage report at file://$(shell pwd)/$(BUILD_DIRECTORY)/lcov/index.html"

$(BUILD_DIRECTORY)/%.o: $(SOURCE_DIRECTORY)/%.cxx
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(TEST_TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ -o $@ $(LDLIBS)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIRECTORY)/*

-include $(DEPENDENCIES)
