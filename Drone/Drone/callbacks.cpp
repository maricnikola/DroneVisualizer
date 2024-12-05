#include "callbacks.h"
#include "globals.h"
#include <iostream>
#include <fstream>
#include <sstream>

void position_print(double xpos, double ypos) {
    std::cout << "Xposition -> " << xpos << " ,Yposition -> " << ypos;
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    mouseX = getXPosition(xpos);
    mouseY = getYPosition(ypos);
    bool inArea = mouseX <= areaX1 && mouseX >= areaX2 && mouseY >= areaY1 && mouseY <= areaY2;
    if (isLeftBtnClicked) {
        xOffset = xGlobalOffset +  mouseX - clickedXPosition;
        yOffset = yGlobalOffset + mouseY - clickedYPosition;
    }
};

void area_mouse_click_callback(GLFWwindow* window, int button, int action, int mods)
{
    double xpos, ypos;
    float setedOffsetX1 = areaX1 + xOffset;
    float setedOffsetX2 = areaX2 + xOffset;
    float setedOffsetY1 = areaY1 + yOffset;
    float setedOffsetY2 = areaY2 + yOffset;

    float centerX = (setedOffsetX1 + setedOffsetX2) / 2;
    float centerY = (setedOffsetY1 + setedOffsetY2) / 2;
    float distance = calculateDistance(centerX, centerY, mouseX, mouseY);
    bool inArea = distance < (0.09 + expandAreaConstant);
    if (button == GLFW_MOUSE_BUTTON_LEFT && inArea) {
        if (action == GLFW_PRESS) {
            glfwGetCursorPos(window, &xpos, &ypos);
            clickedXPosition = getXPosition(xpos);
            clickedYPosition = getYPosition(ypos);
            isLeftBtnClicked = true;
        }
        else if (action == GLFW_RELEASE && isLeftBtnClicked) {
            isLeftBtnClicked = false;
            xGlobalOffset = xGlobalOffset + mouseX - clickedXPosition;
            yGlobalOffset = yGlobalOffset + mouseY - clickedYPosition;
        }
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT ) {
        if (action == GLFW_PRESS && inArea) {
            isRightBtnClicked = true;
            
        }
        else if (action == GLFW_RELEASE && isRightBtnClicked) {
            isRightBtnClicked = false;
        }
    }
}

void setStartAreaPosition(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        xOffset = 0.00f;
        yOffset = 0.00f;
        xGlobalOffset = 0.00f;
        yGlobalOffset = 0.00f;
        expandAreaConstant = 0.00f;
    }
}
