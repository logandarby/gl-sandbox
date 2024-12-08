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

struct SpecMaterial {
    sampler2D specular;
    sampler2D texture;
    float shininess;
};

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

in vec2 v_texCoord;
in vec3 v_worldPos;
in vec3 v_normal;

uniform DirectionalLight u_dirLight;
uniform PointLight u_pointLight;
uniform SpecMaterial u_material;
uniform vec3 u_viewPos;

layout(location = 0) out vec4 color;

vec3 calcPointLight(PointLight light, vec3 normal, vec3 position, vec3 viewDir);
vec3 calcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir);

void main() {
    vec3 viewDir = normalize(u_viewPos - v_worldPos);
    vec3 ptResult = calcPointLight(u_pointLight, normalize(v_normal), v_worldPos, viewDir);
    vec3 dirResult = calcDirectionalLight(u_dirLight, normalize(v_normal), viewDir);
    color = vec4(ptResult + dirResult, 1.0);
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 position, vec3 viewDir) {
    vec3 textureColor = vec3(texture(u_material.texture, v_texCoord));
    vec3 specularColor = vec3(texture(u_material.specular, v_texCoord));

    vec3 lightDir = normalize(light.position - position);

    // Diffuse shadinLighting
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular Lhading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
    // Attenuation
    float distance = length(light.position - position);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
        light.quadratic * (distance * distance));    

    // combine results
    vec3 ambient  = attenuation * light.ambient  * textureColor;
    vec3 diffuse  = attenuation * light.diffuse  * diff * textureColor;
    vec3 specular = attenuation * light.specular * spec * specularColor;
    return ambient + diffuse + specular;
}

vec3 calcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir) {
    vec3 textureColor = vec3(texture(u_material.texture, v_texCoord));
    vec3 specularColor = vec3(texture(u_material.specular, v_texCoord));

    // Ambient Lighting
    vec3 ambient = light.ambient * textureColor;

    // Diffuse Lighting
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * textureColor * light.diffuse;

    // Specular Lighting
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
    vec3 specular = spec * specularColor * light.specular; 

    return ambient + diffuse + specular;
}
