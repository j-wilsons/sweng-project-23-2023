## Add test file to CMakeLists.txt
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

## Running tests
Make sure there is no preexisting `build` folder before running. 
Call the following commands, in order:

First, run 
```
make
```

to create and write to a new `build` folder. Next,

```
cd build
```

to move to that folder. Finally,

```
ctest -C [build_type]
```

where `build_type` is either `Release` or `Debug` to actually run the tests.

If tests are not run, there may be an issue with the tests themselves, or with linking any libraries. Check the log for the third step for any "unresolved external symbols", which may be from libraries not being linked or implemented properly.


## Checking code coverage
### gcov
Code coverage is determined using the `gcov` tool that comes with GCC. To check code coverage, run the above steps and navigate to the `test` directory. From here, you can check coverage of individual test files.

To start, enter the command 

```
g++ -g -O0 [test_file] test_implementations.cpp --coverage -c
```

where `test_file` is the full name of the test file you want to check (e.g., `test_example.cpp`). Linking is avoided deliberately here.

Next, run the same command
```
g++ -g -O0 [test_file] test_implementations.o --coverage -o cov
```

where `test_file` is the full name of the object of the test file you want to check (e.g., `test_example.o`, which will now exist after the previous step). 

Next, run the `cov` executable with:

```
./cov
```

Next, run the command `gcov` by doing:

```
gcov [test_file] -n -r
```

where `test_file` is the full name of the test file you want to check (e.g., `test_example.cpp`). The `-n` flag prevents output files from being written into the directory and cluttering it up. The `-r` flag ignores any files imported using `#include` in the .cpp files.


Following this, you will see the results printed in the console, such as below:

```
File 'test_example.cpp'
Lines executed:100.00% of 6
Lines executed:100.00% of 6
```

### lcov
`lcov` is a tool that allows a graphical representation of coverage results given by `gcov`. 
