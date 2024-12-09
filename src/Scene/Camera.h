#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
   public:
    Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 3.0f),
           glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));
    inline glm::mat4 getViewMatrix() {
        return glm::lookAt(m_pos, m_pos + m_front, m_up);
    }
    inline const glm::vec3 getPos() { return m_pos; }

    // Moves with respect to the front vector
    void move(glm::vec3 dv);
    // Rotates based off a rotational x and y value
    void rotate(float drX, float drY);

   private:
    glm::vec3 m_pos;
    glm::vec3 m_front;
    glm::vec3 m_up;
};
