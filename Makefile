CMAKE_BUILD_TYPE := Release
BUILD_DIR := build

all: build

build:
	if not exist "$(BUILD_DIR)" mkdir $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE) -A Win32 ..
	cmake --build $(BUILD_DIR) --config $(CMAKE_BUILD_TYPE)

clean: cleantest
	rm -rf $(BUILD_DIR)

cleantest:
	rm -rf test/*.gcno
	rm -rf test/*.gcda
	rm -rf test/*.o
	rm -rf test/*.exe
	rm -rf test/html/

.PHONY: all build clean cleantest test coverage htmlcov 

test:
	cd build && ctest -C $(CMAKE_BUILD_TYPE)

coverage:
	cd test && g++ test_example.cpp test_implementations.cpp --coverage -fprofile-arcs -ftest-coverage -g -O0 -o cov1
	cd test && g++ test_isNum.cpp test_implementations.cpp --coverage -fprofile-arcs -ftest-coverage -g -O0 -o cov2
	cd test && g++ test_isCorrectForm.cpp test_implementations.cpp --coverage -fprofile-arcs -ftest-coverage -g -O0 -o cov3
	cd test && ./cov1 && gcov cov1-test_example.cpp -n -r
	cd test && ./cov2 && gcov cov2-test_isNum.cpp -n -r
	cd test && ./cov3 && gcov cov3-test_isCorrectForm.cpp -n -r


htmlcov:
	rm -rf test/html
	cd test && mkdir html
	cd test && gcovr --html-details -o html/tests.details.html 
# ./test/html/tests.details.html
# doesn't seem to work on my machine, not sure why

runServer:
	cd build/release && start server.exe &
  
runClient:
	cd build/release && start client.exe &

run: runClient runServer

freshcov: clean build test coverage htmlcov
