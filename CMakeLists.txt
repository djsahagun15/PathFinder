cmake_minimum_required(VERSION 3.10)
project(PathFinder)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Define source files
set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/node.cpp
    ${CMAKE_SOURCE_DIR}/src/grid.cpp
    ${CMAKE_SOURCE_DIR}/src/camera.cpp
    ${CMAKE_SOURCE_DIR}/src/pathfinding_algorithm.cpp
    ${CMAKE_SOURCE_DIR}/src/bfs.cpp
    ${CMAKE_SOURCE_DIR}/src/dijkstra.cpp
    ${CMAKE_SOURCE_DIR}/src/astar.cpp
    ${CMAKE_SOURCE_DIR}/src/pathfinder.cpp
    ${CMAKE_SOURCE_DIR}/src/main.cpp
)

# Fetch raylib if it is not already installed
include(FetchContent)

# Fetch raylib from GitHub repository
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG master  # You can specify a commit hash or a release tag here if you prefer
)

# Make sure raylib is available and build it if needed
FetchContent_MakeAvailable(raylib)

if (EMSCRIPTEN)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s GL_ENABLE_GET_PROC_ADDRESS=1")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()


# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link raylib and other libraries based on platform
if(WIN32)
    set(LIBRARIES
        raylib
        opengl32
        gdi32
        winmm
    )
elseif(UNIX)
    set(LIBRARIES
        raylib
        GL
        m
        pthread
        dl
        rt
        X11
    )
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

# Link libraries to the project
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})

# Set output directory for the executable
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    CXX_EXTENSIONS OFF
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Add a 'run' target to execute the program
add_custom_target(run
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

# Add custom command to check if source files have changed
add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/check_sources
    COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_BINARY_DIR}/check_sources
    DEPENDS ${SOURCES}
    COMMENT "Checking if source files have changed..."
)

# Add a dependency for 'check_sources' target
add_custom_target(check_sources DEPENDS ${CMAKE_BINARY_DIR}/check_sources)
add_dependencies(run check_sources)
