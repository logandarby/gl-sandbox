#include "Camera.h"

#include "../core/Core.h"

Camera::Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up)
    : m_pos{pos}, m_front{front}, m_up{up} {}

void Camera::move(const glm::vec3 dv) {
    using namespace glm;

    const vec3 right = normalize(cross(m_front, m_up));
    const vec3 forward = normalize(cross(m_up, right));
    const mat3 changeOfBasis = mat3{right, m_up, forward};
    m_pos += changeOfBasis * dv;
}

void Camera::rotate(const float dx, const float dy) {
    using namespace glm;

    const vec3 right = normalize(cross(m_front, m_up));
    const auto yRotation = glm::rotate(mat4(1.0f), radians(dy), right);
    const auto fullRotation =
        glm::rotate(yRotation, radians(dx), vec3(0.0f, 1.0f, 0.0f));

    m_front = glm::normalize(fullRotation * glm::vec4(m_front, 0.0f));
}
