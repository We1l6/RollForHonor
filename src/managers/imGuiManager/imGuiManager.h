#pragma once

#include "raylib.h"
#include "../../devkit/windows/performanceMonitor/performanceMonitor.h"

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
    void ShowPerformanceWindow();

  private:
    float m_maxFrameTime{0.0f};
    bool m_enabled{true};
    bool m_initialized{false};

    static constexpr float PLOT_HEIGHT = 100.0f;
    static constexpr float PLOT_STATISTICS_POSITION = 15.0f; 
    static constexpr float PLOT_SCALE_PADDING = 1.2f;
};