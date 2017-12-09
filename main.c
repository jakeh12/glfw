#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "utils.h"
#include "matrix.h"
#include "draw.h"
#include "camera.h"

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main()
{
  GLFWwindow* window = NULL;
  const GLubyte* renderer;
  const GLubyte* version;

  glfwSetErrorCallback(error_callback);

  if (!glfwInit()) {
    fprintf(stderr, "ERROR: could not start GLFW3\n");
    return 1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
  if (!window) {
    fprintf(stderr, "ERROR: could not open window with GLFW3\n");
    glfwTerminate();
    return 1;
  }

  glfwSetKeyCallback(window, key_callback);
  glfwMakeContextCurrent(window);

  /* start GLEW extension handler */
  glewExperimental = GL_TRUE;
  glewInit();

  /* object to render */
  static GLfloat g_vertex_buffer_data[] = {
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
};

  /* create shaders */
  GLuint vertex_shader = load_shader(GL_VERTEX_SHADER, "vshader.glsl");
  GLuint fragment_shader = load_shader(GL_FRAGMENT_SHADER, "fshader.glsl");
  GLuint program = make_program(vertex_shader, fragment_shader);

  /* create transformation matrix */
  static GLfloat mvp_matrix[16];

  /* tell GL to only draw onto a pixel if the shape is closer to the viewer */
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glDepthFunc(GL_LESS);

  /* generate VAO */
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  /* generate VBO */
  GLuint vbo = generate_buffer(sizeof(g_vertex_buffer_data), g_vertex_buffer_data);

  while(!glfwWindowShouldClose(window)) {



      // **** RENDER ****
      glUseProgram(program);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


      set_matrix(mvp_matrix, 4.0f, 3.0f, 3.0f, deg_to_rad(-45.0f), deg_to_rad(-30.0f));
      glUniformMatrix4fv(glGetUniformLocation(program, "mvp_matrix"), 1, GL_FALSE, mvp_matrix);

      draw_triangles(vbo, 36);
      // **** DONE RENDER ****



      glfwSwapBuffers(window);
      glfwPollEvents();
  }
  /* close GL context and any other GLFW resources */
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
