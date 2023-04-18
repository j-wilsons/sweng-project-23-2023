# Use the latest Windows Server Core 2022 image.
FROM mcr.microsoft.com/windows/servercore:ltsc2022

# Restore the default Windows shell for correct batch processing.
SHELL ["cmd", "/S", "/C"]

# Install Chocolatey
RUN powershell.exe -Command "Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))"

# Install the Visual Studio Build Tools.
RUN choco install visualstudio2022buildtools --package-parameters "--allWorkloads --includeRecommended --includeOptional --passive --add Microsoft.VisualStudio.Component.VC.Tools.x86.x64 --add Microsoft.VisualStudio.Component.Windows10SDK.19041 --locale en-US"

# Set the paths to the C and C++ compilers
ENV CMAKE_C_COMPILER="C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Tools\MSVC\14.29.30133\bin\Hostx64\x64\cl.exe"
ENV CMAKE_CXX_COMPILER="C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Tools\MSVC\14.29.30133\bin\Hostx64\x64\cl.exe"


# Copy the source code to the container.
COPY . C:/app/

# Build the application.
RUN \
    # Set working directory
    cd C:/app/ \
    # Run CMake with explicit compiler paths
    && cmake -G "Visual Studio 17 2022" -A Win32 -DCMAKE_BUILD_TYPE=Release -B build -DCMAKE_C_COMPILER="C:\\Program Files (x86)\\Microsoft Visual Studio\\2022\\BuildTools\\VC\\Tools\\MSVC\\14.30.30705\\bin\\Hostx64\\x86\\cl.exe" -DCMAKE_CXX_COMPILER="C:\\Program Files (x86)\\Microsoft Visual Studio\\2022\\BuildTools\\VC\\Tools\\MSVC\\14.30.30705\\bin\\Hostx64\\x86\\cl.exe" \
    # Build the application
    && cmake --build build --config Release
