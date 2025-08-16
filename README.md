# OpenGL Renderer

A basic OpenGL renderer using GLFW, GLAD, ImGui, and CMake. I am using this project to learn about graphics programing in c++ and learning how to code efficently in Neovim.

## Prerequisites

Make sure you have the following installed:

- **CMake** ≥ 3.16
- **A C++ compiler** with C++23 support (e.g., `g++` ≥ 11, `clang++` ≥ 13, MSVC 2022). I am using g++ for this project and is geared towards that. Modifications may be needed if using a different compiler.
- **OpenGL** development libraries
- **GLFW** (the CMake build will use `find_package(glfw3 REQUIRED)`)

On Ubuntu/Debian-based distros:
```bash
sudo apt update
sudo apt install cmake g++ libglfw3-dev libopengl-dev

**## Cloning from git**

git clone https://github.com/<your-username>/OpenGLRenderer.git
cd OpenGLRenderer

**## Building from cmake and running**

# Create and enter the build directory
cmake -S . -B build
# Build the project
cmake --build build
# run the project from root
./build/renderer

**## Project setup**

OpenGLRenderer/
├── CMakeLists.txt         # Build configuration
├── include/               # Header files
├── src/                   # Source files
├── libs/                  # Third-party libraries (glad, imgui)
└── build/                 # Generated build files (ignored in .gitignore)
