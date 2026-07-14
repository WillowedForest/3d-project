
#include "raylib.h"
#include <stdio.h>

const Vector2 screen{1280.0f, 720.0f};
char outPut[5];

namespace std{};

Mesh CreateCustomMesh() {
    Mesh mesh;
    mesh.vertexCount = 4;
    mesh.triangleCount = 2;

    mesh.vertices = (float *)MemAlloc(mesh.vertexCount * 3 * sizeof(float));
    mesh.normals = (float *)MemAlloc(mesh.vertexCount * 3 * sizeof(float));
    mesh.texcoords = (float *)MemAlloc(mesh.vertexCount * 2 * sizeof(float));
    mesh.indices = (unsigned short *)MemAlloc(mesh.triangleCount * 3 * sizeof(unsigned short));

    float positions[] = {
        -1.0f,  -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f
    };

    float normals[] = {
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f
    };

    float texcoords[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };

    unsigned short indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    mesh.vertices = positions;
    mesh.normals = normals;
    mesh.texcoords = texcoords;
    mesh.indices = indices;

    UploadMesh(&mesh, false);

    return mesh;

}


int main() {
    InitWindow(screen.x, screen.y, "haiiiiii");
    SetTargetFPS(165);
    DisableCursor();

    Mesh mesh = CreateCustomMesh();
    Material material = LoadMaterialDefault();
    Model model = LoadModelFromMesh(mesh);
    model.materials[0] = material;

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

        DrawModel(model, Vector3{0.0f, 0.0f, 0.0f}, 1.0f, WHITE);

        DrawGrid(10, 1.0f);

        EndMode3D();
        EndDrawing();

    }

    CloseWindow();

    return 0;
}

