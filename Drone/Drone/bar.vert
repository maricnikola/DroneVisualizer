#version 330 core 

layout(location = 0) in vec2 inPos;
layout(location = 1) in vec2 inTex; 
out vec2 chTex;
uniform bool isBackground;
uniform int progressBarId;
uniform float batteryConstant;
void main()
{
	vec4 position = vec4(inPos.x * progressBarId, inPos.y, 0.0, 1.0);
	if(!isBackground){
		float xPosition;
		if(inPos.x == -0.3){
			xPosition =  (progressBarId * (inPos.x -0.015)) * batteryConstant;
		}else{
			xPosition = progressBarId * (inPos.x + 0.015);
		}
		position = vec4(xPosition, inPos.y, 0.0, 1.0);
		if(inPos.y == -0.8){
			position = vec4(xPosition, inPos.y - 0.02, 0.0, 1.0);
		}else{
			position = vec4(xPosition, inPos.y + 0.02, 0.0, 1.0);
		}
	}
	gl_Position = position;
	chTex = inTex;
}

