#pragma once

#include "../Scene.h"

class LightingScene : public Scene {
   public:
    virtual void onAttach() override;
    virtual void onDetach() override;
    virtual void onUpdate(const float timestep) override;
    virtual void onImGuiRender() override {};
    virtual void onEvent(const Event& event) override {};
};