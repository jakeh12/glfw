#version 410 core

in vec3 position;
out vec3 color;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

void main() {
  gl_Position = model_matrix * vec4(position, 1.0);
  color = vec3(1.0, position.x + 0.5, position.y + 0.5);
}
