# **PathFinder - Pathfinding Algorithm Visualizer**
PathFinder is an interactive tool for exploring and experimenting with popular pathfinding algorithms such as BFS, Dijkstra, and A*, on a customizable grid system.

## **This project is currently under development and not yet complete.**

## **TODO**
- **Algorithm Implementation**
   - ~~Implement Breath-First Search (BFS)~~
   - ~~Implement Dijkstra's Algorithm.~~
   - ~~Implement A* Algorithm.~~
     
- **Grid Features**
   - Implement grid resizing.
 
- **Visualizations**
   - ~~Visualize the step-by-step process of pathfinding.~~
   - ~~Highlight the discovered path.~~
 
- **Controls**
   - ~~Add buttons for starting, and pausing/resuming algorithm process, and resetting grid.~~
   - ~~Add process speed slider.~~
 
- **Documentation**
   - Add comments in the source code.

## Current Controls
**Mouse Controls:**
- **Left Click**
   - Press and drag to move the start (green) and end (red) nodes
   - Add/remove walls on the grid

- **Right Click**
   - Move the **camera**

- **Mouse Wheel**
   - Camera zoom

**Keyboard Controls:**
- **R**     : Reset the grid to its initial state
- **C**     : Clear the path

## Prerequisites
   Before building the project, make sure you have the following installed in your system:
   - **GCC or Clang**   : C/C++ compiler (required)
   - **CMake**          : Build system (required)
   - **Emscripten SDK** (Optional. Required for building the web version)
   - **Python**         (Optional. Required for building the web version; emsdk requires Python)
   - **Git**            (Optional. Required for building the web version; emsdk requires Git)

## Building for Desktop
1. **Clone this repository:**
   ```
   git clone https://github.com/djsahagun15/PathFinder.git
   cd PathFinder
   ```
   
2. **Build the project:**
   ```
   mkdir build
   cd build
   cmake ..
   make
   ```
   
3. **Run the application:**
   The binaries are saved in the PathFinder/bin folder, or use the following command to run the application:
   ```
   make run
   ```

## Building for Web
1. **Install Emscripten SDK**
   Download the [Emscripten SDK](https://emscripten.org/docs/getting_started/downloads.html) ([GitHub](https://github.com/emscripten-core/emsdk)).

   Execute the following commands to install and activate the latest Emscripten SDK tools:
   ```
   ./emsdk update
   ./emsdk install latest
   ./emsdk activate latest

   source ./emsdk_env.sh
   ```

2. **Clone this repository:**
   ```
   git clone https://github.com/djsahagun15/PathFinder.git
   cd PathFinder
   ```

3. **Build the project:**
   ```
   emcmake cmake -S . -B build -DPLATFORM=Web
   cmake --build build
   ```

4. **Run the application:**
   Go to the bin folder where the `.html` is located and create a `localhost` using Python:
   ```
   cd bin
   python -m http.server [port](12345)
   ```

   Access the webpage from a browser with the web address:
   ```
   localhost:[port]/PathFinder.html
   ```
