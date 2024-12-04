#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

class Drone {
public:
    float centerX;
    float centerY;
    float x;
    float y;
    bool isTurned;
    float batteryPercent;
    bool isDestroyed;

    Drone(float cX, float cY, float posX, float posY, bool turned, float battery, bool destroyed)
        : centerX(cX), centerY(cY), x(posX), y(posY), isTurned(turned), batteryPercent(battery), isDestroyed(destroyed) {
    }
    void deactivateDrone();
    void decreasBatteryLevel();
    void increaseBatteryLevel();
    void checkPositionValidity();
};

void drawDrones(GLFWwindow* window, Shader shader, unsigned int texture1, unsigned int texture2);

extern Drone drone1;
extern Drone drone2;