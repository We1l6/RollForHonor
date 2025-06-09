set(MAIN_SOURCES
    "main.cpp")

add_executable(RollForHonor
  ${MAIN_SOURCES})

# Link the executable target RollForHonor with the specified libraries privately
target_link_libraries(RollForHonor PRIVATE 
    spdlog::spdlog
    fmt::fmt
    nlohmann_json::nlohmann_json)