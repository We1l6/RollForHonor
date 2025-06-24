#pragma once
#include "raylib.h"

class RenderManager{

    public:
    bool Init(int width, int height, const char* title);
    void Set2DCamera(Vector2 pos, Vector2 target);
    void BeginFrame();
    void EndFrame();
    void Shutdown();
    private:
    Camera2D m_camera;
};