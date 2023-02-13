cmake_minimum_required(VERSION 3.13)

# Set project name
project(ServerClient)

# Find required packages
find_package(Threads REQUIRED)

# Add subdirectory
add_subdirectory(src)