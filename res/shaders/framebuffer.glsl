#shader vertex
#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_texCoord;

void main() {
    gl_Position = vec4(position.x, position.y, 0.0, 1.0);
    v_texCoord = texCoord;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 FragColor;
in vec2 v_texCoord;

uniform sampler2D u_texture;

const float offset_x = 1.0f / 800.0f;  
const float offset_y = 1.0f / 800.0f;  

vec2 offsets[9] = vec2[]
(
    vec2(-offset_x,  offset_y), vec2( 0.0f,    offset_y), vec2( offset_x,  offset_y),
    vec2(-offset_x,  0.0f),     vec2( 0.0f,    0.0f),     vec2( offset_x,  0.0f),
    vec2(-offset_x, -offset_y), vec2( 0.0f,   -offset_y), vec2( offset_x, -offset_y) 
);

float edKernel[9] = float[]
(
    1,  1, 1,
    1, -10, 1,
    1,  1, 1
);

float blurKernel[9] = float[]
(
    1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0,
    1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0,
    1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0
);

void main() {
    // color = vec4(1.0, 1.0, 1.0, 1.0);
    // FragColor = texture(u_texture, v_texCoord);
    FragColor = vec4(vec3(1.0) - vec3(texture(u_texture, v_texCoord)), 1.0);
    // vec3 color = vec3(0.0f);
    // for(int i = 0; i < 9; i++)
    //     color += vec3(texture(u_texture, v_texCoord.st + offsets[i])) * edKernel[i];
    // FragColor = vec4(color, 1.0f);
}
