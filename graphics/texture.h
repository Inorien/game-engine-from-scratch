#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//BMP loader lovingly inspired (stolen) from http://www.opengl-tutorial.org/beginners-tutorials/tutorial-5-a-textured-cube/

GLuint loadBMP(const char* path);