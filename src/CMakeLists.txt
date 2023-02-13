# Set source files
set(SOURCES
        server.cpp
        client.cpp
        )

# Create executables for server.cpp and client.cpp
foreach(src_file ${SOURCES})
    get_filename_component(exec_name ${src_file} NAME_WE)
    add_executable(${exec_name} ${src_file})
endforeach()