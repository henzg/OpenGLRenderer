cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE GLVND)

cmake_minimum_required(VERSION 3.16)
project(renderer LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# compile_commands.json setup
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --- Third part libs --- #
# glad
add_library(glad STATIC libs/glad/src/glad.c)
target_include_directories(glad PUBLIC libs/glad/include)

# glm *header only so it uses INTERFCE
add_library(glm_lib INTERFACE)
target_include_directories(glm_lib INTERFACE ${CMAKE_SOURCE_DIR}/libs)

# imgui 
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/libs/imgui)
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/imgui_impl_opengl3.cpp
)
add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC 
    ${IMGUI_DIR}
    ${CMAKE_SOURCE_DIR}/libs
)

# --- Core Application -- #
set(APP_SRC
    src/main.cpp
    src/Camera.cpp
    src/Core.cpp
    src/DeveloperWindow.cpp
    src/ElementArray.cpp
    src/ImGuiSystem.cpp
    src/IndexBuffer.cpp
    src/InputManager.cpp
    src/Mesh.cpp
    src/Renderer.cpp
    src/ResourceManager.cpp
    src/Scene.cpp
    src/Texture.cpp
    src/VertexArray.cpp
    src/VertexBuffer.cpp
    src/Window.cpp
    src/stb_image.cpp
    src/tests/Test.cpp
    src/tests/Test3DBasics.cpp
    src/tests/TestClearColor.cpp
    src/tests/TestLightCaster.cpp
    src/tests/TestLighting.cpp
    src/tests/TestLightingMaps.cpp
    src/tests/TestMaterials.cpp
    src/tests/TestShaders.cpp
    src/tests/TestSquare.cpp
    src/tests/TestTriangle.cpp
)
# file(GLOB_RECURSE APP_SRC ${CMAKE_SOURCE_DIR}/src/*.cpp) # old implementation, works but less explicit. Keep for now in case files dont load and you want to set using this method.

# creates executable for the project
add_executable(${PROJECT_NAME} ${APP_SRC})

# Custom include directories. Can add more if needed
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

# --- Link Libraries to the Main Executable --- #
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# Link all necessary libs to executable *private means they are only linked to the project and not for consumers
target_link_libraries(${PROJECT_NAME} PRIVATE 
    glad 
    glfw
    OpenGL::GL 
    imgui 
    glm_lib
)
