#version 330 core 

layout(location = 0) in vec2 inPos;
layout(location = 1) in vec2 inTex; 
out vec2 chTex;
uniform bool isRightBtnClicked;
uniform float expandConstant;
uniform vec2 uPos;

void main()
{
	vec4 position;
	float xPosition;
	float yPosition;
	if(inPos.x == -0.16){
		xPosition =  inPos.x + expandConstant;
	}else{
		xPosition = inPos.x - expandConstant;
	}
	xPosition += uPos.x;
	position = vec4(xPosition, inPos.y, 0.0, 1.0);
	if(inPos.y == 0.6){
		yPosition = inPos.y - expandConstant;
	}else{
		yPosition = inPos.y + expandConstant;
	}
	yPosition += uPos.y;

	position = vec4(xPosition, yPosition, 0.0, 1.0);
		
	gl_Position = position;
	chTex = inTex;
}

