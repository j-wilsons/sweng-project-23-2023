CMAKE_BUILD_TYPE := Release
BUILD_DIR := build

all: build

build:
	if not exist "$(BUILD_DIR)" mkdir $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE) -A Win32 ..
	cmake --build $(BUILD_DIR) --config $(CMAKE_BUILD_TYPE)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all build clean

runServer:
	cd build/release && start server.exe &

runClient:
	cd build/release && start client.exe &

run: runClient runServer
