cmake_minimum_required (VERSION 3.8)
project ("Sweng-project-2023")
set(CMAKE_BUILD_TYPE Release)
add_library(Application ${CMAKE_CURRENT_SOURCE_DIR}/src/Application.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/Application.h)

#add_library(quickfix STATIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/quickfix.lib)
set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/Client.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Server.cpp
            )
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
foreach(src_file ${SOURCES})
    get_filename_component(exec_name ${src_file} NAME_WE)
    add_executable(${exec_name} ${src_file})
    target_link_libraries(${exec_name} "${CMAKE_CURRENT_SOURCE_DIR}/libs/quickfix.lib")
    target_link_libraries(${exec_name} wsock32 ws2_32)
    target_link_libraries(${exec_name} Application)
endforeach()




# all tests must return either 0 (pass) or not-zero (fail)
enable_testing() # enable testing
add_library(imps test/test_implementations.cpp) # add function defintions file

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



# ! AUTOMATIC TESTING, LINKING NOT WORKING, IGNORE
# # add test files here in the format 'add_executable(NAME PATH)'
# # all tests must return either 0 (pass) or not-zero (fail)
# # add_executable(cpp_test test/test.cpp) # add first test file
# enable_testing() # enable testing
# add_library(imps test/test_implementations.cpp) # add function defintions file
# create_test_sourcelist(
#     Tests
#     AllTests.cpp
#     test/test_isCorrectForm.cpp
#     test/test_isNum.cpp
# )
# add_executable(AllTests ${Tests}) # add second test file
# target_link_libraries(AllTests PUBLIC imps)
# set (ActiveTests ${Tests})
# remove (ActiveTests AllTests.cpp)
# foreach (test ${ActiveTests})
#     get_filename_component (tst ${test} NAME_WE)
#     add_test (
#         NAME ${tst}
#         COMMAND AllTests ${tst}
#     )
# endforeach()
