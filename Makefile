CMAKE_BUILD_TYPE := Release
BUILD_DIR := build

all: build

build:
	if not exist "$(BUILD_DIR)" mkdir $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE) -A Win32 ..
	cmake --build $(BUILD_DIR) --config $(CMAKE_BUILD_TYPE)

clean:
	rm -rf $(BUILD_DIR)
# maybe something to clear the uncommitted files in /test too

.PHONY: all build clean

run:
	cd build/release && start server.exe &
	cd build/release && start client.exe &

# test:
# 	cd build
# 	ctest -C $(CMAKE_BUILD_TYPE)

# coverage:
# 	cd test
# 	g++ -g -O0 test_example.cpp test_implementation.cpp --coverage -c
# 	g++ -g -O0 test_example.o test_implementation.o --coverage -c cov
# 	./cov
# 	gcov test_example.cpp -n -r
