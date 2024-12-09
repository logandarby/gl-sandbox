#include "Application.h"

#include <imgui.h>

#include "Events/Event.h"
#include "FBO.h"
#include "IndexBuffer.h"
#include "Math/MatrixUtils.h"
#include "Model/CubeModel.h"
#include "Model/NormalCubeModel.h"
#include "Model/RectangleModel.h"
#include "Scene/Light.h"
#include "Scene/Material.h"
#include "Shader.h"
#include "Texture/CubemapTexture.h"
#include "Texture/Texture2D.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/vec3.hpp"

static const float POS_DELTA = 0.1f;
static const double MOUSE_SENSITIVITY = 0.08;
static float dx = 0, dy = 0, dz = 0;
static double drx = 0, dry = 0;
static const glm::vec3 cubePositions[] = {
    glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
    glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

Application &Application::getInstance(const int width, const int height,
                                      const std::string name) {
    static Application app(width, height, name);
    return app;
}

void move(const int keycode, const float delta) {
    switch (keycode) {
        case GLFW_KEY_W:
            dz += delta;
            break;
        case GLFW_KEY_A:
            dx -= delta;
            break;
        case GLFW_KEY_S:
            dz -= delta;
            break;
        case GLFW_KEY_D:
            dx += delta;
            break;
        case GLFW_KEY_SPACE:
            dy += delta;
            break;
        case GLFW_KEY_LEFT_SHIFT:
            dy -= delta;
            break;
    }
}

void Application::keyReleaseCallback(KeyReleaseEvent &e) {
    if (!m_isMenuOpen) {
        move(e.keycode, POS_DELTA);
    }
}

// Based on the key, modifies dx or dy
void Application::keyPressCallback(KeyPressEvent &e) {
    switch (e.keycode) {
        case GLFW_KEY_Q:
            m_window.destroy();
            break;
        case GLFW_KEY_ESCAPE:
            m_isMenuOpen = !m_isMenuOpen;
            if (m_isMenuOpen) {
                m_window.toggleCursorMode(CursorMode::Normal);
            } else {
                m_window.toggleCursorMode(CursorMode::Disabled);
            }
            break;
    }
    if (!m_isMenuOpen) {
        move(e.keycode, -POS_DELTA);
    }
}

void Application::mouseScrollCallback(MouseScrollEvent &e) {}

void Application::mouseOffsetCallback(MouseOffsetEvent &e) {
    if (m_isMenuOpen) return;
    drx = e.xOffset * -MOUSE_SENSITIVITY;
    dry = e.yOffset * -MOUSE_SENSITIVITY;
    m_camera.rotate(drx, dry);
}

Application::Application(const int width, const int height,
                         const std::string name)
    : m_width{width},
      m_height{height},
      m_appName{name},
      m_window{width, height, name},
      m_renderer{},
      m_camera{} {
    LOG_CORE_INFO("Window created successfully");
    m_window.setEventCallback([&](Event &e) -> void {
        Event::dispatch<KeyPressEvent>(
            e, EventType::KeyPress,
            BIND_EVENT_FUNC(Application::keyPressCallback));
        Event::dispatch<KeyReleaseEvent>(
            e, EventType::KeyRelease,
            BIND_EVENT_FUNC(Application::keyReleaseCallback));
        Event::dispatch<MouseScrollEvent>(
            e, EventType::MouseScroll,
            BIND_EVENT_FUNC(Application::mouseScrollCallback));
        Event::dispatch<MouseOffsetEvent>(
            e, EventType::MouseOffset,
            BIND_EVENT_FUNC(Application::mouseOffsetCallback));
    });
}

void Application::run() { lightingTest(); }

void Application::lightingTest() {
    const unsigned int DOWNSAMPLE = 4;
    bool isDither = true;

    FBOTex fboTex({.width = static_cast<unsigned int>(m_width) / DOWNSAMPLE,
                   .height = static_cast<unsigned int>(m_height) / DOWNSAMPLE,
                   .magSampler = GL_NEAREST,
                   .minSampler = GL_NEAREST});

    // Rectangle
    RectangleModel2D rect;
    VertexArray rectVAO;
    rectVAO.addBuffer(std::make_shared<VertexBuffer>(rect.m_points.data(),
                                                     sizeof(rect.m_points)),
                      std::make_shared<BufferLayout>(
                          BufferLayout().withLayout<PositionWithTexture2D>()));
    IndexBuffer rectIb(rect.m_indices.data(),
                       static_cast<unsigned int>(rect.m_indices.size()));

    // Skybox
    CubeModel skyboxCube;
    VertexArray skyboxVAO;
    skyboxVAO.addBuffer(
        std::make_shared<VertexBuffer>(skyboxCube.m_points.data(),
                                       sizeof(skyboxCube.m_points)),
        std::make_shared<BufferLayout>(
            BufferLayout().withLayout<PositionWithTexture3D>()));
    IndexBuffer skyboxIb(
        skyboxCube.m_indices.data(),
        static_cast<unsigned int>(skyboxCube.m_indices.size()));

    // Cube
    NormalCubeModel cube;
    VertexArray vao;
    vao.addBuffer(std::make_shared<VertexBuffer>(cube.m_points.data(),
                                                 sizeof(cube.m_points)),
                  std::make_shared<BufferLayout>(
                      BufferLayout().withLayout<PosNormalTexture3D>()));
    IndexBuffer ib(cube.m_indices.data(),
                   static_cast<unsigned int>(cube.m_indices.size()));

    // Lighting
    CubeModel lightingCube;
    VertexArray lightVAO;
    lightVAO.addBuffer(
        std::make_shared<VertexBuffer>(lightingCube.m_points.data(),
                                       sizeof(lightingCube.m_points)),
        std::make_shared<BufferLayout>(
            BufferLayout().withLayout<PositionWithTexture3D>()));
    IndexBuffer lightingIb(
        lightingCube.m_indices.data(),
        static_cast<unsigned int>(lightingCube.m_indices.size()));
    lightingCube.modelMatrix =
        glm::translate(lightingCube.modelMatrix, glm::vec3(2.0f, 2.0f, -2.0f));
    lightingCube.modelMatrix =
        glm::scale(lightingCube.modelMatrix, glm::vec3(0.6f, 0.6f, 0.6f));

    const GLCore::Sampler2D TEXTURE_SLOT = 0;
    const GLCore::Sampler2D SPECULAR_SLOT = 1;
    const GLCore::Sampler2D SKYBOX_SLOT = 2;
    const GLCore::Sampler2D FBO_TEX_SLOT = 3;
    Texture2D tex(RESOURCES_PATH "/textures/box/box_texture.png");
    Texture2D specularTex(RESOURCES_PATH "/textures/box/box_specular.png");
    CubemapTexture skyboxTex(
        {.right = RESOURCES_PATH "/textures/skybox2/right.jpg",
         .left = RESOURCES_PATH "/textures/skybox2/left.jpg",
         .top = RESOURCES_PATH "/textures/skybox2/top.jpg",
         .bottom = RESOURCES_PATH "/textures/skybox2/bottom.jpg",
         .back = RESOURCES_PATH "/textures/skybox2/back.jpg",
         .front = RESOURCES_PATH "/textures/skybox2/front.jpg"});
    tex.bind(TEXTURE_SLOT);
    specularTex.bind(SPECULAR_SLOT);
    skyboxTex.bind(SKYBOX_SLOT);
    Shader litTextureShader(RESOURCES_PATH "/shaders/specTexture.glsl");
    Shader colorShader(RESOURCES_PATH "/shaders/color3d.glsl");
    Shader skyboxShader(RESOURCES_PATH "/shaders/skyboxShader.glsl");
    Shader fboShader(RESOURCES_PATH "/shaders/dither.glsl");

    glm::mat4 projection(1.0f);
    projection = glm::perspective(
        glm::radians(45.0f), (float)m_width / (float)m_height, 0.1f, 100.0f);

    // Light
    DirectionalLight light{
        .direction = lightingCube.modelMatrix * glm::vec4(0, 0, 0, 1.0f),
        .ambient = glm::vec3(0.2f, 0.2f, 0.2f),
        .diffuse = glm::vec3(0.5f, 0.5f, 0.5f),
        .specular = glm::vec3(1.0f, 1.0f, 1.0f),
    };
    PointLight ptLight{
        .position = lightingCube.modelMatrix * glm::vec4(0, 0, 0, 1.0f),
        .ambient = glm::vec3(0.2f, 0.2f, 0.2f),
        .diffuse = glm::vec3(0.5f, 0.5f, 0.5f),
        .specular = glm::vec3(1.0f, 1.0f, 1.0f),
        .constant = 1.0f,
        .linear = 0.09f,
        .quadratic = 0.032f,
    };

    SpecMaterial material{
        .specular = SPECULAR_SLOT,
        .texture = TEXTURE_SLOT,
        .shininess = 32,
    };

    float spread = 0.05f;

    m_window.whileOpen([&]() -> void {
        fboTex.bindFBO();

        m_renderer.clear();
        GL_CALL(glEnable(GL_DEPTH_TEST));

        if (m_isMenuOpen) {
            ImGui::Begin("Debug");
            ImGui::Text(
                fmt::format("Framerate {}", ImGui::GetIO().Framerate).c_str());
            ImGui::Text("Dither");
            ImGui::SliderFloat("Spread", &spread, 0.0f, 0.4f);
            ImGui::Checkbox("Enable Dither", &isDither);
            ImGui::Text("Light");
            ImGui::SliderFloat3("Light Diffuse", &light.diffuse[0], 0.0f, 1.0f);
            ImGui::SliderFloat3("Light Specular", &light.specular[0], 0.0f,
                                1.0f);
            ImGui::SliderFloat3("Light Ambient", &light.ambient[0], 0.0f, 1.0f);
            ImGui::Text("Material");
            ImGui::SliderFloat("Material Shininess", &material.shininess, 0.0f,
                               100.0f);

            if (ImGui::Button("Quit")) {
                m_window.destroy();
            }
            ImGui::End();
        }

        cube.modelMatrix = glm::rotate(cube.modelMatrix, glm::radians(2.0f),
                                       glm::vec3(1.0f, 1.0f, 1.0f));
        m_camera.move(glm::vec3(-dx, -dy, -dz));

        litTextureShader.bind();
        litTextureShader.setUniform1i("u_texture", 0)
            .setUniform3f("u_viewPos", m_camera.getPos())
            .setMVP("u_mvp", cube.modelMatrix, m_camera.getViewMatrix(),
                    projection)
            .setLight("u_pointLight", ptLight)
            .setLight("u_dirLight", light)
            .setMaterial("u_material", material);

        for (unsigned int i = 0; i < 10; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle),
                                glm::vec3(1.0f, 0.3f, 0.5f));
            if (i != 0) {
                litTextureShader.setUniformMat4("u_mvp.model", model)
                    .setUniformMat3("u_mvp.normal",
                                    Math::getNormalMatrix(model));
            }

            m_renderer.draw(vao, ib, litTextureShader);
        }

        colorShader.bind();
        colorShader.setUniform4f("u_color", glm::vec4(light.diffuse, 1.0f))
            .setUniformMat4("u_model", lightingCube.modelMatrix)
            .setUniformMat4("u_view", m_camera.getViewMatrix())
            .setUniformMat4("u_projection", projection);

        m_renderer.draw(lightVAO, lightingIb, colorShader);

        skyboxShader.bind();
        skyboxShader
            .setMVP("u_mvp", glm::mat4(1.0f),
                    glm::mat4(glm::mat3(m_camera.getViewMatrix())), projection)
            .setUniform1i("u_skybox", SKYBOX_SLOT);

        m_renderer.draw(skyboxVAO, skyboxIb, skyboxShader);

        GL_CALL(glDisable(GL_DEPTH_TEST));

        fboTex.unbind();
        fboTex.bindTexture(FBO_TEX_SLOT);

        fboShader.bind();
        fboShader.setUniform1i("u_texture", FBO_TEX_SLOT)
            .setUniform1i("u_enable", isDither)
            .setUniform1f("u_spread", spread)
            .setUniform2f("u_resolution", glm::vec2(m_width / DOWNSAMPLE,
                                                    m_height / DOWNSAMPLE));

        GL_CALL(glViewport(0, 0, m_width, m_height));

        m_renderer.draw(rectVAO, rectIb, fboShader);
    });
}

// FBO Test

void Application::fboTest() {
    // Cube
    CubeModel cube;
    VertexArray cubeVAO;
    cubeVAO.addBuffer(std::make_shared<VertexBuffer>(cube.m_points.data(),
                                                     sizeof(cube.m_points)),
                      std::make_shared<BufferLayout>(
                          BufferLayout().withLayout<PositionWithTexture3D>()));
    IndexBuffer cubeIb(cube.m_indices.data(),
                       static_cast<unsigned int>(cube.m_indices.size()));

    const glm::mat4 projection(glm::perspective(
        glm::radians(45.0f), (float)m_width / (float)m_height, 0.1f, 100.0f));

    Shader colorShader(RESOURCES_PATH "/shaders/color3d.glsl");

    // FBO Rect
    const unsigned int FBO_SLOT = 0;
    RectangleModel2D rect;
    VertexArray rectVAO;
    rectVAO.addBuffer(std::make_shared<VertexBuffer>(rect.m_points.data(),
                                                     sizeof(rect.m_points)),
                      std::make_shared<BufferLayout>(
                          BufferLayout().withLayout<PositionWithTexture2D>()));
    IndexBuffer rectIb(rect.m_indices.data(),
                       static_cast<unsigned int>(rect.m_indices.size()));

    FBOTex fboTex({.width = static_cast<unsigned int>(m_width),
                   .height = static_cast<unsigned int>(m_height)});
    Shader fboShader(RESOURCES_PATH "/shaders/framebuffer.glsl");

    m_window.whileOpen([&]() -> void {
        fboTex.bindFBO();

        m_renderer.clear();
        GL_CALL(glEnable(GL_DEPTH_TEST));

        cube.modelMatrix = glm::rotate(cube.modelMatrix, glm::radians(2.0f),
                                       glm::vec3(1.0f, 1.0f, 1.0f));
        m_camera.move(glm::vec3(-dx, -dy, -dz));

        colorShader.bind();
        colorShader.setUniform4f("u_color", glm::vec4(0.2f, 0.8f, 0.6f, 1.0f))
            .setUniformMat4("u_model", cube.modelMatrix)
            .setUniformMat4("u_view", m_camera.getViewMatrix())
            .setUniformMat4("u_projection", projection);

        m_renderer.draw(cubeVAO, cubeIb, colorShader);

        GL_CALL(glDisable(GL_DEPTH_TEST));

        fboTex.unbind();
        fboTex.bindTexture(FBO_SLOT);

        fboShader.bind();
        fboShader.setUniform1i("u_texture", FBO_SLOT);
        m_renderer.draw(rectVAO, rectIb, fboShader);
    });
}
