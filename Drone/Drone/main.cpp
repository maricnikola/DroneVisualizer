#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

#include "OpenGLHelper.h"
#include "Drone.h"
#include "Shader.h"
#include "globals.h"
#include "callbacks.h"


void createBackround(float vertices[], unsigned int numVertices, unsigned int& VAO, unsigned int& VBO, Shader shader);
void prepareVAOandVBO(float vertices[], unsigned int numVertices, unsigned int& VAO, unsigned int& VBO, unsigned int stride);
void drawSquare(unsigned int texture, unsigned int offset, unsigned int numOfPoints);


int main(void)
{
    if (!glfwInit())
    {
        std::cout << "GLFW Biblioteka se nije ucitala! :(\n";
        return 1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;
    unsigned int wWidth = 1400;
    unsigned int wHeight = 800;
    const char wTitle[] = "[Drone]";
    window = glfwCreateWindow(width, height, wTitle, NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Prozor nije napravljen! :(\n";
        glfwTerminate();
        return 2;
    }

    glfwMakeContextCurrent(window);


    if (glewInit() != GLEW_OK)
    {
        std::cout << "GLEW nije mogao da se ucita! :'(\n";
        return 3;
    }
    Shader messageShader("message.vert", "basic.frag");
    Shader unifiedShader("basic.vert", "basic.frag");
    Shader pointShader("point.vert", "point.frag");
    Shader areaShader("area.vert", "area.frag");
    Shader barShader("bar.vert", "bar.frag");

    float vertices[] =
    {   //background
        1, -1,    1, 0,
       -1, -1,    0, 0,
        1,  1,    1, 1,
       -1,  1,    0, 1,
       // drones
     0.3, 0.1,   1, 0,
     0.26, 0.1,   0, 0,
     0.3, 0.15,   1, 1,
     0.26, 0.15,   0, 1,
     // area
    areaX1, areaY1,   1,0,
    areaX2, areaY1,   0,0,
    areaX1, areaY2,   1,1,
    areaX2, areaY2,   0,1,
    //progress bar
    -0.3,-0.9,        1,0,
    -0.9, -0.9,       0,0,
    -0.3,-0.80,        1,1,
    -0.9, -0.80,       0,1,
    // name
   -0.6,  0.75,       1,0,
   -0.95, 0.75,       0,0,
   -0.6,  0.85,       1,1,
   -0.95, 0.85,       0,1,
    };
    unsigned int VAO, VBO;
    createBackround(vertices, sizeof(vertices), VAO, VBO, unifiedShader);

    unsigned int backgroundTexture = loadTexture(BACKGROUND_PATH);
    unsigned int redDroneTexture = loadTexture(DRONE1_PATH);
    unsigned int yellowDroneTexture = loadTexture(DRONE2_PATH);
    unsigned int restrictedAreaTexture = loadTexture(AREA_PATH);
    unsigned int progressYellowTexture = loadTexture(YELLOW_PROGRESS_PATH);
    unsigned int progressRedTexture = loadTexture(RED_PROGRESS_PATH);
    unsigned int nameAndIndex = loadTexture(NAME_PATH);
    unsigned int drone1Destroyed = loadTexture(DRONE1_DESTROYED_PATH);
    unsigned int drone2Destroyed = loadTexture(DRONE2_DESTROYED_PATH);

    unsigned int pointStride = (2 + 3) * sizeof(float);

    float pointVertex[] = {
        0.0, 0.0,  0,1,0,
     -0.25,-0.25,  0,1,0
    };
    unsigned int pointVAO, pointVBO;
    //prepareVAOandVBO(pointVertex, sizeof(pointVertex), pointVAO, pointVBO, pointStride);

    //pointShader.use();

    glClearColor(0, 0, 0, 1.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    float precent = 1.0;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    const float tolerance = 0.001;

    glfwSetMouseButtonCallback(window, area_mouse_click_callback);
    glfwSetKeyCallback(window, setStartAreaPosition);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
        glClear(GL_COLOR_BUFFER_BIT);
        unifiedShader.use();
        glBindVertexArray(VAO);

        drawSquare(backgroundTexture, 0, 4);
        drawSquare(nameAndIndex, 16, 4);
        glUseProgram(0);

        if (std::fabs(std::fmod(drone1.batteryPercent, 0.10)) < tolerance) {
            //std::cout << "Battery percentage: " << drone1.batteryPercent << std::endl;
        }
        barShader.use();
        barShader.setBool("isBackground", true);
        barShader.setInt("progressBarId", 1);
        barShader.setFloat("batteryConstant", drone1.batteryPercent);
        drawSquare(progressYellowTexture, 12, 4);

        barShader.setBool("isBackground", false);

        drawSquare(progressYellowTexture, 12, 4);

        barShader.use();
        barShader.setBool("isBackground", true);
        barShader.setInt("progressBarId", -1);
        barShader.setFloat("batteryConstant", drone2.batteryPercent);

        drawSquare(progressRedTexture, 12, 4);

        barShader.setBool("isBackground", false);

        drawSquare(progressRedTexture, 12, 4);

        glUseProgram(0);

        bindPointVAOAndShader(window, pointShader, pointVAO, drone1, drone2, yellowDroneTexture, redDroneTexture);

        if (drone1.isDestroyed) {
            messageShader.use();
            messageShader.setFloat("yPosition", 0.12);
            messageShader.setInt("side", 1);
            drawSquare(drone1Destroyed, 12, 4);
        }
        if (drone2.isDestroyed) {
            messageShader.use();
            messageShader.setFloat("yPosition", 0.12);
            messageShader.setInt("side", -1);
            drawSquare(drone2Destroyed, 12, 4);
        }

        if (isRightBtnClicked) {
            expandAreaConstant += 0.00001;
        }
        areaShader.use();
        areaShader.setVec2("uPos", xOffset, yOffset);
        areaShader.setBool("isRightBtnClicked", isRightBtnClicked);
        areaShader.setFloat("expandConstant", expandAreaConstant);

        if (isRightBtnClicked) drawSquare(redDroneTexture, 8, 4);
        else drawSquare(restrictedAreaTexture, 8, 4);

        glUseProgram(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteTextures(1, &backgroundTexture);
    glDeleteTextures(1, &redDroneTexture);
    glDeleteTextures(1, &yellowDroneTexture);

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    pointShader.remove();
    unifiedShader.remove();
    glDeleteBuffers(1, &pointVBO);
    glDeleteVertexArrays(1, &pointVAO);

    glfwTerminate();

    return 0;
}

void drawSquare(unsigned int texture, unsigned int offset, unsigned int numOfPoints) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glDrawArrays(GL_TRIANGLE_STRIP, offset, numOfPoints);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void createBackround(float vertices[],
    unsigned int numVertices,
    unsigned int& VAO,
    unsigned int& VBO,
    Shader shader) {

    unsigned int stride = (2 + 2) * sizeof(float);
    prepareVAOandVBO(vertices, numVertices, VAO, VBO, stride);
}

void prepareVAOandVBO(float vertices[], unsigned int numVertices, unsigned int& VAO, unsigned int& VBO, unsigned int stride) {
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, numVertices, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
