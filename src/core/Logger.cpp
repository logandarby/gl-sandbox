#include "Logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>

std::shared_ptr<spdlog::logger> Logger::m_coreLogger;
std::shared_ptr<spdlog::logger> Logger::m_openGlLogger;

void Logger::init() {
    spdlog::set_pattern("%^[%T] %n: %v%$");

    m_coreLogger = spdlog::stdout_color_mt("App");
    m_coreLogger->set_level(spdlog::level::trace);

    m_openGlLogger = spdlog::stdout_color_mt("OpenGL");
    m_openGlLogger->set_level(spdlog::level::trace);
}
