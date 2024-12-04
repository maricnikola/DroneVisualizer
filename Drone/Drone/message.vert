#version 330 core 

layout(location = 0) in vec2 inPos;
layout(location = 1) in vec2 inTex;

uniform float yPosition;
uniform float xPosition;
uniform int side;
out vec2 chTex;

void main(){
	float translation = 0;
	if(side == -1){
		translation = 1.2;
	}
	float xPos = inPos.x + xPosition + translation;
	gl_Position = vec4(xPos, inPos.y + yPosition, 0.0, 1.0);
	chTex = inTex;
}