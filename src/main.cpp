
#include "raylib.h"

const Vector2 screen{800.0f, 480.0f};
char outPut[5];


int main() {
    InitWindow(screen.x, screen.y, "haiiiiii");
    SetTargetFPS(165);

    Camera3D camera;
    camera.position = {10.0f, 10.0f, 10.0f};
    camera.target = Vector3{2.0f, 2.0f, 2.0f};
    camera.up = (Vector3{0.0f, 1.0f, 0.0f});
    camera.fovy = 90.0;
    camera.projection = CAMERA_PERSPECTIVE;

    Vector3 cubePosition = {0.0f, 0.0f, 0.0f};

    while (!WindowShouldClose()) {

        UpdateCamera(&camera, CAMERA_FREE);

        BeginDrawing();

        ClearBackground(PURPLE);

        BeginMode3D(camera);

        DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, PINK);

        DrawGrid(10, 1.0f);

        EndMode3D();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
