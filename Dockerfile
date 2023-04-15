# Use the latest Windows Server Core 2022 image.
FROM mcr.microsoft.com/windows/servercore:ltsc2022

# Restore the default Windows shell for correct batch processing.
SHELL ["cmd", "/S", "/C"]

# Install Chocolatey
RUN powershell.exe -Command "Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))"

# Install curl using Chocolatey
RUN powershell.exe -Command "choco install curl -y"

# Install the Visual Studio Build Tools.
RUN \
    # Download the Build Tools bootstrapper.
    curl -SL --output vs_buildtools.exe https://aka.ms/vs/17/release/vs_buildtools.exe \
    \
    # Install Build Tools with the Microsoft.VisualStudio.Workload.AzureBuildTools workload, excluding workloads and components with known issues.
    && (start /w vs_buildtools.exe --quiet --wait --norestart --nocache \
        --installPath "%ProgramFiles(x86)%\Microsoft Visual Studio\2022\BuildTools" \
        --add Microsoft.VisualStudio.Workload.AzureBuildTools \
        --add Microsoft.VisualStudio.Component.VC.CMake.Project \
        --add Microsoft.VisualStudio.Component.VC.Tools.x86.x64 \
        --remove Microsoft.VisualStudio.Component.Windows10SDK.10240 \
        --remove Microsoft.VisualStudio.Component.Windows10SDK.10586 \
        --remove Microsoft.VisualStudio.Component.Windows10SDK.14393 \
        --remove Microsoft.VisualStudio.Component.Windows81SDK \
        || IF "%ERRORLEVEL%"=="3010" EXIT 0) \
    \
    # Cleanup
    && del /q vs_buildtools.exe

# Install CMake
RUN choco install cmake -y --installargs 'ADD_CMAKE_TO_PATH=System'

# Copy the source code to the container.
COPY . C:/app/

# Build the application.
RUN \
    # Set working directory
    cd C:/app/ \
    # Run CMake
    && cmake -G "Visual Studio 17 2022" -A Win32 -DCMAKE_BUILD_TYPE=Release -B build \
    # Build the application
    && cmake --build build --config Release
