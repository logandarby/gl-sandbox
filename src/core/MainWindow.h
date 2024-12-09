#pragma once

#include <functional>
#include <string>

#include "../Core/GLCore.h"
#include "../Events/Event.h"

enum CursorMode {
    Disabled = GLFW_CURSOR_DISABLED,
    Normal = GLFW_CURSOR_NORMAL,
};

struct WindowUserPtr {
    std::function<void(Event&)> eventCallback;
    double lastCursorX, lastCursorY;
};

class MainWindow {
   public:
    MainWindow(int width, int height, const std::string& name);
    ~MainWindow();
    MainWindow(MainWindow const&) = delete;
    void operator=(MainWindow const&) = delete;

    void whileOpen(std::function<void(void)> renderLoop);
    void destroy();
    void toggleCursorMode(CursorMode mode);
    inline void setEventCallback(std::function<void(Event&)> callback) {
        m_data.eventCallback = callback;
    }

    inline GLFWwindow* getRawWindowRef() const { return m_window; }

   private:
    bool isOpen();
    GLFWwindow* m_window;
    WindowUserPtr m_data;
    void initEventHandling();
    bool m_isRunning;
};
