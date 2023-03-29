## Adding test files
To add a test file, add the following code block to `CMakeLists.txt` in the base folder:

```
# Let 'FILE' be the name of the test file to add (e.g., test_MyFunc)
# Let 'FILE_EXT' be the name of the test file to add with its extension (e.g., test_MyFunc.cpp)

# [FILE_EXT]
add_executable([FILE] test/[FILE_EXT])
target_link_libraries([FILE] PRIVATE imps)
add_test (
    NAME [FILE]
    COMMAND $<TARGET_FILE:[FILE]>
)
```

where `imps` contains the implementations in the file.
For example, for a file named "test_MyFunc.cpp",

```
# test_MyFunc.cpp
add_executable(test_MyFunc test/test_MyFunc.cpp)
target_link_libraries(test_MyFunc PRIVATE imps)
add_test (
    NAME test_MyFunc
    COMMAND $<TARGET_FILE:test_MyFunc>
)
```

The file itself must either include the header file for the functions to test (in which case, add the function definition to `test_implementations.cpp`) and have a single testing function. This function must be the exact same as the filename itself and must return an integer. If the function returns `0`, that means all tests within have passed. If not, at least one test has failed and the file fails overall. The file should also have a `main` function that calls and returns the test function. Look at current files for examples.

Also, in order for test coverage to work with the added tests, add the following lines to the Makefile in the root directory:
```
cd test && g++ [FILE_EXT] test_implementations.cpp --coverage -fprofile-arcs -ftest-coverage -g -O0 -o [EXE_NAME]
cd test && ./[EXE_NAME] && gcov [EXE_NAME]-[FILE_EXT] -n -r
```
The flags in the first line are what allow gcov files to be generated, with `-fprofile-arcs` generating .gcda files. The `gcov` on the second line generates .gcno files. Also note that all names in brackets must be fully replaced without extra characters. For a file named "test_myFunc.cpp", this would look like:
```
cd test && g++ test_myFunc.cpp test_implementations.cpp --coverage -fprofile-arcs -ftest-coverage -g -O0 -o covx
cd test && ./covx && gcov covx-test_myFunc.cpp.cpp -n -r
```
where `-n` doesn't create (unecessary) output files and `-r` only checks coverage for local files, i.e. it ignores any files imported with `#include`.

## Running tests
To run tests, simply call the line:
```
make test
```
to run all tests. The results will appear in the console to check.

If tests are not run, there may be an issue with the tests themselves, or with linking any libraries. Check the log for the third step for any "unresolved external symbols", which may be from libraries not being linked or implemented properly.


## Checking code coverage
### gcov
Code coverage is determined using the `gcov` tool that comes with GCC. We will be using this tool to generate code coverage reports. From here, you can check coverage of all test files.

To check code coverage, simply enter the line:
```
make coverage
```
to generate .gcno and .gcda files. These files can then be used with whatever software of your choice to generate a graphical output. The results of the tests will display in the console, such as below:

```
File 'test_example.cpp'
Lines executed:100.00% of 6
Lines executed:100.00% of 6
```

### Graphical output
In terms of graphical output, there are many options available, such as lcov. However, this program uses gcovr to check code coverage. gcovr can be installed through pip, the package installer for Python. You can download Python here: https://www.python.org/downloads/. Make sure to add Python to your PATH environment variable, or else you won't be able to access gcovr without its full path.

To install gcovr, enter the following command on the command line:
```
pip install gcovr
```
You must have generated the required .gcda and .gcno files using the above `make coverage` command. Once this is done, simply run the command 
```
make htmlcov
```
to generate a HTML file. This file is located in
```
/test/html/tests.details.html
```
within this directory and will show the coverage for all tests and their respective functions.
