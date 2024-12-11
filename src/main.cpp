#include <raylib.h>
#include "pathfinder.hpp"


int main() {
    PathFinder pf (30, 30);
    pf.run();
    return 0;
}