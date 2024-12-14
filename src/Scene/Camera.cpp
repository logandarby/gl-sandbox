#include "Camera.h"
#include "../core/Core.h"

namespace Utils {
    glm::mat4 getProjectionMatrix(CameraSpecification& spec) {
        switch (spec.type) {
            case CameraType::PERSPECTIVE:
                return glm::perspective(
                    glm::radians(spec.fov),
                    (float)spec.viewportWidth / (float)spec.viewportHeight,
                    0.1f, 100.0f
                );
            case CameraType::ORTHOGRAPHIC:
                return glm::ortho(
                    0.0f, (float)spec.viewportWidth, 0.0f,
                    (float)spec.viewportHeight, 0.1f, 100.0f
                );
            default:
                CORE_ASSERT(false);
                return glm::mat4(1.0f);
        }
    }
}  // namespace Utils

Camera::Camera(CameraSpecification spec) :
    m_spec(spec), m_projectionMatrix(Utils::getProjectionMatrix(spec)) {}

void Camera::move(const glm::vec3 dv) {
    using namespace glm;

    const vec3 right = normalize(cross(m_spec.front, m_spec.up));
    const vec3 forward = normalize(cross(m_spec.up, right));
    const mat3 changeOfBasis = mat3{ right, m_spec.up, forward };
    m_spec.pos += changeOfBasis * dv;
}

void Camera::rotate(const float dx, const float dy) {
    using namespace glm;

    const vec3 right = normalize(cross(m_spec.front, m_spec.up));
    const auto yRotation = glm::rotate(mat4(1.0f), radians(dy), right);
    const auto fullRotation =
        glm::rotate(yRotation, radians(dx), vec3(0.0f, 1.0f, 0.0f));

    m_spec.front = glm::normalize(fullRotation * glm::vec4(m_spec.front, 0.0f));
}
