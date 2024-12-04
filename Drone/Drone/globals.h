#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>

extern const char* BACKGROUND_PATH;
extern const char* DRONE1_PATH;
extern const char* DRONE2_PATH;
extern const char* AREA_PATH;
extern const char* YELLOW_PROGRESS_PATH;
extern const char* RED_PROGRESS_PATH;
extern const char* NAME_PATH;
extern const char* DRONE1_DESTROYED_PATH;
extern const char* DRONE2_DESTROYED_PATH;
extern const char* PERCENTAGE_PATH;

extern const char* X_TEXT_PATH;
extern const char* Y_TEXT_PATH;
extern const char* ZERO_DOT_PATH;
extern const char* MINUS_PATH;

//extern unsigned int zeroTexture;
//extern unsigned int oneTexture;
//extern unsigned int twoTexture;
//extern unsigned int threeTexture;
//extern unsigned int fourTexture;
//extern unsigned int fiveTexture;
//extern unsigned int sixTexture;
//extern unsigned int sevenTexture;
//extern unsigned int eightTexture;
//extern unsigned int nineTexture;

extern const char* NUMBER_TEXTURE_PATH[];

extern float width;
extern float height;

extern float areaX1;   
extern float areaX2;
extern float areaY1;  
extern float areaY2;

extern bool isLeftBtnClicked;
extern bool isRightBtnClicked;
extern float expandAreaConstant;
extern float mouseX;
extern float mouseY;

extern float clickedXPosition;
extern float clickedYPosition;
extern float xOffset;
extern float yOffset;
extern float xGlobalOffset;
extern float yGlobalOffset;

float getXPosition(double xPos);
float getYPosition(double yPos);

void updateArea();

extern float batteryConstant;
extern float batteryDownMargin;


float calculateDistance(float x2, float y2, float x1, float y1);
#endif 
