#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>

#include "OpenGLHelper.h"
#include "Drone.h"
#include "Shader.h"
#include "globals.h"
#include "callbacks.h"

void createBackround(float vertices[], unsigned int numVertices, unsigned int& VAO, unsigned int& VBO, Shader shader);
void prepareVAOandVBO(float vertices[], unsigned int numVertices, unsigned int& VAO, unsigned int& VBO, unsigned int stride);
void drawSquare(unsigned int texture, unsigned int offset, unsigned int numOfPoints);
void showDroneDestroyedMessage(Shader shader, Drone drone, int side, unsigned int messageTexture);
unsigned int getTextureFromNumber(int number);
void loadNumberTextures();
void drawBatteryPercent(float number, int side, Shader shader);
void drawDroneCoordinates(Drone drone, int side, Shader shader);

unsigned int zeroTexture;
unsigned int oneTexture;
unsigned int twoTexture;
unsigned int threeTexture;
unsigned int fourTexture;
unsigned int fiveTexture;
unsigned int sixTexture;
unsigned int sevenTexture;
unsigned int eightTexture;
unsigned int nineTexture;
unsigned int percentageTexture;
unsigned int xTexture;
unsigned int yTexture;
unsigned int zeroDotTexture;
unsigned int minusTexture;

const double TARGET_FPS = 60.0;
const double FPS = 1.0 / TARGET_FPS;

double valueToPercentage(float value, double minValue = 1.00, double maxValue = 2.81) {
    if (value < minValue) return 100.0; 
    if (value > maxValue) return 0.0;   

    double percentage =  100 - ((value - minValue) / (maxValue - minValue)) * 100.0;
    return static_cast<int>(std::round(percentage));
}

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
    const char wTitle[] = "[Drone]";
    window = glfwCreateWindow(width, height, wTitle, NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Prozor nije napravljen! :(\n";
        glfwTerminate();
        return 2;
    }
    glfwSetWindowSizeLimits(window, width, height, width, height);
    glfwMakeContextCurrent(window);


    if (glewInit() != GLEW_OK)
    {
        std::cout << "GLEW nije mogao da se ucita! :'(\n";
        return 3;
    }
    Shader messageShader("message.vert", "basic.frag");
    Shader unifiedShader("basic.vert", "background.frag");
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
   -0.4,  0.85,       1,0,
   -0.95, 0.85,       0,0,
   -0.4,  0.95,       1,1,
   -0.95, 0.95,       0,1,
    // battery percent
   -0.85, -0.9,       1,0,
   -0.90, -0.9,       0,0,
   -0.85, -0.8,       1,1,
   -0.90, -0.8,       0,1,
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
    loadNumberTextures();

    glClearColor(0, 0, 0, 1.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    float precent = 1.0;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetMouseButtonCallback(window, area_mouse_click_callback);
    glfwSetKeyCallback(window, setStartAreaPosition);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    double previousTime = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {
        double currentTime = glfwGetTime();
        double elapsedTime = currentTime - previousTime;

        if (elapsedTime < FPS) {
            glfwWaitEventsTimeout(FPS - elapsedTime);
            continue;
        }
        previousTime = currentTime;
        
        
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
        glClear(GL_COLOR_BUFFER_BIT);
        unifiedShader.use();
        unifiedShader.setBool("isMap", true);
        glBindVertexArray(VAO);

        drawSquare(backgroundTexture, 0, 4);

        unifiedShader.setBool("isMap", false);
        drawSquare(nameAndIndex, 16, 4);
        glUseProgram(0);

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

        drawDrones(window, pointShader, yellowDroneTexture, redDroneTexture);

        drawBatteryPercent(drone1.batteryPercent,  1, messageShader);
        drawBatteryPercent(drone2.batteryPercent, -1, messageShader);

        drawDroneCoordinates(drone1,  1, messageShader);
        drawDroneCoordinates(drone2, -1, messageShader);

        showDroneDestroyedMessage(messageShader, drone1,  1, drone1Destroyed);
        showDroneDestroyedMessage(messageShader, drone2, -1, drone2Destroyed);

        if (isRightBtnClicked) {
            expandAreaConstant += 0.001;
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
    glfwTerminate();

    return 0;
}
void showDroneDestroyedMessage(Shader shader, Drone drone, int side, unsigned int messageTexture) {
    if (drone.isDestroyed) {
        shader.use();
        shader.setFloat("yPosition", 0.12);
        shader.setFloat("xPosition", 0);
        shader.setInt("side", side);
        drawSquare(messageTexture, 12, 4);
    }
    glUseProgram(0);
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

void loadNumberTextures() {
    zeroTexture = loadTexture(NUMBER_TEXTURE_PATH[0]);
    oneTexture = loadTexture(NUMBER_TEXTURE_PATH[1]);
    twoTexture = loadTexture(NUMBER_TEXTURE_PATH[2]);
    threeTexture = loadTexture(NUMBER_TEXTURE_PATH[3]);
    fourTexture = loadTexture(NUMBER_TEXTURE_PATH[4]);
    fiveTexture = loadTexture(NUMBER_TEXTURE_PATH[5]);
    sixTexture = loadTexture(NUMBER_TEXTURE_PATH[6]);
    sevenTexture = loadTexture(NUMBER_TEXTURE_PATH[7]);
    eightTexture = loadTexture(NUMBER_TEXTURE_PATH[8]);
    nineTexture = loadTexture(NUMBER_TEXTURE_PATH[9]);
    percentageTexture = loadTexture(PERCENTAGE_PATH);
    zeroDotTexture = loadTexture(ZERO_DOT_PATH);
    minusTexture = loadTexture(MINUS_PATH);
    xTexture = loadTexture(X_TEXT_PATH);
    yTexture = loadTexture(Y_TEXT_PATH);
}

unsigned int getTextureFromNumber(int number) {
    switch (number)
    {
    case 0:
        return zeroTexture;
    case 1:
        return oneTexture;
    case 2:
        return twoTexture;
    case 3:
        return threeTexture;
    case 4:
        return fourTexture;
    case 5:
        return fiveTexture;
    case 6:
        return sixTexture;
    case 7:
        return sevenTexture;
    case 8:
        return eightTexture;
    case 9:
        return nineTexture;
    default:
        break;
    }
}

void drawDigits(const std::vector<int>& digits, Shader shader, float offset) {
    for (int digit : digits) {
        shader.setFloat("xPosition", offset);
        drawSquare(getTextureFromNumber(digit), 20, 4);
        offset += 0.05;
    }
}
void drawBatteryPercent(float number, int side, Shader shader) {
    int percentage = valueToPercentage(number);
    int firstDigit;
    int secondDigit;

    shader.use();
    shader.setInt("side", side);
    shader.setFloat("yPosition", -0.01);

    if (percentage == 100) {
        firstDigit = percentage / 100;
        secondDigit = (percentage / 10) % 10;
        int thirdDigit = percentage % 100;

        std::vector<int> digits = { firstDigit, secondDigit, thirdDigit };

        drawDigits(digits, shader, 0);
    
        shader.setFloat("xPosition", 0.15);
        drawSquare(percentageTexture, 20, 4);

    }else if(percentage >= 10){
        firstDigit = percentage / 10;
        secondDigit = percentage  % 10;
        std::vector<int> digits = { firstDigit, secondDigit };

        drawDigits(digits, shader, 0);

        shader.setFloat("xPosition", 0.1);
        drawSquare(percentageTexture, 20, 4);
    }
    else {
        firstDigit =  percentage;
        shader.setFloat("xPosition", 0);
        drawSquare(getTextureFromNumber(firstDigit), 20, 4);

        shader.setFloat("xPosition", 0.05);
        drawSquare(percentageTexture, 20, 4);
    }
    glUseProgram(0);
}

void drawDroneCoordinates(Drone drone, int side, Shader shader) {
    float offset = 0.00;
    shader.use();
    shader.setInt("side", side);
    shader.setFloat("yPosition", -0.1);
    shader.setFloat("xPosition", offset);
    drawSquare(xTexture, 20, 4);

    int x = (drone.centerX + drone.x) * 100;
    int y = (drone.centerY + drone.y) * 100;
    if (x < 0) {
        x = -1 * x;
        offset += 0.05;
        shader.setFloat("xPosition", offset);
        drawSquare(minusTexture, 20, 4);
    }
    int firstDigitX = x / 10;
    int secondDigitX = x % 10;
    std::vector<int> digitsX = { firstDigitX, secondDigitX };
    
    offset += 0.05;
    shader.setFloat("xPosition", offset);
    drawSquare(zeroDotTexture, 20, 4);

    offset += 0.05;
    shader.setFloat("xPosition", offset);
    drawDigits(digitsX, shader, offset);

    offset += 0.10;
    shader.setFloat("xPosition", offset);
    drawSquare(yTexture, 20, 4);
    if (y < 0) {
        y = -1 * y;
        offset += 0.05;
        shader.setFloat("xPosition", offset);
        drawSquare(minusTexture, 20, 4);
    }
    int firstDigitY = y / 10;
    int secondDigitY = y % 10;
    std::vector<int> digitsY = { firstDigitY, secondDigitY };

    offset += 0.05;
    shader.setFloat("xPosition", offset);
    drawSquare(zeroDotTexture, 20, 4);

    offset += 0.05;
    drawDigits(digitsY, shader, offset);

    glUseProgram(0);
}
