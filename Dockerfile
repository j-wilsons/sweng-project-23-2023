# Use the latest Windows Server Core 2022 image.
FROM mcr.microsoft.com/windows/servercore:ltsc2022

# Restore the default Windows shell for correct batch processing.
SHELL ["cmd", "/S", "/C"]

# Install curl
RUN powershell.exe -Command Install-PackageProvider -Name NuGet -MinimumVersion 2.8.5.201 -Force ; \
    powershell.exe -Command Install-Package -Name curl

# Install the Visual Studio Build Tools.
RUN `
    # Download the Build Tools bootstrapper.
    curl -SL --output vs_buildtools.exe https://aka.ms/vs/17/release/vs_buildtools.exe \
    `
    # Install Build Tools with the Microsoft.VisualStudio.Workload.AzureBuildTools workload, excluding workloads and components with known issues.
    && (start /w vs_buildtools.exe --quiet --wait --norestart --nocache \
        --installPath "%ProgramFiles(x86)%\Microsoft Visual Studio\2022\BuildTools" \
        --add Microsoft.VisualStudio.Workload.AzureBuildTools \
        --remove Microsoft.VisualStudio.Component.Windows10SDK.10240 \
        --remove Microsoft.VisualStudio.Component.Windows10SDK.10586 \
        --remove Microsoft.VisualStudio.Component.Windows10SDK.14393 \
        --remove Microsoft.VisualStudio.Component.Windows81SDK \
        || IF "%ERRORLEVEL%"=="3010" EXIT 0) \
    \
    # Cleanup
    && del /q vs_buildtools.exe

# Install CMake
RUN `
    # Download CMake
    curl -SL --output cmake_installer.exe https://github.com/Kitware/CMake/releases/download/v3.22.0/cmake-3.22.0-windows-x86_64.exe \
    # Install CMake
    && cmake_installer.exe --quiet --skip-license \
    # Cleanup
    && del /q cmake_installer.exe

# Copy the source code to the container.
COPY . C:\app

# Build the application.
RUN \
    # Set working directory
    cd C:\app \
    # Run CMake
    && cmake . \
    # Build the application
    && cmake --build . --config Release

# Define the entry point for the docker container.
# This entry point launches the application.
ENTRYPOINT ["C:\\app\\bin\\MyApp.exe"]
