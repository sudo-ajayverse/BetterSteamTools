# How to Build BetterSteamTools

This document provides step-by-step instructions for building **BetterSteamTools** from source on Windows.

---

## Prerequisites

Before compiling the project, ensure you have the following software installed:

### 1. Visual Studio 2022 Community (Free)
* **Download Link:** [Visual Studio Downloads](https://visualstudio.microsoft.com/downloads/)
* **Installation Step:** During installation, make sure to check the box for:
  👉 **"Desktop development with C++"**  
  *(This installs the MSVC C++ compiler and Windows SDK required for building Windows DLLs).*

### 2. CMake (Free & Open Source)
* **Download Link:** [CMake Official Downloads](https://cmake.org/download/)
* **Installer:** Download the **Windows x64 Installer (`.msi`)**.
* **Installation Step:** During setup, select:
  👉 **"Add CMake to system PATH for all users"**

---

## Build Instructions

Once Visual Studio and CMake are installed:

1. Open **PowerShell** or **Command Prompt**.
2. Navigate to your project directory:
   ```powershell
   cd "D:\Git Projects\Git repos\BetterSteamTools"
   ```
3. Run `build.bat` to compile:
   ```powershell
   .\build.bat
   ```

---

## Output Binaries

After the build succeeds, your output binaries will be created in:
* 📍 **Core DLLs:** `build/src/Release/` (`dwmapi.dll` / `xinput1_4.dll` & `OpenSteamTool.dll`)
* 📍 **Ticket Tool:** `build/tools/Release/` (`extract_tickets.exe`)
