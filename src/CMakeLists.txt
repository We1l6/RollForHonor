set(MAIN_SOURCES
    "main.cpp")

add_executable(RollForHonor
  ${MAIN_SOURCES}  
  "userInterface/userInterface.cpp" "userInterface/userInterface.h" 
  "userInterface/button/button.cpp" "userInterface/button/button.h"
  "userInterface/scrollBar/scrollBar.cpp" "userInterface/scrollBar/scrollBar.h"
  "userInterface/checkBox/checkBox.cpp" "userInterface/checkBox/checkBox.h"
  "userInterface/UIUtils/RectanglePro/RectanglePro.cpp" "userInterface/UIUtils/RectanglePro/RectanglePro.h"
  "userInterface/UIUtils/TextPro/TextPro.cpp" "userInterface/UIUtils/TextPro/TextPro.h"
  "userInterface/UIUtils/UISkin/UISkin.cpp" "userInterface/UIUtils/UISkin/UISkin.h"
  "userInterface/UIUtils/TextBox/TextBox.cpp" "userInterface/UIUtils/TextBox/TextBox.h"
  "managers/loggerManager/loggerManager.cpp" "managers/loggerManager/loggerManager.h"
  "managers/resourceManagers/soundManager/soundManager.cpp" "managers/resourceManagers/soundManager/soundManager.h"
  "managers/resourceManagers/textureManager/textureManager.cpp" "managers/resourceManagers/textureManager/textureManager.h"
  "managers/resourceManagers/fontManager/fontManager.cpp" "managers/resourceManagers/fontManager/fontManager.h"
  "managers/renderManager/renderManager.cpp" "managers/renderManager/renderManager.h"
  "managers/sceneManager/sceneManager.cpp" "managers/sceneManager/sceneManager.h"
  "managers/imGuiManager/imGuiManager.h" "managers/imGuiManager/imGuiManager.cpp"
  "scenes/mainMenuScene/mainMenuScene.cpp" "scenes/mainMenuScene/mainMenuScene.h"
  "scenes/scene/scene.h"
  "devkit/windows/performanceMonitor/performanceMonitor.h" "devkit/windows/performanceMonitor/performanceMonitor.cpp"
)

# Link the executable target RollForHonor with the specified libraries privately
target_link_libraries(RollForHonor PRIVATE 
    spdlog::spdlog
    fmt::fmt
    nlohmann_json::nlohmann_json
    raylib
) 

if(ENABLE_DEV_TOOLS)
message(STATUS "DEV_TOOLS support enabled")
target_compile_definitions(RollForHonor PRIVATE ENABLE_DEV_TOOLS)
target_link_libraries(RollForHonor PRIVATE 
    imgui
    rlImGui)
else()
    message(STATUS "DEV_TOOLS support disabled")
endif()