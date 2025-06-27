#include "imGuiManager.h"

#include <algorithm>
#include <numeric>

#ifdef ENABLE_DEV_TOOLS
#include "imgui.h"
#include "rlImGui.h"

ImGuiManager::ImGuiManager() = default;
ImGuiManager::~ImGuiManager() = default;

bool ImGuiManager::Init()
{
    if (!m_initialized)
    {
        rlImGuiSetup(true);
        m_initialized = true;
    }
    return m_initialized;
}

void ImGuiManager::BeginFrame() { rlImGuiBegin(); }
void ImGuiManager::EndFrame() { rlImGuiEnd(); }

void ImGuiManager::Shutdown()
{
    if (m_initialized)
    {
        rlImGuiShutdown();
    }
}

bool ImGuiManager::IsEnabled() const { return m_enabled; }
void ImGuiManager::Enable(bool enable) { m_enabled = enable; }

void ImGuiManager::ShowDebugWindow(float fps)
{
    ImGui::Begin("Debug Info");
    ImGui::Text("FPS: %.1f", fps);
    ImGui::Text("Window Size: %d x %d", GetScreenWidth(), GetScreenHeight());
    ImGui::Text("Raylib Version: %s", RAYLIB_VERSION);
    ImGui::Text("CPU Cores: %d", GetMonitorPhysicalWidth(0));
    ImGui::Text("Display: %s", GetMonitorName(0));
    Vector2 mousePos = GetMousePosition();
    ImGui::Text("Mouse: (%.0f, %.0f)", mousePos.x, mousePos.y);

    ImGui::ShowDemoWindow();
    ImGui::End();
}

void ImGuiManager::ShowPerformanceWindow()
{
    static bool initialized = false;
    static bool paused = false;

    if (!initialized) {
        PerformanceMonitor::StartMonitoring();
        initialized = true;
    }

    ImGui::Begin("Performance Monitor");

    if (ImGui::Button(paused ? "Resume" : "Pause")) {
        paused = !paused;
    }

    ImGui::SameLine();
    ImGui::Text(paused ? "Paused" : "Running");

    if (!paused) {
        PerformanceMonitor::Update();
    }

    // --- CPU Usage ---
    const auto& cpuHistory = PerformanceMonitor::GetCpuHistory();
    ImGui::Text("CPU Usage:");
    if (!cpuHistory.empty())
    {
        float maxCpu = *std::max_element(cpuHistory.begin(), cpuHistory.end());
        float minCpu = *std::min_element(cpuHistory.begin(), cpuHistory.end());
        float avgCpu = std::accumulate(cpuHistory.begin(), cpuHistory.end(), 0.0f) / cpuHistory.size();
        float y_min = minCpu;
        float y_max = maxCpu;

        if (y_min == y_max) {
            y_max = y_min + 1.0f;
        }

        ImGui::PlotLines("##cpu", cpuHistory.data(), (int)cpuHistory.size(), 0, nullptr, 0.0f, y_max * PLOT_SCALE_PADDING, ImVec2(0, PLOT_HEIGHT));

        ImGui::SameLine();
        ImGui::SetCursorPosX(PLOT_STATISTICS_POSITION);
        ImGui::Text("Min: %.1f%%", minCpu);
        ImGui::SameLine();
        ImGui::Text("Avg: %.1f%%", avgCpu);
        ImGui::SameLine();
        ImGui::Text("Max: %.1f%%", maxCpu);
    }

    ImGui::Separator();

    // --- Memory Usage ---
    const auto& memHistory = PerformanceMonitor::GetMemHistory();
    ImGui::Text("Memory Usage (MB):");

    if (!memHistory.empty()) {
        float avgMem = std::accumulate(memHistory.begin(), memHistory.end(), 0.0f) / memHistory.size();
        float minMem = *std::min_element(memHistory.begin(), memHistory.end());
        float maxMem = *std::max_element(memHistory.begin(), memHistory.end());

        ImGui::PlotLines("##mem", memHistory.data(), static_cast<int>(memHistory.size()),
            0, nullptr, 0.0f, maxMem * PLOT_SCALE_PADDING, ImVec2(0, PLOT_HEIGHT));

        ImGui::SameLine();
        ImGui::SetCursorPosX(PLOT_STATISTICS_POSITION);
        ImGui::Text("Min: %.1f MB", minMem);
        ImGui::SameLine();
        ImGui::Text("Avg: %.1f MB", avgMem);
        ImGui::SameLine();
        ImGui::Text("Max: %.1f MB", maxMem);
    }

    ImGui::End();
}


#else

ImGuiManager::ImGuiManager() = default;
ImGuiManager::~ImGuiManager() = default;

bool ImGuiManager::Init() { return false; }
void ImGuiManager::BeginFrame() {}
void ImGuiManager::EndFrame() {}
void ImGuiManager::Shutdown() {}

bool ImGuiManager::IsEnabled() const { return false; }
void ImGuiManager::Enable(bool) {}
void ImGuiManager::ShowDebugWindow(float) {}
#endif