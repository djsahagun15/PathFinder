# **PathFinder - Pathfinding Algorithm Visualizer**
PathFinder is an interactive tool for exploring and experimenting with popular pathfinding algorithms such as BFS, Dijkstra, and A*, on a customizable grid system.

## **This project is currently under development and not yet complete.**

## **TODO**
- **Algorithm Implementation**
   - ~~Implement Breath-First Search (BFS)~~
   - Implement Dijkstra's Algorithm.
   - Implement A* Algorithm.
     
- **Grid Features**
   - Implement grid resizing.
 
- **Visualizations**
   - Visualize the step-by-step process of pathfinding.
   - ~~Highlight the discovered path.~~
 
- **Controls**
   - Add buttons for starting, and pausing/resuming algorithm process, and resetting grid.
   - Add process speed slider.
 
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
- **Space** : Run the selected algorithm (Only BFS as of now)

## Build with CMake
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
