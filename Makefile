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
	cd test && g++ test_example.cpp test_implementations.cpp -lws2_32 --coverage -fprofile-arcs -ftest-coverage -g -O0 -o cov1
	cd test && g++ test_isNum.cpp test_implementations.cpp -lws2_32 --coverage -fprofile-arcs -ftest-coverage -g -O0 -o cov2
	cd test && g++ test_isCorrectForm.cpp test_implementations.cpp -lws2_32 --coverage -fprofile-arcs -ftest-coverage -g -O0 -o cov3
	cd test && g++ test_userInput.cpp test_implementations.cpp -lws2_32 --coverage -fprofile-arcs -ftest-coverage -g -O0 -o cov4
	cd test && g++ test_httpReq.cpp test_implementations.cpp -lws2_32 --coverage -fprofile-arcs -ftest-coverage -g -O0 -o cov5
	test/cov1 && cd test && gcov cov1-test_example.cpp -n -r -b
	test/cov2 && cd test && gcov cov2-test_isNum.cpp -n -r -b
	test/cov3 && cd test && gcov cov3-test_isCorrectForm.cpp -n -r -b
	test/cov4 && cd test && gcov cov4-test_userInput.cpp -n -r -b
	test/cov5 && cd test && gcov cov5-test_httpReq.cpp -n -r -b


htmlcov:
	rm -rf test/html
	cd test && mkdir html
	cd test && gcovr --html-details -o html/tests.details.html 
	./open_coverage.bat


runServer:
	cd build/release && start server.exe &
  
runClient:
	cd build/release && start client.exe &

run: runClient runServer

freshcov: clean build test coverage htmlcov

freshtest: clean build test