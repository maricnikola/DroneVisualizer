#include "globals.h"
#include <cmath>

const char* BACKGROUND_PATH = "res/majevica_lopare.png";
const char* DRONE1_PATH = "res/red.png";
const char* DRONE2_PATH = "res/yellow.png";
const char* AREA_PATH = "res/blue.png";
const char* YELLOW_PROGRESS_PATH = "res/yellow_progress.jpg";
const char* RED_PROGRESS_PATH = "res/red_progress.png";
const char* NAME_PATH = "res/text/name_surname_bold.png";
const char* DRONE1_DESTROYED_PATH = "res/text/yellow_destroy_message.png";
const char* DRONE2_DESTROYED_PATH = "res/text/red_destroy_message.png";

const char* X_TEXT_PATH = "res/text/X.png";
const char* Y_TEXT_PATH = "res/text/Y.png";

const char* ZERO_DOT_PATH = "res/text/zero_dot.png";
const char* MINUS_PATH = "res/text/minus.png";

const char* NUMBER_TEXTURE_PATH[] = {
	"res/numbers/0.png",
	"res/numbers/1.png",
	"res/numbers/2.png",
	"res/numbers/3.png",
	"res/numbers/4.png",
	"res/numbers/5.png",
	"res/numbers/6.png",
	"res/numbers/7.png",
	"res/numbers/8.png",
	"res/numbers/9.png"
};
const char* PERCENTAGE_PATH = "res/text/percentage.png";

float width = 1400;
float height = 900;

float areaX1 = -0.16;
float areaX2 = -0.36;
float areaY1 = 0.6;
float areaY2 = 0.8;

bool isLeftBtnClicked = false;
bool isRightBtnClicked = false;
float expandAreaConstant = 0;

float mouseX = 0;
float mouseY = 0;
float clickedXPosition = 0;
float clickedYPosition = 0;

float xOffset = 0;
float yOffset = 0;
float xGlobalOffset = 0;
float yGlobalOffset = 0;

float getXPosition(double xPos) {
	return 2.0f * xPos / width - 1.0f;
}
float getYPosition(double yPos) {
	return 1.0f - 2.0f * yPos/ height;
}
void updateArea() {
	areaX1 += mouseX - clickedXPosition;
	areaX2 += mouseX - clickedXPosition;
	areaY1 += mouseY - clickedYPosition;
	areaY2 += mouseY - clickedYPosition;
}

float batteryConstant = 0.0001f;
float batteryDownMargin = 0.354f;

float calculateDistance(float x2, float y2, float x1, float y1) {
	return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
}