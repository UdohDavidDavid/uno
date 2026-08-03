#version 330 core

uniform mat4 mvp;
in vec3 vertexPosition;

out vec4 fragPos;

void main() {
    gl_Position = mvp * vec4(vertexPosition, 1.0f);
    fragPos = gl_Position;
}
