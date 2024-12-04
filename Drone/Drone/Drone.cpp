#include <iostream>
#include <fstream>
#include <sstream>
#include <thread> 

#include "Drone.h"
#include "globals.h"


Drone drone1 = { 0.00f, 0.00f, false, 1.00f, false };
Drone drone2 = { 0.10f, 0.10f, false, 1.00f, false };

void decreasBatteryLevel(Drone& drone) {
    if (drone.batteryPercent > 2.821) {
        drone.isDestroyed = true;
        drone.batteryPercent = 2.82f;
    }
    else {
        drone.batteryPercent += batteryConstant;
    }
}
void increaseBatteryLevel(Drone& drone) {
    if (drone.batteryPercent < 1.001f) {
        drone.batteryPercent = 1.00f;
    }
    else {
        drone.batteryPercent -= batteryConstant;
    }
}
void bindPointVAOAndShader(GLFWwindow* window, Shader shader, unsigned int& VAO,
    Drone& drone1, Drone& drone2, unsigned int texture1, unsigned int texture2) {

    if (drone1.isDestroyed && drone2.isDestroyed) return;

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS && drone1.batteryPercent > 0.00f) {
        drone1.isTurned = true;
    }
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
        drone2.isTurned = true;
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
        drone1.isTurned = false;
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
        drone2.isTurned = false;
    }
    if (drone1.isTurned) {
        decreasBatteryLevel(drone1);
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && drone1.y <= 1)
        {
            drone1.y += 0.001;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && drone1.y > -1)
        {
            drone1.y -= 0.001;
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && drone1.x <= 1)
        {
            drone1.x += 0.001;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && drone1.x >= -1.2)
        {
            drone1.x -= 0.001;
        }
    }
    else {
        increaseBatteryLevel(drone1);
    }
    if (drone2.isTurned) {
        decreasBatteryLevel(drone2);
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && drone2.y <= 1)
        {
            drone2.y += 0.001;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && drone2.y > -1)
        {
            drone2.y -= 0.001;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && drone2.x <= 1)
        {
            drone2.x += 0.001;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && drone2.x >= -1)
        {
            drone2.x -= 0.001;
        }
    }
    else {
        increaseBatteryLevel(drone2);
    }

    shader.use();
    glPointSize(20);

    if (!drone1.isDestroyed) {
        shader.setBool("isTurned", drone1.isTurned);
        shader.setVec2("uPos", drone1.x, drone1.y);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    if (!drone2.isDestroyed) {
        shader.setVec2("uPos", drone2.x, drone2.y);
        shader.setBool("isTurned", drone2.isTurned);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    glUseProgram(0);
}