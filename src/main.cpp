#include "spdlog/spdlog.h"
#include <fmt/base.h>

#include <raylib.h>

#include "resourceManager/resourceManager.h"
#include "userInterface/button/button.h"
#include "userInterface/scrollBar/scrollBar.h"
int main() {
  InitWindow(1920, 1080, "Hello World");
  SetTargetFPS(60);
  Color bgColor = WHITE;

  // for tests
  std::function<void(Color)> changeBGColor = [&](Color color) {
    bgColor = (bgColor.r == WHITE.r && bgColor.g == WHITE.g &&
               bgColor.b == WHITE.b && bgColor.a == WHITE.a)
                  ? BLACK
                  : WHITE;
  };

  RectanglePro sbHor({1920 / 2, 1080 / 2}, {200, 20}, 0.0f, 10.0f, LIGHTGRAY);
  RectanglePro sbVert({1920 / 2 + 120, 1080 / 2}, {20, 200}, 0.0f, 10.0f, BLUE);
  RectanglePro btn1({1920 / 2, 1080 / 2 + 50}, {150, 50}, 0.0f, 10.0f,
                    LIGHTGRAY);
  RectanglePro btn2({1920 / 2, 1080 / 2 + 105}, {150, 50}, 0.0f, 10.0f, BLUE);
  TextPro text("CLICK");

  ScrollBar sb(RectanglePro(sbHor), TextPro("SCROLL TEXT"), 0.0f, 256.0f, true);
  ScrollBar sb2(RectanglePro(sbVert), TextPro("SCROLL TEXT"), 0.0f, 1000.0f,
                false);
  sb2.setStep(200.0f);
  sb.setColor(LIGHTGRAY);
  sb.setThumbColor(WHITE);
  sb.setThumbHoverColor(GRAY);
  sb.setNormalizedValue(0.5f);
  Button button(btn1, text);
  Button button2(btn2, text,
                 nullptr,                        // onHold
                 [&]() { changeBGColor(BLACK); } // onClickFinished
  );
  button2.setText("A");

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(bgColor);
    button.Update();
    button2.Update();
    sb.Update();
    sb2.Update();
    EndDrawing();
  }

  fmt::print("Hello, world!\n");

  spdlog::info("Welcome to spdlog!");
  spdlog::error("Some error message with arg: {}", 1);

  spdlog::warn("Easy padding in numbers like {:08d}", 12);
  spdlog::critical(
      "Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
  spdlog::info("Support for floats {:03.2f}", 1.23456);
  spdlog::info("Positional args are {1} {0}..", "too", "supported");
  spdlog::info("{:<30}", "left aligned");

  spdlog::set_level(spdlog::level::debug); // Set global log level to debug
  spdlog::debug("This message should be displayed..");

  // change log pattern
  spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");

  // Compile time log levels
  // Note that this does not change the current log level, it will only
  // remove (depending on SPDLOG_ACTIVE_LEVEL) the call on the release code.
  SPDLOG_TRACE("Some trace message with param {}", 42);
  SPDLOG_DEBUG("Some debug message");
}

void testF(int test, int test2) {
  spdlog::info("{:<30}", "left aligned");
  spdlog::info("Positional args are {1} {0}..", "too", "supported");
}