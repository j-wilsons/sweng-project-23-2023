cmake_minimum_required (VERSION 3.8)
project ("Sweng-project-2023")
set(CMAKE_BUILD_TYPE Release)

add_library(Application ${CMAKE_CURRENT_SOURCE_DIR}/src/Application.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/Application.h)
add_library(DatabaseManager ${CMAKE_CURRENT_SOURCE_DIR}/src/DatabaseManager.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/DatabaseManager.h)
add_library(MatchingEngine ${CMAKE_CURRENT_SOURCE_DIR}/src/MatchingEngine.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/MatchingEngine.h)
add_library(OrderStatus ${CMAKE_CURRENT_SOURCE_DIR}/src/OrderStatus.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/OrderStatus.h)


#add_library(quickfix STATIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/quickfix.lib)
set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/Client.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Server.cpp
            )
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include
                    ${CMAKE_CURRENT_SOURCE_DIR}/src)

foreach(src_file ${SOURCES})
    get_filename_component(exec_name ${src_file} NAME_WE)
    add_executable(${exec_name} ${src_file})
    target_link_libraries(${exec_name} "${CMAKE_CURRENT_SOURCE_DIR}/libs/quickfix.lib")
    target_link_libraries(${exec_name} "${CMAKE_CURRENT_SOURCE_DIR}/libs/libcurl.lib")
    target_link_libraries(${exec_name} ODBC32.lib)
    target_link_libraries(${exec_name} MatchingEngine)
    target_link_libraries(${exec_name} wsock32 ws2_32)
    target_link_libraries(${exec_name} Application)
    target_link_libraries(${exec_name} DatabaseManager)
    target_link_libraries(${exec_name} ${CURL_LIB})
    target_link_libraries(${exec_name} OrderStatus)
endforeach()




# all tests must return either 0 (pass) or not-zero (fail)
enable_testing() # enable testing

# https://www.danielsieger.com/blog/2022/03/06/code-coverage-for-cpp.html
set(CMAKE_CXX_FLAGS="-g -O0 -Wall -W -Wshadow -Wunused-variable -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers -Wno-deprecated -Woverloaded-virtual -Wwrite-strings --coverage -fprofile-arcs -ftest-coverage")

#SET(CMAKE_SHARED_LINKER_FLAGS="-fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS="-O0 --coverage -fprofile-arcs -ftest-coverage")
add_library(imps test/test_implementations.cpp) # add function defintions file
set (gcov_path "${CMAKE_CURRENT_SOURCE_DIR}/libs/gcov.exe")
target_link_options(imps PRIVATE gcov_path)

# test_isNum.cpp
add_executable(test_isNum test/test_isNum.cpp)
target_link_libraries(test_isNum PRIVATE imps)
add_test (
    NAME test_isNum
    COMMAND $<TARGET_FILE:test_isNum>
)

# test_isCorrectForm.cpp
add_executable(test_isCorrectForm test/test_isCorrectForm.cpp) # add test file
target_link_libraries(test_isCorrectForm PRIVATE imps)
add_test (
    NAME test_isCorrectForm
    COMMAND $<TARGET_FILE:test_isCorrectForm>
)

# test_example.cpp
add_executable(test_example test/test_example.cpp) # add test file
target_link_libraries(test_example PRIVATE imps)
add_test (
    NAME test_example
    COMMAND $<TARGET_FILE:test_example>
)

# test_userInput.cpp
add_executable(test_userInput test/test_userInput.cpp) # add test file
target_link_libraries(test_userInput PRIVATE imps)
add_test (
    NAME test_userInput
    COMMAND $<TARGET_FILE:test_userInput>
)

# test_extract_key.cpp
add_executable(test_extract_key test/test_extract_key.cpp) # add test file
target_link_libraries(test_extract_key PRIVATE imps)
add_test (
    NAME test_extract_key
    COMMAND $<TARGET_FILE:test_extract_key>
)
