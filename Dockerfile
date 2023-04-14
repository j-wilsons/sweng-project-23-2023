# Use an official Windows Server Core image as a parent image
FROM mcr.microsoft.com/windows/servercore:ltsc2019

# Set the working directory to C:\app
WORKDIR C:\app

# Install the Visual Studio Build Tools
ADD https://aka.ms/vs/16/release/vs_buildtools.exe C:\TEMP\vs_buildtools.exe
RUN C:\TEMP\vs_buildtools.exe --quiet --wait --norestart --nocache `
    --installPath C:\BuildTools `
    --add Microsoft.VisualStudio.Workload.VCTools `
    --add Microsoft.VisualStudio.Component.VC.CMake.Project `
    --add Microsoft.VisualStudio.Component.Windows10SDK.18362 `
    --add Microsoft.VisualStudio.Component.Windows10SDK.19041 `
    || IF "%ERRORLEVEL%"=="3010" EXIT 0

# Set the Visual Studio Build Tools environment variables
RUN setx /M PATH "%PATH%;C:\BuildTools\VC\Auxiliary\Build"

# Download and install CMake
ADD https://github.com/Kitware/CMake/releases/download/v3.21.3/cmake-3.21.3-windows-x86_64.zip C:\TEMP\cmake.zip
RUN powershell -Command Expand-Archive -Path C:\TEMP\cmake.zip -DestinationPath C:\ && `
    setx /M PATH "%PATH%;C:\cmake-3.21.3-win64-x64\bin"

# Copy the project directory into the container at C:\app
COPY . C:\app

# Use CMake to build the project
RUN C:\BuildTools\VC\Auxiliary\Build\vcvars64.bat && `
    mkdir build && cd build && `
    cmake -G "Visual Studio 16 2019" .. && `
    cmake --build . --config Release

# Set the default command to run when the container starts
CMD ["myapp.exe"]
