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
