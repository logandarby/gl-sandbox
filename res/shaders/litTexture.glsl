#shader vertex
#version 330 core

struct MVP {
    mat4 model;
    mat4 view;
    mat4 projection;
    mat3 normal;
};

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

uniform MVP u_mvp;
out vec2 v_texCoord;
out vec3 v_worldPos;
out vec3 v_normal;

void main() {
    gl_Position = u_mvp.projection * u_mvp.view * u_mvp.model * vec4(position, 1.0);
    v_texCoord = texCoord;
    v_worldPos = vec3(u_mvp.model * vec4(position, 1.0));
    v_normal = normalize(u_mvp.normal * normal);
}



#shader fragment
#version 330 core

struct Material {
    vec3 specular;
    sampler2D texture;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec2 v_texCoord;
in vec3 v_worldPos;
in vec3 v_normal;

uniform Light u_light;
uniform Material u_material;
uniform vec3 u_viewPos;

layout(location = 0) out vec4 color;

void main() {
    vec3 textureColor = vec3(texture(u_material.texture, v_texCoord));

    // Diffuse Lighting
    vec3 lightDir = normalize(u_light.position - v_worldPos);
    float diff = max(dot(v_normal, lightDir), 0.0);
    vec3 diffuse = diff * textureColor * u_light.diffuse;

    // Ambient Lighting
    vec3 ambient = u_light.ambient * textureColor;

    // Specular Lighting
    vec3 viewDir = normalize(u_viewPos - v_worldPos);
    vec3 reflectDir = reflect(-lightDir, v_normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
    vec3 specular = spec * u_material.specular * u_light.specular; 

    vec3 result = (ambient + diffuse + specular);
    color = vec4(result, 1.0);
}
