#include <raylib.h>
#include "pathfinder.hpp"


int main() {
    PathFinder pf (10, 10);
    pf.run();
    return 0;
}