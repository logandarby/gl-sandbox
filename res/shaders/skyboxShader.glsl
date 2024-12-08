#shader vertex
#version 330 core

struct MVP {
    mat4 model;
    mat4 view;
    mat4 projection;
    mat3 normal;
};

layout(location = 0) in vec3 position;

uniform MVP u_mvp;
out vec3 v_texCoord;

void main() {
    vec4 pos = u_mvp.projection * u_mvp.view * vec4(position, 1.0);
    gl_Position = vec4(pos.x, pos.y, pos.w, pos.w);
    v_texCoord = position;
}



#shader fragment
#version 330 core

in vec3 v_texCoord;

uniform samplerCube u_skybox;

layout(location = 0) out vec4 color;

void main() {
    color = texture(u_skybox, v_texCoord);
}
