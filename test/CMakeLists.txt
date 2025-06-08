# Create a test executable
add_executable(RollForHonorTests
    "test_main.cpp"
)

# Link the test executable
target_link_libraries(RollForHonorTests PRIVATE
    Catch2::Catch2WithMain
    spdlog::spdlog
    fmt::fmt
    nlohmann_json::nlohmann_json
)

# Enable testing and add the test executable
enable_testing()
add_test(NAME RollForHonorTests COMMAND RollForHonorTests)

