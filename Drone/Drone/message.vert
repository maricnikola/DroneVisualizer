#version 330 core 

layout(location = 0) in vec2 inPos;
layout(location = 1) in vec2 inTex;

uniform float yPosition;
uniform int side;
out vec2 chTex;

void main(){
	gl_Position = vec4(inPos.x * side, inPos.y + yPosition, 0.0, 1.0);
	chTex = inTex;
}