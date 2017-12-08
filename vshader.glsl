#version 410 core

in vec3 position;

out vec3 color;

void main() {
  gl_Position = vec4(position*0.2, 1.0);
  color = vec3(1.0, position.x + 0.5, position.y + 0.5);
}
