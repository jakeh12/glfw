#version 410 core

in vec3 color;
out vec3 out_color;

void main() {
  //out_color = vec3(1,1,0);
  out_color = vec3(color);
}
