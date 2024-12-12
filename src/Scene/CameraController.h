#pragma once

#include "Camera.h"
#include "Events/Event.h"
#include "Renderer/RendererTypes.h"

struct CameraControllerSpec {
    float moveSpeed = 0.1f;
    float rotSpeed = 0.1f;
};

class CameraController {
  public:
    CameraController(CameraSpecification camSpec, CameraControllerSpec controllerSpec)
        : m_camera(camSpec), m_spec(controllerSpec), m_deltaPos{0, 0, 0}, m_deltaRot{0, 0} {}

    void onUpdate();
    void onEvent(Event &e);

    inline const Camera &getCamera() const { return m_camera; }

  private:
    Camera m_camera;
    CameraControllerSpec m_spec;
    glm::vec3 m_deltaPos;
    glm::vec2 m_deltaRot;

  private:
    void m_onKeyPress(KeyPressEvent &e);
    void m_onKeyRelease(KeyReleaseEvent &e);
    void m_onMouseOffset(MouseOffsetEvent &e);
    void m_move(GL::KeyCode keycode, float delta);
};
