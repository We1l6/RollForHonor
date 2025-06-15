set(MAIN_SOURCES
    "main.cpp")

add_executable(RollForHonor
  ${MAIN_SOURCES}  
  "userInterface/button/button.cpp" "userInterface/button/button.h"
  "userInterface/userInterface.cpp" "userInterface/userInterface.h"
  "loggerManager/loggerManager.cpp" "loggerManager/loggerManager.h")
)

# Link the executable target RollForHonor with the specified libraries privately
target_link_libraries(RollForHonor PRIVATE 
    spdlog::spdlog
    fmt::fmt
    nlohmann_json::nlohmann_json
    raylib)
