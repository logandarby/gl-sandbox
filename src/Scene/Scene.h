#pragma once

#include <string>

#include "Events/Event.h"

class Scene {
   public:
    Scene(std::string& name) : m_name(name) {};
    virtual ~Scene() = default;

    virtual void onAttach() = 0;
    virtual void onDetach() = 0;
    virtual void onUpdate(const float timestep) = 0;
    virtual void onImGuiRender() = 0;
    virtual void onEvent(const Event& event) = 0;
    ;

   protected:
    const std::string m_name;
};