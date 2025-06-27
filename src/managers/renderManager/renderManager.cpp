#include "renderManager.h"


bool RenderManager::Init(int width, int height, const char *title)
{
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(width, height, title);
    SetExitKey(KEY_BACKSPACE);
    SetTargetFPS(60);
    return IsWindowReady();
}

void RenderManager::Set2DCamera(Vector2 pos, Vector2 target) {}

void RenderManager::BeginFrame()
{
    BeginDrawing();
    ClearBackground(BLACK);

#ifdef ENABLE_DEV_TOOLS
    if (m_imGuiManager->IsEnabled())
    {
        m_imGuiManager->BeginFrame();
    }
#endif

    // BeginMode2D(m_camera);
}

void RenderManager::EndFrame()
{
#ifdef ENABLE_DEV_TOOLS
    if (m_imGuiManager->IsEnabled())
    {
        m_imGuiManager->ShowDebugWindow(GetFPS());
        m_imGuiManager->ShowPerformanceWindow();
        m_imGuiManager->EndFrame();
    }
#endif

    // EndMode2D();
    DrawFPS(10, 10);
    EndDrawing();
}

void RenderManager::Shutdown() { CloseWindow(); }