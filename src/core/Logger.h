#pragma once

#include <spdlog/spdlog.h>

#include <memory>

class Logger {
   public:
    static void init();
    static const std::shared_ptr<spdlog::logger> getCoreLogger() {
        return m_coreLogger;
    }
    static const std::shared_ptr<spdlog::logger> getOpenGlLogger() {
        return m_openGlLogger;
    }

   private:
    static std::shared_ptr<spdlog::logger> m_coreLogger;
    static std::shared_ptr<spdlog::logger> m_openGlLogger;
};

// These macros should be used to log-- they can be disabled with release builds

#ifdef _DEBUG
#define LOG_CORE_ERR(...) Logger::getCoreLogger()->error(__VA_ARGS__)
#define LOG_CORE_WARN(...) Logger::getCoreLogger()->warn(__VA_ARGS__)
#define LOG_CORE_INFO(...) Logger::getCoreLogger()->info(__VA_ARGS__)
#define LOG_CORE_TRACE(...) Logger::getCoreLogger()->trace(__VA_ARGS__)

#define LOG_GL_ERR(...) Logger::getOpenGlLogger()->error(__VA_ARGS__)
#define LOG_GL_WARN(...) Logger::getOpenGlLogger()->warn(__VA_ARGS__)
#define LOG_GL_INFO(...) Logger::getOpenGlLogger()->info(__VA_ARGS__)
#define LOG_GL_TRACE(...) Logger::getOpenGlLogger()->trace(__VA_ARGS__)
#else
#define LOG_CORE_ERR(...)
#define LOG_CORE_WARN(...)
#define LOG_CORE_INFO(...)
#define LOG_CORE_TRACE(...)

#define LOG_GL_ERR(...)
#define LOG_GL_WARN(...)
#define LOG_GL_INFO(...)
#define LOG_GL_TRACE(...)
#endif  // _DEBUG
