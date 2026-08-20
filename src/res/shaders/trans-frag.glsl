#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

out vec4 finalColor;

void main() {
    // Get the vertical position (0.0 to 1.0)
    float y = fragTexCoord.y;

    // Trans flag colors (RGB normalized)
    vec3 lightBlue = vec3(0.55, 0.81, 0.95);  // Top
    vec3 white = vec3(1.0, 1.0, 1.0);         // Middle
    vec3 pink = vec3(0.95, 0.57, 0.78);       // Bottom

    // Assign colors based on vertical position
    vec3 color;
    if (y < 0.333) {
        color = lightBlue;
    } else if (y < 0.666) {
        color = white;
    } else {
        color = pink;
    }

    finalColor = vec4(color, 1.0) * fragColor;
}
