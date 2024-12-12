#pragma once

#include <string>

#include "ApplicationSpec.h"
#include "Events/Event.h"
#include "Scene/Scene.h"
#include "Util/Timestep.h"
#include "core/MainWindow.h"

class Application {
   public:
    Application(const ApplicationSpec& spec);
    void run();
    void setScene(Ref<Scene> scene);

   private:
    const int m_width, m_height;
    const std::string m_appName;
    MainWindow m_window;
    WeakRef<Scene> m_currentScene;
    Timestep::CurrentTime m_lastTime;

   private:
    void onEvent(Event& e);
    void keyPressCallback(KeyPressEvent& e);
};
