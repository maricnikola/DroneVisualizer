#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

struct Drone {
    float x;
    float y;
    bool isTurned;
    float batteryPercent;
    bool isDestroyed;
};

void bindPointVAOAndShader(GLFWwindow* window, Shader shader, unsigned int& VAO,
    Drone& drone1, Drone& drone2, unsigned int texture1, unsigned int texture2);

extern Drone drone1;
extern Drone drone2;