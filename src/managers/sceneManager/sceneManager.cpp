#include "sceneManager.h"


SceneManager::~SceneManager()
{
    while (!m_scenes.empty())
    {
        m_scenes.top()->Unload();
        m_scenes.pop();
    }
}


bool SceneManager::isEmpty() const { return m_scenes.empty(); }


void SceneManager::ChangeScene(std::unique_ptr<Scene> scene)
{
    if (!m_scenes.empty())
    {
        m_scenes.top()->Unload();
        m_scenes.pop();
    }
    m_scenes.push(std::move(scene));
    m_scenes.top()->Init(m_renderManager, m_textureManager, m_fontManager,
                         m_soundManager);
}


void SceneManager::PushScene(std::unique_ptr<Scene> scene)
{
    if (!m_scenes.empty())
    {
        m_scenes.top()->Unload();
    }
    m_scenes.push(std::move(scene));
    m_scenes.top()->Init(m_renderManager, m_textureManager, m_fontManager,
                         m_soundManager);
}


void SceneManager::PopScene()
{
    if (!m_scenes.empty())
    {
        m_scenes.top()->Unload();
        m_scenes.pop();
    }
}


void SceneManager::Update(float deltaTime)
{
    if (!m_scenes.empty())
    {
        m_scenes.top()->Update(deltaTime);
        if (m_scenes.top()->ShouldExit())
        {
            PopScene();
        }
    }
}

void SceneManager::Render()
{
    if (!m_scenes.empty())
    {
        m_renderManager->BeginFrame();
        m_scenes.top()->Render();
        m_renderManager->EndFrame();
    }
}