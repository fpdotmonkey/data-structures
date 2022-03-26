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
  #

LINTFLAGS:=\
  --quiet \
  -- \
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
	$(shell valgrind --leak-check=yes ./$(TEST_TARGET))

.PHONY: test
test: build
	if ! ./$(TEST_TARGET); then exit 2; fi

.PHONY: build
build: lint $(TEST_TARGET)

.PHONY: lint
lint: $(SOURCES)
	$(LINT) $(SOURCE_DIRECTORY)/*.cxx $(SOURCE_DIRECTORY)/*.h $(LINTFLAGS)

$(BUILD_DIRECTORY)/%.o: $(SOURCE_DIRECTORY)/%.cxx
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(TEST_TARGET): $(OBJECTS)
	$(CXX) $^ -o $@ $(LDLIBS)

.PHONY: clean
clean:
	rm -f $(BUILD_DIRECTORY)/*

-include $(DEPENDENCIES)
