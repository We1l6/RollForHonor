#pragma once
#include "../imGuiManager/imGuiManager.h"
#include "raylib.h"
#include <memory>
class RenderManager
{
  public:
    bool Init(int width, int height, const char *title);
    void SetImGuiManager(std::shared_ptr<ImGuiManager> imGuiManager)
    {
        m_imGuiManager = imGuiManager;
    }
    void Set2DCamera(Vector2 pos, Vector2 target);
    void BeginFrame();
    void EndFrame();
    void Shutdown();

  private:
    Camera2D m_camera;
    std::shared_ptr<ImGuiManager> m_imGuiManager;
};