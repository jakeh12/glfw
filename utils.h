#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define deg_to_rad(deg) (deg * M_PI / 180.0)
#define rad_to_deg(rad) (rad * 180.0 / M_PI)

char* load_file(const char* path);
GLuint make_shader(GLenum type, const char* source);
GLuint load_shader(GLenum type, const char* path);
GLuint make_program(GLuint vertex_shader, GLuint fragment_shader);
GLuint generate_buffer(GLuint size, GLfloat* data);
void delete_buffer(GLuint buffer);

#endif
