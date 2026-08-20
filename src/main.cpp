#include "raylib.h"
#include "nlohmann/json.hpp"
#include <cstddef>
#include <functional>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>


const Vector2 screen{1280.0f, 720.0f};
char outPut[5];

const Vector3 Center = {0.0f, 0.0f, 0.0f};

const char* saveFilPeath = "src/res/savefile.json";

using json = nlohmann::json;

Camera3D camera;

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

void SaveCamersPosition(){
    json data;

    data["posx"] = camera.position.x;
    data["posy"] = camera.position.y;
    data["posz"] = camera.position.z;
    data["rotx"] = camera.target.x;
    data["roty"] = camera.target.y;
    data["rotz"] = camera.target.z;

    std::ofstream outfile(saveFilPeath);

    outfile << data.dump();
    outfile.close();

}

void LoadPlayerPosition(){
    std::ifstream file(saveFilPeath);

    json data = json::parse(file);
    file.close();

    camera.target = Vector3{data["rotx"].get<float>(), data["roty"].get<float>(), data["rotz"].get<float>()};
    camera.position = Vector3{data["posx"].get<float>(), data["posy"].get<float>(), data["posz"].get<float>()};

}

int main() {
    InitWindow(screen.x, screen.y, "haiiiiii");
    InitAudioDevice();
    SetTargetFPS(165);
    DisableCursor();


    camera.position = {10.0f, 10.0f, 10.0f};
    camera.target = Vector3{2.0f, 2.0f, 2.0f};
    camera.up = (Vector3{0.0f, 1.0f, 0.0f});
    camera.fovy = 90.0;
    camera.projection = CAMERA_PERSPECTIVE;

    Vector3 cubePosition = {0.0f, 0.0f, 0.0f};

    //loading shdaers
    Shader spinningRainbowShader = LoadShader("src/res/shaders/vertex.glsl", "src/res/shaders/fragment.glsl");
    int uTimeLoc = GetShaderLocation(spinningRainbowShader, "uTime");

    Shader transFlag = LoadShader("src/res/shaders/trans-vert.glsl", "src/res/shaders/trans-frag.glsl");

    //loading models
    Model floorModel = LoadModelFromMesh(CreateCustomMesh());
    floorModel.materials[0] = LoadMaterialDefault();

   /*Model teapot = {0};
    teapot = LoadModel("src/res/model/teapot.obj");
    teapot.materials[0] = LoadMaterialDefault();
    teapot.materials[0].shader = spinningRainbowShader;
*/

   Model world = {0};
   world = LoadModel("src/res/model/world.obj");

    Sound funny = LoadSound("src/res/sound/funny.wav");

    while (!WindowShouldClose()) {

        UpdateCamera(&camera, CAMERA_FREE);

        float time = GetTime();
        SetShaderValue(spinningRainbowShader, uTimeLoc, &time, SHADER_UNIFORM_FLOAT);

        BeginDrawing();

        ClearBackground(DARKGRAY);

        DrawFPS(10, 10);

        BeginMode3D(camera);

        //floor
        DrawModelEx(floorModel, Vector3{ 1.0f, 1.0f, 1.0f }, Vector3{ 0.0f, 0.0f, 0.0f },30.0f, Vector3{ 20.0f, 2.0f, 20.0f }, WHITE);

        DrawModelEx(world, Vector3{ 0.0f, 1.8f, 0.0f }, Vector3{ 0.0f, 0.0f, 0.0f },30.0f, Vector3{ 0.05f, 0.05f, 0.05f }, WHITE);

        /* for (int i = 0; i <= 20; i++) {

            Vector3 pos = Vector3{0.0f + i * 3, 1.8f, 0.0f};

            DrawModelEx(world, pos, Vector3{ 0.0f, 0.0f, 0.0f },30.0f, Vector3{ 0.05f, 0.05f, 0.05f }, WHITE);
            }

         for (int i = 0; i <= 20; i++) {

            Vector3 pos = Vector3{0.0f + i * 3, 1.8f * 2, 0.0f};

            DrawModelEx(world, pos, Vector3{ 0.0f, 0.0f, 0.0f },30.0f, Vector3{ 0.05f, 0.05f, 0.05f }, WHITE);
            }

         for (int i = 0; i <= 20; i++) {

            Vector3 pos = Vector3{0.0f + i * 3, 1.8f * 3, 0.0f};

            DrawModelEx(world, pos, Vector3{ 0.0f, 0.0f, 0.0f },30.0f, Vector3{ 0.05f, 0.05f, 0.05f }, WHITE);
            }

         for (int i = 0; i <= 20; i++) {

            Vector3 pos = Vector3{0.0f + i * 3, 1.8f * 4, 0.0f};

            DrawModelEx(world, pos, Vector3{ 0.0f, 0.0f, 0.0f },30.0f, Vector3{ 0.05f, 0.05f, 0.05f }, WHITE);
            }

         for (int i = 0; i <= 20; i++) {

            Vector3 pos = Vector3{0.0f + i * 3, 1.8f * 5, 0.0f};

            DrawModelEx(world, pos, Vector3{ 0.0f, 0.0f, 0.0f },30.0f, Vector3{ 0.05f, 0.05f, 0.05f }, WHITE);
            }*/

        //DrawGrid(500, 1.0f);

        EndMode3D();
        EndDrawing();

        if(IsKeyPressed(KEY_U)){
            PlaySound(funny);
        }

        if(IsKeyPressed(KEY_T)){
            SaveCamersPosition();
        }

        if (IsKeyPressed(KEY_Y)) {
            LoadPlayerPosition();
        }

    }

    UnloadModel(floorModel);
    //UnloadModel(teapot);
    UnloadModel(world);

    UnloadSound(funny);

    CloseWindow();

    return 0;
}
