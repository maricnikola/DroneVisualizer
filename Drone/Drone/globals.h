#ifndef GLOBALS_H
#define GLOBALS_H

#include <mutex>
#include <condition_variable>

extern const char* BACKGROUND_PATH;
extern const char* DRONE1_PATH;
extern const char* DRONE2_PATH;
extern const char* AREA_PATH;
extern const char* YELLOW_PROGRESS_PATH;
extern const char* RED_PROGRESS_PATH;
extern const char* NAME_PATH;
extern const char* DRONE1_DESTROYED_PATH;
extern const char* DRONE2_DESTROYED_PATH;

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

#endif 
