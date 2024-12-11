#include <raylib.h>
#include "pathfinder.hpp"


int main() {
    PathFinder pf (25, 25);
    pf.run();
    return 0;
}