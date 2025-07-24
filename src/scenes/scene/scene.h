#pragma once


class SceneManager;

#include "../../managers/renderManager/renderManager.h"
#include "../../managers/resourceManagers/fontManager/fontManager.h"
#include "../../managers/resourceManagers/soundManager/soundManager.h"
#include "../../managers/resourceManagers/textureManager/textureManager.h"
#include "../../managers/sceneManager/sceneManager.h"
#include <memory>


class Scene
{
  public:
    virtual ~Scene() = default;
    virtual void Init(std::shared_ptr<RenderManager> renderManager,
                      std::shared_ptr<TextureManager> textureManager,
                      std::shared_ptr<FontManager> fontManager,
                      std::shared_ptr<SoundManager> soundManager,
                      std::weak_ptr<SceneManager> sceneManager) = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;
    virtual void Unload() = 0;
    virtual bool ShouldExit() = 0;

		std::string getName(){return m_name;}

  protected:
    void setName(std::string name){m_name = name;}
    std::weak_ptr<SceneManager> m_sceneManager;
		std::string m_name;
};
