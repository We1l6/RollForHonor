#include "loggerManager.h"

LoggerManager::LoggerManager() {
  try {
    logger = spdlog::basic_logger_mt("file_logger", "logs/logs.log", true);
    logger->set_level(spdlog::level::trace);
    logger->set_pattern("[%Y-%m-%d %H:%M:%S] [%^%l%$] %v");
    logger->flush_on(spdlog::level::info);
    logger->info("Logger initialized.");
  } catch (const spdlog::spdlog_ex &ex) {
    std::cout << "Logger initialization failed: " << ex.what();
  }
}

LoggerManager &LoggerManager::getInstance() {
  static LoggerManager instance;
  return instance;
}

std::shared_ptr<spdlog::logger> LoggerManager::getLogger() { return logger; }

void LoggerManager::setLogLevel(spdlog::level::level_enum level) {
  logger->set_level(level);
}