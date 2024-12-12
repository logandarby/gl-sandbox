#pragma once

#include <functional>
#include <string>

#include "../Events/Event.h"
#include "Renderer/RendererTypes.h"

struct WindowUserPtr {
    std::function<void(Event &)> eventCallback;
    double lastCursorX, lastCursorY;
};

struct GLFWwindow;

class MainWindow {
  public:
    MainWindow(int width, int height, const std::string &name);
    ~MainWindow();
    MainWindow(MainWindow const &) = delete;
    void operator=(MainWindow const &) = delete;

    void whileOpen(std::function<void(void)> renderLoop);
    void destroy();
    void toggleCursorMode(GL::CursorMode mode);
    inline void setEventCallback(std::function<void(Event &)> callback) {
        m_data.eventCallback = callback;
    }

    inline GLFWwindow *getRawWindowRef() const { return m_window; }

  private:
    bool isOpen();
    GLFWwindow *m_window;
    WindowUserPtr m_data;
    void initEventHandling();
    bool m_isRunning;
};
