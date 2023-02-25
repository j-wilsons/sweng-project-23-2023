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





