#include <raylib.h>

#define WINW    700
#define WINH    700


int main() {
    InitWindow(WINW, WINH, "PathFinder");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}