CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Werror
LIBS := -lgtest -lgtest_main -lpthread

BUILD_DIR := build
ARCHIVE_DIR := archive_calculator
ARCHIVE_NAME := archive_calculator.tgz

.PHONY: all clean install uninstall dist tests gcov_report leak_application open clang

all: install

install:
	@if [ ! -d "$(BUILD_DIR)" ] || [ ! -f "$(BUILD_DIR)/viewer.app/Contents/MacOS/viewer" ]; then \
		mkdir -p $(BUILD_DIR); \
		cd view && qmake && make -j6 && make clean && rm Makefile; \
		cd ..; \
		mv view/viewer.app $(BUILD_DIR); \
		echo "The Viewer application has been successfully installed and is in ${PWD}/$(BUILD_DIR)"; \
	else \
		echo "The Viewer application is already installed in the ${PWD}/$(BUILD_DIR) folder"; \
	fi

uninstall:
	@if [ -d "$(BUILD_DIR)" ]; then \
		rm -r $(BUILD_DIR); \
		echo "The application was successfully deleted"; \
	else \
		echo "The application is not installed"; \
	fi

clean:
	@-rm -rf test print test.info *.gcda *.gcno report leaks *.dSYM gcov_report*
	@echo "Deletion completed"

tests: clean
	@chmod 000 tests/obj/City.obj
	@$(CXX) $(CXXFLAGS) tests/tests.cc model/*.cc -g -o test $(LIBS)
	@./test

clang:
	@find . \( -name '*.h' -o -name '*.cc' \) -print0 | xargs -0 clang-format -n -style=Google

clang_correct:
	@find . \( -name '*.h' -o -name '*.cc' \) -print0 | xargs -0 clang-format -i -style=Google

dvi:
	open README.md

dist:
	@if [ -d "$(BUILD_DIR)" ] && [ -f "$(BUILD_DIR)/viewer.app/Contents/MacOS/viewer" ]; then \
		echo "Begin packaging process"; \
		mkdir -p $(ARCHIVE_DIR); \
		mv $(BUILD_DIR)/viewer.app $(ARCHIVE_DIR)/; \
		tar cvzf $(ARCHIVE_NAME) $(ARCHIVE_DIR)/; \
		rm -rf $(ARCHIVE_DIR)/; \
		echo "Build completed"; \
	else \
		make install; \
		make dist; \
	fi

