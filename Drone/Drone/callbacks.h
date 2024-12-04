#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void position_print(double xpos, double ypos);
void area_mouse_click_callback(GLFWwindow* window, int button, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void setStartAreaPosition(GLFWwindow* window, int key, int scancode, int action, int mods);