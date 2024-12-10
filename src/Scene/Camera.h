#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class CameraType {
    PERSPECTIVE,
    ORTHOGRAPHIC,
};

struct CameraSpecification {
    int viewportWidth, viewportHeight;

    CameraType type = CameraType::PERSPECTIVE;
    float fov = 45.0f;

    glm::vec3 pos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
};

class Camera {
   public:
    Camera(CameraSpecification spec);
    inline glm::mat4 getViewMatrix() const {
        return glm::lookAt(m_spec.pos, m_spec.pos + m_spec.front, m_spec.up);
    }
    inline const glm::vec3 getPos() const { return m_spec.pos; }
    inline const glm::mat4 getProjectionMatrix() const {
        return m_projectionMatrix;
    }

    // Moves with respect to the front vector
    void move(glm::vec3 dv);
    // Rotates based off a rotational x and y value
    void rotate(float drX, float drY);

   private:
    CameraSpecification m_spec;
    glm::mat4 m_projectionMatrix;
};
