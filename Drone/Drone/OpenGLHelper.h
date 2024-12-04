#pragma once


#include <GL/glew.h>
#include <GLFW/glfw3.h>
unsigned int createShader(const char* vsSource, const char* fsSource);

unsigned int compileShader(GLenum type, const char* source);

unsigned int loadTexture(const char* path);

void drawSquare(unsigned int texture, unsigned int offset, unsigned int numOfPoints);



