#shader vertex
#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_texCoord;
out vec2 v_position;

void main() {
    gl_Position = vec4(position.x, position.y, 0.0, 1.0);
    v_position = position.xy;
    v_texCoord = texCoord;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 FragColor;
in vec2 v_texCoord;
in vec2 v_position;

uniform sampler2D u_texture;
uniform vec2 u_resolution;
uniform float u_spread = 0.25;
uniform int u_enable;

const float colorCount = 4;
const vec3 palette[4] = vec3[](
    vec3(110, 131, 135) / 255.0,
    vec3(164, 184, 196) / 255.0,
    vec3(200, 211, 213) / 255.0,
    vec3(252, 250, 250) / 255.0
);

const int bayer4[4 * 4] = int[](
    0, 8, 2, 10,
    12, 4, 14, 6,
    3, 11, 1, 9,
    15, 7, 13, 5
);

const int bayer8[8 * 8] = int[] (
    0, 32, 8, 40, 2, 34, 10, 42,
    48, 16, 56, 24, 50, 18, 58, 26,
    12, 44, 4, 36, 14, 46, 6, 38,   
    60, 28, 52, 20, 62, 30, 54, 22,
    3, 35, 11, 43, 1, 33, 9, 41,
    51, 19, 59, 27, 49, 17, 57, 25,
    15, 47, 7, 39, 13, 45, 5, 37,
    63, 31, 55, 23, 61, 29, 53, 21
);

float getBayer4(int x, int y) {
    return float(bayer4[(x % 4) + (y % 4) * 4]) * (1.0f / 16.0f) - 0.5;
}

float getBayer8(int x, int y) {
    return float(bayer8[(x % 8) + (y % 8) * 8]) * (1.0f / 64.0f) - 0.5;
}

void quantizeColor(inout vec4 color, in float colorCount) {
    vec3 newColor = floor((color.rgb * (colorCount - 1)) + 0.5) / (colorCount - 1);
    color = vec4(newColor, color.a);
}

void makeGreyscale(inout vec4 color) {
    float grey = dot(color.rgb, vec3(0.299, 0.587, 0.114));
    color = vec4(grey, grey, grey, color.a);
}

void addDitherNoise(inout vec4 color, in vec2 screenCoord, in float spread) {
    float noise = getBayer8(int(screenCoord.x), int(screenCoord.y));
    color += spread * noise;
}

void main() {
    if (u_enable == 0) {
        FragColor = texture(u_texture, v_texCoord);
        return;
    }
    vec2 screenCoord = u_resolution * v_texCoord;
    vec4 color = texture(u_texture, v_texCoord);
    addDitherNoise(color, screenCoord, u_spread);
    makeGreyscale(color);
    quantizeColor(color, colorCount);
    color = vec4(palette[min(int(color.r * (colorCount - 1)), 3)], 1.0);
    FragColor = color;
}
