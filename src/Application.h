#pragma once

#include <string>

#include "Events/Event.h"
#include "Renderer.h"
#include "Scene/Camera.h"
#include "core/MainWindow.h"

class Application {
   public:
    static Application& getInstance(int width, int height, std::string name);

    void run();

   private:
    Application(int width, int height, std::string name);

   private:
    const int m_width, m_height;
    const std::string m_appName;
    MainWindow m_window;
    Renderer m_renderer;
    Camera m_camera;
    bool m_isMenuOpen = false;

   private:
    void keyPressCallback(KeyPressEvent& e);
    void keyReleaseCallback(KeyReleaseEvent& e);
    void mouseOffsetCallback(MouseOffsetEvent& e);
    void mouseScrollCallback(MouseScrollEvent& e);

    void lightingTest();

    // Legacy Test
    void fboTest();
};
