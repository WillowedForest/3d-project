#include "raylib.h"
#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>


const Vector2 screen{800.0f, 480.0f};
char outPut[5];

bool notopen = false;

using json = nlohmann::json;

Mesh CreateCustomMesh(float size = 1.0f) {
    Mesh mesh = { 0 };
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
        -s, -s, -s,    s, -s, -s,    s, s,  s,   -s, -s,  s,
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
        -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f
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


    size_t vCount = sizeof(vertices) / sizeof(vertices[0]);
    for (size_t i = 0; i < vCount; i++) mesh.vertices[i] = vertices[i];

    size_t nCount = sizeof(normals) / sizeof(normals[0]);
    for (size_t i = 0; i < nCount; i++) mesh.normals[i] = normals[i];

    size_t tCount = sizeof(texcoords) / sizeof(texcoords[0]);
    for (size_t i = 0; i < tCount; i++) mesh.texcoords[i] = texcoords[i];

    size_t iCount = sizeof(indices) / sizeof(indices[0]);
    for (size_t i = 0; i < iCount; i++) mesh.indices[i] = indices[i];

    UploadMesh(&mesh, false);

    return mesh;

}

//void SavePosition(Vector3 vec){
//    json data;
//
//    data["x"] = vec.x;
//    data["y"] = vec.y;
//    data["z"] = vec.z;
//
//    std::ofstream outfile("test.json");
//
//    if(!outfile.is_open()){
//        notopen = true;
//    }
//
//    outfile << data.dump(4);
//    outfile.close();
//
//}


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

    Mesh mesh = CreateCustomMesh();
    Model model = LoadModelFromMesh(mesh);
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].color = WHITE;

    while (!WindowShouldClose()) {

        UpdateCamera(&camera, CAMERA_FREE);

        BeginDrawing();

        ClearBackground(PURPLE);
        
        BeginMode3D(camera);

       // DrawModelEx(model, Vector3{ 1.0f, 1.0f, 1.0f }, Vector3{ 1.0f, 1.0f, 0.0f },30.0f, Vector3{ 2.0f, 2.0f, 2.0f }, WHITE);
        DrawModel(model, Vector3{ 0.0f,0.0f,0.0f }, 1.0f, WHITE);
       
        DrawCube(Vector3{ 0.0f,0.0f,0.0f }, 5, 5, 5, WHITE);

        DrawGrid(500, 2.0f);

        EndMode3D();
        EndDrawing();
    }
    //if(IsKeyPressed(KEY_T)){
    ////    SavePosition(camera.position);
    //}

    CloseWindow();

    return 0;
}
