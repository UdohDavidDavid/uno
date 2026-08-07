#version 330 core

in vec4 fragPos;
out vec4 fragColor;

float alpha;
float distance;
float radius = 0.2f;
float outer_radius = 2.0f;

void main() {
    distance = length(fragPos.xy);
    if (distance < radius) {
        alpha = 0.0f;
    }
    else if (distance < outer_radius) {
        alpha = (distance - radius) / (outer_radius - radius);
    }
    fragColor = vec4(0.0f, 0.0f, 0.0f, alpha);
}
