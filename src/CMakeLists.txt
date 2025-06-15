set(MAIN_SOURCES
    "main.cpp")

add_executable(RollForHonor
  ${MAIN_SOURCES}  
  "userInterface/button/button.cpp" "userInterface/button/button.h"
  "userInterface/userInterface.cpp" "userInterface/userInterface.h" 
  "userInterface/UIUtils/RectanglePro/RectanglePro.cpp" "userInterface/UIUtils/RectanglePro/RectanglePro.h"
  "userInterface/UIUtils/TextPro/TextPro.cpp" "userInterface/UIUtils/TextPro/TextPro.h"
  "userInterface/scrollbar/scrollBar.cpp" "userInterface/scrollBar/scrollBar.h"
  "loggerManager/loggerManager.cpp" "loggerManager/loggerManager.h"
)

# Link the executable target RollForHonor with the specified libraries privately
target_link_libraries(RollForHonor PRIVATE 
    spdlog::spdlog
    fmt::fmt
    nlohmann_json::nlohmann_json
    raylib)