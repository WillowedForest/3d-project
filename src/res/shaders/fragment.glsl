#version 330 core

in vec2 fragCoord;
out vec4 FragColor;
uniform float uTime;

vec3 hsv2rgb(vec3 c) {
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main() {
    vec2 uv = fragCoord;
    float hue = uv.x + uTime;

    vec3 color = hsv2rgb(vec3(fract(hue), 1.0, 1.0));
    FragColor = vec4(color, 1.0);

}
