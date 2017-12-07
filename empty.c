#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "shader.h"

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

  /* create shaders */ 
  GLuint vertexShader = loadShader(GL_VERTEX_SHADER, "vshader.glsl");
  GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, "fshader.glsl");
  
  GLuint program = glCreateProgram();
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);

  glUseProgram(program);

  /* get version info */
  renderer = glGetString(GL_RENDERER);
  version = glGetString(GL_VERSION);
  printf("Renderer: %s\n", renderer);
  printf("OpenGL version supported: %s\n", version);
 
  /* tell GL to only draw onto a pixel if the shape is closer to the viewer */
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
 
  /* OTHER STUFF GOES HERE NEXT */
  while(!glfwWindowShouldClose(window)) {
      int width, height;
      glfwGetFramebufferSize(window, &width, &height);
      glViewport(0, 0, width, height);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glfwSwapBuffers(window);
      glfwPollEvents();
  }
  /* close GL context and any other GLFW resources */
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

