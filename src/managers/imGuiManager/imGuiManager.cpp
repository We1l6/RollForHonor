#include "imGuiManager.h"

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