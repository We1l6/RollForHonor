#pragma once

#include <iostream>
#include <memory>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

#define LOG_TRACE(...)                                                         \
  LoggerManager::getInstance().getLogger()->trace(__VA_ARGS__)
#define LOG_DEBUG(...)                                                         \
  LoggerManager::getInstance().getLogger()->debug(__VA_ARGS__)
#define LOG_INFO(...)                                                          \
  LoggerManager::getInstance().getLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)                                                          \
  LoggerManager::getInstance().getLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)                                                         \
  LoggerManager::getInstance().getLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...)                                                      \
  LoggerManager::getInstance().getLogger()->critical(__VA_ARGS__)

class LoggerManager {
public:
  static LoggerManager &getInstance();
  std::shared_ptr<spdlog::logger> getLogger();
  void setLogLevel(spdlog::level::level_enum level);

private:
  LoggerManager();

  std::shared_ptr<spdlog::logger> logger;

  LoggerManager(const LoggerManager &) = delete;
  LoggerManager &operator=(const LoggerManager &) = delete;
};
