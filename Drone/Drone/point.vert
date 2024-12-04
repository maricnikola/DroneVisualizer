#version 330 core 

layout(location = 0) in vec2 inPos;
layout(location = 1) in vec2 inTex;
uniform vec2 uPos;

out vec2 chTex;

void main(){
	gl_Position = vec4(inPos + uPos, 0.0, 1.0);
	chTex = inTex;
}