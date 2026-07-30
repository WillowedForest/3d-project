#version 330

in vec3 vertexPosition;
in vec3 vertexNormals;
in vec2 vertexTexCoored;
in vec4 vertexColor;

uniform mat4 mvp;
uniform float uTime;

out vec3 fragNomral;
out vec3 fragPosition;
out vec4 fragColor;
out vec2 fragTexCoord;

void main(){
    float angle = uTime;
    float cosA = cos(angle);
    float sinA = sin(angle);

    vec3 rotatedPos = vec3(
        vertexPosition.x * cosA - vertexPosition.z * sinA,
        vertexPosition.y,
        vertexPosition.x * sinA + vertexPosition.z * cosA
    );

    gl_Position = mvp * vec4(rotatedPos, 1.0);

    fragNomral = vertexNormals;
    fragPosition = rotatedPos;
    fragColor = vertexColor;
    fragTexCoord = vertexTexCoored;
}
