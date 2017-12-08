#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "utils.h"
#include "matrix.h"
#include "draw.h"

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

  /* create a vertex buffer */
  static GLfloat g_vertex_buffer_data[] = {
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
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


  /* generate VAO */
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  /* generate VBO */
  GLuint vbo = generate_buffer(sizeof(g_vertex_buffer_data), g_vertex_buffer_data);

  /* create shaders */
  GLuint shaders[2];
  shaders[0] = load_shader(GL_VERTEX_SHADER, "vshader.glsl");
  shaders[1] = load_shader(GL_FRAGMENT_SHADER, "fshader.glsl");
  GLuint program = make_program(shaders, 2);

  /* create model matrix */
  static GLfloat model_matrix[16] = {
    0.2f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.2f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.2f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  };


  /* create view matrix */
  static GLfloat view_matrix[16] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  };

  /* create projection matrix */
  static GLfloat projection_matrix[16] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  };

  glUseProgram(program);

  GLint model_loc = glGetUniformLocation(program, "model_matrix");
  glUniformMatrix4fv(model_loc, 1, GL_FALSE, model_matrix);
  GLint view_loc = glGetUniformLocation(program, "view_matrix");
  glUniformMatrix4fv(view_loc, 1, GL_FALSE, view_matrix);
  GLint projection_loc = glGetUniformLocation(program, "projection_matrix");
  glUniformMatrix4fv(projection_loc, 1, GL_FALSE, projection_matrix);


  /* get version info */
  renderer = glGetString(GL_RENDERER);
  version = glGetString(GL_VERSION);
  printf("Renderer: %s\n", renderer);
  printf("OpenGL version supported: %s\n", version);

  /* tell GL to only draw onto a pixel if the shape is closer to the viewer */
  glEnable(GL_DEPTH_TEST);
  //glEnable(GL_CULL_FACE);
  glDepthFunc(GL_LESS);

  /* OTHER STUFF GOES HERE NEXT */
  int width, height;
  while(!glfwWindowShouldClose(window)) {

      glfwGetFramebufferSize(window, &width, &height);
      glViewport(0, 0, width, height);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      //rotate(model_matrix, deg_to_rad(1.0), deg_to_rad(0.0), deg_to_rad(0.0));

      // **** RENDER ****
      glUseProgram(program);
      draw_triangles(vbo, 12*3);
      // **** DONE RENDER ****

      glfwSwapBuffers(window);
      glfwPollEvents();
  }
  /* close GL context and any other GLFW resources */
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
