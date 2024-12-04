#include <iostream>
#include <fstream>
#include <sstream>
#include <thread> 

#include "Drone.h"
#include "globals.h"
#include "OpenGLHelper.h"

Drone drone1(0.28f, 0.125f, 0.00f, 0.00f, false, 1.00f, false);
Drone drone2(0.28f, 0.125f, 0.10f, 0.10f, false, 1.00f, false);

void Drone::deactivateDrone() {
    batteryPercent = 2.82;
    isDestroyed = true;
    centerX = 0;
    centerY = 0;
    x = 0;
    y = 0;
}

void Drone::decreasBatteryLevel() {
    if (batteryPercent > 2.811) {
        isDestroyed = true;
        batteryPercent = 2.81f;
    }
    else {
        batteryPercent += batteryConstant;
    }
}
void Drone::increaseBatteryLevel() {
    if (batteryPercent < 1.001f) {
        batteryPercent = 1.00f;
    }
    else {
        batteryPercent -= batteryConstant;
    }
}
void Drone::checkPositionValidity() {
    float drone1XPos = x + centerX;
    float drone1YPos = y + centerY;
    if (drone1YPos >= 1 || drone1YPos <= -1 || drone1XPos >= 1 || drone1XPos <= -1) {
        deactivateDrone();
    }
    if (isTurned) {
        float areaCenterX = (areaX1 + xOffset + areaX2 + xOffset) / 2;
        float areaCenterY = (areaY1 + yOffset + areaY2 + yOffset) / 2;
        float distanceBetweenDrons = calculateDistance(centerX + x, centerY + y, areaCenterX, areaCenterY);
        if (distanceBetweenDrons < (0.11 + expandAreaConstant)) {
            deactivateDrone();
        }
    }
}

void bindDrone1Commands(GLFWwindow* window) {
    if (drone1.isDestroyed) return;
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS && drone1.batteryPercent > 0.00f) {
        drone1.isTurned = true;
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
        drone1.isTurned = false;
    }
    if (drone1.isTurned) {
        drone1.decreasBatteryLevel();
        float drone1XPos = drone1.x + drone1.centerX;
        float drone1YPos = drone1.y + drone1.centerY;
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            drone1.y += 0.001;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            drone1.y -= 0.001;
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            drone1.x += 0.001;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            drone1.x -= 0.001;
        }
    }
    else {
        drone1.increaseBatteryLevel();
    }
    drone1.checkPositionValidity();
}

void bindDrone2Commands(GLFWwindow* window) {
    if (drone2.isDestroyed) return;
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
        drone2.isTurned = true;
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
        drone2.isTurned = false;
    }
    if (drone2.isTurned && !drone2.isDestroyed) {
        drone2.decreasBatteryLevel();
        float drone2XPos = drone2.x + drone2.centerX;
        float drone2YPos = drone2.y + drone2.centerY;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && drone2YPos <= 1)
        {
            drone2.y += 0.001;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && drone2YPos > -1)
        {
            drone2.y -= 0.001;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && drone2XPos <= 1)
        {
            drone2.x += 0.001;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && drone2XPos >= -1)
        {
            drone2.x -= 0.001;
        }
    }
    else if (!drone2.isDestroyed) {
        drone2.increaseBatteryLevel();
    }
    drone2.checkPositionValidity();
}   

void drawDrones(GLFWwindow* window, Shader shader, unsigned int texture1, unsigned int texture2) {
    bindDrone1Commands(window);
    bindDrone2Commands(window);

    if (drone1.isTurned && drone2.isTurned) {
        float distanceBetweenDrons = calculateDistance(drone1.centerX + drone1.x, drone1.centerY + drone1.y, drone2.centerX + drone2.x, drone2.centerY + drone2.y);
        if (distanceBetweenDrons < 0.03) {
            drone1.deactivateDrone();
            drone2.deactivateDrone();

        }
    }
    shader.use();
    glPointSize(20);

    if (!drone1.isDestroyed) {
        shader.setBool("isTurned", drone1.isTurned);
        shader.setVec2("uPos", drone1.x, drone1.y);

        drawSquare(texture1, 4, 4);
    }
    
    if (!drone2.isDestroyed) {
        shader.setVec2("uPos", drone2.x, drone2.y);
        shader.setBool("isTurned", drone2.isTurned);

        drawSquare(texture2, 4, 4);
    }

    glUseProgram(0);
}