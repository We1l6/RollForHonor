#pragma once

#include "raylib.h"

class ImGuiManager
{
  public:
    ImGuiManager();
    ~ImGuiManager();

    bool Init();
    void BeginFrame();
    void EndFrame();
    void Shutdown();

    bool IsEnabled() const;
    void Enable(bool enable);
    void ShowDebugWindow(float fps);

  private:
    bool m_enabled = true;
    bool m_initialized = false;
};