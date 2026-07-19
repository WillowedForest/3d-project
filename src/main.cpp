
#include "raylib.h"
#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>


const Vector2 screen{800.0f, 480.0f};
char outPut[5];

using json = nlohmann::json;

Mesh CreateCustomMesh(float size = 1.0f) {
    Mesh mesh;
    mesh.vertexCount = 24;
    mesh.triangleCount = 12;

    mesh.vertices = (float *)MemAlloc(mesh.vertexCount * 3 * sizeof(float));
    mesh.normals = (float *)MemAlloc(mesh.vertexCount * 3 * sizeof(float));
    mesh.texcoords = (float *)MemAlloc(mesh.vertexCount * 2 * sizeof(float));
    mesh.indices = (unsigned short *)MemAlloc(mesh.triangleCount * 3 * sizeof(unsigned short));

    float s = size / 2.0f;

    float vertices[] = {
        // Front face (Z+)
        -s, -s,  s,    s, -s,  s,    s,  s,  s,   -s,  s,  s,
        // Back face (Z-)
        -s, -s, -s,   -s,  s, -s,    s,  s, -s,    s, -s, -s,
        // Top face (Y+)
        -s,  s, -s,   -s,  s,  s,    s,  s,  s,    s,  s, -s,
        // Bottom face (Y-)
        -s, -s, -s,    s, -s, -s,    s, -s,  s,   -s, -s,  s,
        // Right face (X+)
         s, -s, -s,    s,  s, -s,    s,  s,  s,    s, -s,  s,
        // Left face (X-)
        -s, -s, -s,   -s, -s,  s,   -s,  s,  s,   -s,  s, -s
    };

    float normals[] = {
        // Front
        0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,
        // Back
        0.0f, 0.0f, -1.0f,   0.0f, 0.0f, -1.0f,   0.0f, 0.0f, -1.0f,   0.0f, 0.0f, -1.0f,
        // Top
        0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 0.0f,
        // Bottom
        0.0f, -1.0f, 0.0f,   0.0f, -1.0f, 0.0f,   0.0f, -1.0f, 0.0f,   0.0f, -1.0f, 0.0f,
        // Right
        1.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f,
        // Left
        -1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f
    };

    float texcoords[] = {
        0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f,  0.0f, 1.0f,  // Front
        0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f,  0.0f, 1.0f,  // Back
        0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f,  0.0f, 1.0f,  // Top
        0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f,  0.0f, 1.0f,  // Bottom
        0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f,  0.0f, 1.0f,  // Right
        0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f,  0.0f, 1.0f   // Left
    };

    unsigned short indices[] = {
        0, 1, 2,    0, 2, 3,      // Front
        4, 5, 6,    4, 6, 7,      // Back
        8, 9, 10,   8, 10, 11,    // Top
        12, 13, 14, 12, 14, 15,   // Bottom
        16, 17, 18, 16, 18, 19,   // Right
        20, 21, 22, 20, 22, 23    // Left
    };

    mesh.vertices = vertices;
    mesh.normals = normals;
    mesh.texcoords = texcoords;
    mesh.indices = indices;

    return mesh;

}

void SavePosition(Vector3 vec, const char* filename){
    json data;

    data["x"] = vec.x;
    data["y"] = vec.y;
    data["z"] = vec.z;

    std::ofstream file(filename);
    file << data.dump(4);
    file.close();

}

int main() {
    InitWindow(screen.x, screen.y, "haiiiiii");
    SetTargetFPS(165);

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

        DrawModel(model, Vector3{0.0f, 0.0f, 0.0f},1.0f, WHITE);
        DrawGrid(1000, 1.0f);

        EndMode3D();
        EndDrawing();


    }


    std::ofstream outFile("newfile.txt"); // Specify the file name

    // Check if the file is open
    if (outFile.is_open()) {
        outFile << "Hello, this file is next to the executable!"; // Write to the file
        outFile.close(); // Close the file
    } else {
        // Handle error
        std::cerr << "Unable to open file";
    }

    CloseWindow();

    return 0;
}
