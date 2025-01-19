#include <raylib.h>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

#include "pathfinder.hpp"


std::unique_ptr<PathFinder> pf;

void runPathFinder() {
    if (pf) pf->run();
}


int main() {
    pf = std::make_unique<PathFinder>(30, 30);

    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop(runPathFinder, 0, 1);
    #else
        pf->run();
    #endif
    return 0;
}