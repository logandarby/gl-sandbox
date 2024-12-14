#include "CameraController.h"
#include "Core/GLCore.h"

void CameraController::onEvent(Event& e) {
    EventDispatcher dispatcher(e);
    dispatcher.dispatch<KeyPressEvent>([&](KeyPressEvent& e) {
        m_onKeyPress(e);
    });
    dispatcher.dispatch<KeyReleaseEvent>([&](KeyReleaseEvent& e) {
        m_onKeyRelease(e);
    });
    dispatcher.dispatch<MouseOffsetEvent>([&](MouseOffsetEvent& e) {
        m_onMouseOffset(e);
    });
}

void CameraController::onUpdate() {
    m_camera.move(m_deltaPos);
}

void CameraController::m_onKeyPress(KeyPressEvent& e) {
    m_move(e.getKeyCode(), m_spec.moveSpeed);
}
void CameraController::m_onKeyRelease(KeyReleaseEvent& e) {
    m_move(e.getKeyCode(), -m_spec.moveSpeed);
}
void CameraController::m_onMouseOffset(MouseOffsetEvent& e) {
    m_deltaRot.x = e.xOffset * -m_spec.rotSpeed;
    m_deltaRot.y = e.yOffset * -m_spec.rotSpeed;
    m_camera.rotate(m_deltaRot.x, m_deltaRot.y);
}

void CameraController::m_move(const GL::KeyCode keycode, const float delta) {
    switch (keycode) {
        case GL::KeyCode::W:
            m_deltaPos.z += delta;
            break;
        case GL::KeyCode::A:
            m_deltaPos.x -= delta;
            break;
        case GL::KeyCode::S:
            m_deltaPos.z -= delta;
            break;
        case GL::KeyCode::D:
            m_deltaPos.x += delta;
            break;
        case GL::KeyCode::SPACE:
            m_deltaPos.y += delta;
            break;
        case GL::KeyCode::LEFT_SHIFT:
            m_deltaPos.y -= delta;
            break;
    }
}
